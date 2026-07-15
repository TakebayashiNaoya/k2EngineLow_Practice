#pragma once


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
};

