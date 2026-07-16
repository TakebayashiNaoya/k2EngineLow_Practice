/*!
 * @brief   Minimal model shader (STARTING POINT).
 *
 * Right now this only draws the albedo (base color) texture. There is NO lighting.
 * Your job is to add lighting here, step by step:
 *   1. ambient        (add a constant brightness)
 *   2. diffuse         (directional light + Lambert:  dot(normal, -lightDir))
 *   3. specular        (Phong / Blinn-Phong highlight)
 *   4. specular map    (control the highlight strength per-pixel with a texture)
 *   5. normal map      (per-pixel normals using the tangent space / TBN)
 *
 * See: 学習ガイド_自作レンダリングエンジン.md  (Phase 1)
 *
 * NOTE: To pass values (light direction/color, ambient, etc.) from C++ into this
 *       shader, add your own cbuffer here and fill it from a ConstantBuffer on the
 *       C++ side. The engine does NOT feed lighting data anymore (that used to be
 *       k2Engine's job, which you are now replacing).
 */

cbuffer LightCB : register(b1)
{
    // --- Step 1-5 : ライティング① アンビエント（環境光） --- //
    float3 ambientColor;
    float pad1;
    // --- Step 1-6 : ライティング② ディフューズ（拡散反射） --- //
    float3 DirectionalLightColor;
    float pad2;
    float3 lightDirection;
    float pad3;
    // --- Step 1-7 : ライティング③ スペキュラ（鏡面反射） --- //
    float3 cameraPosition;
    float pad4;
};

////////////////////////////////////////////////
// Pixel shader input.
////////////////////////////////////////////////
struct SPSIn
{
    float4 pos      : SV_POSITION;  // Clip-space position.
    float3 normal   : NORMAL;       // World-space normal.
    float3 tangent  : TANGENT;      // World-space tangent   (for normal mapping later).
    float3 biNormal : BINORMAL;     // World-space binormal  (for normal mapping later).
    float2 uv       : TEXCOORD0;    // UV.
    float3 worldPos : TEXCOORD1;    // World-space position  (for specular later).
};

///////////////////////////////////////
// Common vertex shader code.
// Provides: ModelCb(b0: mWorld/mView/mProj), SVSIn, bone matrices (t3),
//           and the entry points VSMain / VSMainSkin / VSMainInstancing, etc.
///////////////////////////////////////
#include "ModelVSCommon.h"

///////////////////////////////////////
// Shader resources.
// The tkm material binds the albedo texture to t0.
// (t1 = normal map, t2 = metallic/smooth — you can add them when you need them.)
///////////////////////////////////////
Texture2D<float4> albedoTexture : register(t0);
Texture2D<float4> normalMap     : register(t1);
Texture2D<float4> specularMap   : register(t2);
sampler Sampler : register(s0);

////////////////////////////////////////////////
// Vertex shader core (called by the VSMain* entry points in ModelVSCommon.h).
////////////////////////////////////////////////
SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer)
{
    SPSIn psIn;

    // Local space -> world space.
    psIn.pos = CalcVertexPositionInWorldSpace(vsIn.pos, mWorldLocal, isUsePreComputedVertexBuffer);
    psIn.worldPos = psIn.pos;

    // World -> view -> projection (clip) space.
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);

    // World-space normal / tangent / binormal.
    CalcVertexNormalTangentBiNormalInWorldSpace(
        psIn.normal,
        psIn.tangent,
        psIn.biNormal,
        mWorldLocal,
        vsIn.normal,
        vsIn.tangent,
        vsIn.biNormal,
        isUsePreComputedVertexBuffer
    );

    psIn.uv = vsIn.uv;
    return psIn;
}

////////////////////////////////////////////////
// Pixel shader.
// For now: just output the albedo texture. Add your lighting here.
////////////////////////////////////////////////
float4 PSMain(SPSIn In) : SV_Target0
{
    float4 albedoColor = albedoTexture.Sample(Sampler, In.uv);
    float3 lig;    
    
    // --- Step 1-9 : ノーマルマップ（法線マップ） --- //
    float3 normalMapColor = normalMap.Sample(Sampler, In.uv);
    // 法線マップの色を[0,1]から[-1,1]に変換して正規化
    float3 localNormal = normalize(normalMapColor * 2.0f - 1.0f);
    // 各ベクトルを正規化（ピクセル間補間で長さが変わるため必ず行う）
    float3 T = normalize(In.tangent);
    float3 B = normalize(In.biNormal);
    float3 N = normalize(In.normal);
    // TBN行列の構築 (HLSLでは行ベクトルとして自動構成されます)
    float3x3 TBN = float3x3(T, B, N);
    // ローカル空間の法線をワールド空間に変換
    float3 worldNormal = normalize(mul(localNormal, TBN));

    // TODO: add lighting. For example, start with ambient:
    // --- Step 1-5 : ライティング① アンビエント（環境光） --- //
    float3 ambientLightColor = ambientColor;
    //albedoColor.xyz *= ambient;
    
    // --- Step 1-6 : ライティング② ディフューズ（拡散反射） --- //
    float power = max(normalize(dot(worldNormal, lightDirection * -1.0f)), 0.0f);
    float3 directionalLightColor = DirectionalLightColor * power;
    //lig = ambient + directionalLightColor;
    //albedoColor *= lig;
    
    // --- Step 1-7 : ライティング③ スペキュラ（鏡面反射） --- //
    float3 reflectDir = reflect(lightDirection, worldNormal);
    float3 toCamera = normalize(cameraPosition - In.worldPos);
    float t = pow(max(dot(toCamera, reflectDir), 0.0f), 1.0f);
    
    // --- Step 1-8 : スペキュラマップ --- //
    float3 specMap = specularMap.Sample(Sampler, In.uv);
    float3 specular = DirectionalLightColor * t * specMap;
    
    
    lig = ambientLightColor + directionalLightColor + specular;
    albedoColor.xyz *= lig;

    return albedoColor;
}
