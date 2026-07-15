#pragma once
#include "SpriteRender.h"


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
	SpriteRender spriteRender_;  /** スプライトレンダー */

	float time_ = 0.0f;  /** 時間の経過を管理する変数 */
};
