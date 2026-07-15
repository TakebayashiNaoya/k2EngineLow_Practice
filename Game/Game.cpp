#include "stdafx.h"
#include "Game.h"


bool Game::Start()
{
	// Step 1-2 : `SpriteRender` を自作する
	//spriteRender_.Init("Assets/modelData/ground.dds", 100.0f, 100.0f);

	// Step 1-3 : モデルを1体出す（3D）
	//{
	//	ModelInitData modelInitData;
	//	modelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//	modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//	model.Init(modelInitData);
	//}

	// Step 1-4 : `ModelRender` を自作する
	modelRender_.Init("Assets/modelData/unityChan.tkm");

	return true;
}


void Game::Update()
{
	time_ += 0.01f;
	if (time_ > 1.0f)
	{
		time_ = 0.0f;
	}

	// Step 1-2 : `SpriteRender` を自作する
	//{
	//	spriteRender_.SetPosition(time_ * 500, time_ * 500);
	//	spriteRender_.SetScale(1.0f + time_, 1.0f + time_);
	//	Quaternion rotation;
	//	rotation.SetRotationDegZ(time_ * 360.0f);
	//	spriteRender_.SetRotation(rotation);

	//	spriteRender_.Update();
	//}

	// Step 1-4 : `ModelRender` を自作する
	{
		modelRender_.SetPosition(0.0f, 0.0f, 0.0f);
		modelRender_.SetScale(1.0f , 1.0f, 1.0f);
		Quaternion rotation;
		rotation.SetRotationDegY(time_ * 360.0f);
		modelRender_.SetRotation(rotation);
		modelRender_.Update();
	}
}


void Game::Render(RenderContext& rc)
{
	// Step 1-2 : `SpriteRender` を自作する
	//spriteRender_.Draw(rc);

	// Step 1-3 : モデルを1体出す（3D）
	//model.Draw(rc);

	// Step 1-4 : `ModelRender` を自作する
	modelRender_.Draw(rc);
}
