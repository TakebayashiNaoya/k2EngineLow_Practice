#pragma once


class SpriteRender
{
public:
	/** 座標を設定 */
	inline void SetPosition(const Vector3& position) { position_.Set(position.x, position.y); }
	inline void SetPosition(const Vector2& position) { position_ = position; }
	inline void SetPosition(float x, float y) { position_.Set(x, y); }
	/** 拡縮を設定 */
	inline void SetScale(const Vector3& scale) { scale_.Set(scale.x, scale.y); }
	inline void SetScale(const Vector2& scale) { scale_ = scale; }
	inline void SetScale(float x, float y) { scale_.Set(x, y); }
	/** 回転を設定 */
	inline void SetRotation(const Quaternion& rotation) { rotation_ = rotation; }


public:
	/** 初期化 */
	void Init(const char* ddsFilePath,float width, float height);
	/** 更新 */
	void Update();
	/** 描画 */
	void Draw(RenderContext& renderContext);

	SpriteRender();
	~SpriteRender();


private:
	Vector2	   position_;  /** 座標 */
	Vector2	   scale_;     /** 拡縮 */
	Quaternion rotation_;  /** 回転 */

	Sprite	   sprite_;	   /** スプライト */
};

