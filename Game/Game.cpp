#include "stdafx.h"
#include "Game.h"


bool Game::Start()
{
	// Step 1-2 : `SpriteRender` を自作する
	spriteRender_.Init("Assets/modelData/ground.dds", 100.0f, 100.0f);

	// Step 1-3 : モデルを1体出す（3D）
	{
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		model.Init(modelInitData);
	}

	return true;
}


void Game::Update()
{
	// Step 1-2 : `SpriteRender` を自作する
	{
		time_ += 0.01f;
		if (time_ > 1.0f)
		{
			time_ = 0.0f;
		}

		spriteRender_.SetPosition(time_ * 500, time_ * 500);
		spriteRender_.SetScale(1.0f + time_, 1.0f + time_);
		Quaternion rotation;
		rotation.SetRotationDegZ(time_ * 360.0f);
		spriteRender_.SetRotation(rotation);

		spriteRender_.Update();
	}
}


void Game::Render(RenderContext& rc)
{
	// Step 1-2 : `SpriteRender` を自作する
	spriteRender_.Draw(rc);

	// Step 1-3 : モデルを1体出す（3D）
	model.Draw(rc);
}
