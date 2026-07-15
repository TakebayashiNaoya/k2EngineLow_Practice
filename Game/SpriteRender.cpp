#include "stdafx.h"
#include "SpriteRender.h"


SpriteRender::SpriteRender()
{

}


SpriteRender::~SpriteRender()
{}


void SpriteRender::Init(const char* ddsFilePath, float width, float height)
{
	SpriteInitData initData;
	initData.m_ddsFilePath[0] = ddsFilePath;
	initData.m_fxFilePath = "Assets/shader/sprite.fx";
	initData.m_width = width;
	initData.m_height = height;
	sprite_.Init(initData);

	position_ = Vector2(0.0f, 0.0f);
	scale_ = Vector2(1.0f, 1.0f);
	rotation_ = Quaternion::Identity;
}


void SpriteRender::Update()
{
	sprite_.Update({ position_.x, position_.y, 0.0f }, rotation_, { scale_.x, scale_.y, 1.0f });
}


void SpriteRender::Draw(RenderContext& renderContext)
{
	sprite_.Draw(renderContext);
}