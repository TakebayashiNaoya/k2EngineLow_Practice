#pragma once
#include "SpriteRender.h"
#include "graphics/Model.h"
#include "ModelRender.h"


// The starting point of your game.
// This is a plain IGameObject running on K2EngineLow only.
// Right now it draws nothing, so you will just see the gray clear color.
// Add your own rendering (a triangle, a sprite, a model...) step by step.
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);


private:
	float time_ = 0.0f;  /** 時間の経過を管理する変数 */

	// --- Step 1-2 : `SpriteRender` を自作する --- //
	//SpriteRender spriteRender_;  /** スプライトレンダー */

	// --- Step 1-3 : モデルを1体出す（3D） --- //
	//Model model;

	// --- Step 1-4 : `ModelRender` を自作する --- //
	ModelRender modelRender_;  /** モデルレンダー */
};
