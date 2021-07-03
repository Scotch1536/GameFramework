#pragma once
#include <string>

#include "../ExternalCode/CTextureData.h"
#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

class CRenderComponent;

class CSprite2DComponent :public CComponent,public IRender
{
private:
	CTextureData& mTexture;
	CRenderComponent& mRenderComponent;
	
public:
	CTransform Transform;
	CSprite2DComponent(CActor& owner, CTextureData& texture, std::string vertexShaderPath, std::string pixelShaderPath, int priority = 45);

	void Render()override;
};