#include "stdafx.h"
#include "ModelRender.h"


void ModelRender::Init(const char* modelFilePath)
{
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = modelFilePath;
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	modelInitData.m_expandConstantBuffer = &lightCB_;
	modelInitData.m_expandConstantBufferSize = sizeof(lightCB_);
	model_.Init(modelInitData);
}


void ModelRender::Update()
{
	model_.UpdateWorldMatrix(position_, rotation_, scale_);
}


void ModelRender::Draw(RenderContext & renderContext)
{
	model_.Draw(renderContext);
}
