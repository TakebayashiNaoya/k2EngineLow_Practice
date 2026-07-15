#pragma once


struct LightCB
{
	// --- Step 1-5 : ライティング① アンビエント（環境光） --- //
	Vector4 ambientColor=Vector4(0.5f, 0.5f, 0.5f, 1.0f);

	// --- Step 1-6 : ライティング② ディフューズ（拡散反射） --- //
	Vector4 DirectionalLightColor = Vector4(0.5, 0.5, 0.5, 1.0f);
	Vector3 lightDirection = Vector3(1.0f, 0.0f, 0.0f);

	// --- Step 1-7 : ライティング③ スペキュラ（鏡面反射） --- //
	Vector3 cameraPosition = g_camera3D->GetPosition();
};


class ModelRender
{
public:
	/** 座標を設定 */
	void SetPosition(const Vector3& position) { position_ = position; }
	void SetPosition(float x, float y, float z) { position_.Set(x, y, z); }
	/** 拡縮を設定 */
	void SetScale(const Vector3& scale) { scale_ = scale; }
	void SetScale(float x, float y, float z) { scale_.Set(x, y, z); }
	/** 回転を設定 */
	void SetRotation(const Quaternion& rotation) { rotation_ = rotation; }


public:
	/** 初期化 */
	void Init(const char* modelFilePath);
	/** 更新 */
	void Update();
	/** 描画 */
	void Draw(RenderContext& renderContext);

	ModelRender() {};
	~ModelRender() {};


private:
	Vector3	   position_;  /** 座標 */
	Vector3	   scale_;     /** 拡縮 */
	Quaternion rotation_;  /** 回転 */

	Model	   model_;	   /** モデル */

	// --- Step 1-5 : ライティング① アンビエント（環境光） --- //
	LightCB lightCB_; /** 定数バッファ */
};

