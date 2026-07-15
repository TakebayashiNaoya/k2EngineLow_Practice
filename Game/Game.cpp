#include "stdafx.h"
#include "Game.h"


bool Game::Start()
{
	spriteRender_.Init("Assets/modelData/ground.dds", 100.0f, 100.0f);
	return true;
}


void Game::Update()
{
	time_ += 0.01f;
	if (time_ > 1.0f)
	{
		time_ = 0.0f;
	}

	spriteRender_.SetPosition(time_*500, time_*500);
	spriteRender_.SetScale(1.0f + time_, 1.0f + time_);
	Quaternion rotation;
	rotation.SetRotationDegZ(time_ * 360.0f);
	spriteRender_.SetRotation(rotation);

	spriteRender_.Update();
}


void Game::Render(RenderContext& rc)
{
	spriteRender_.Draw(rc);
}
