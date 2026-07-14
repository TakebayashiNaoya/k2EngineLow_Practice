#include "stdafx.h"
#include "Game.h"


bool Game::Start()
{
	SpriteInitData initData;
	initData.m_ddsFilePath[0] = "Assets/modelData/ground.DDS";
	initData.m_fxFilePath = "Assets/shader/sprite.fx";
	initData.m_width = 512;
	initData.m_height = 512;
	sprite_.Init(initData);
	return true;
}

void Game::Update()
{
}

void Game::Render(RenderContext& rc)
{
	sprite_.Draw(rc);
}
