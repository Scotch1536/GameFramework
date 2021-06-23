#pragma once
#include <string>

#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

class CRenderComponent;

class C2DTextureComponent :public CComponent, public IRender
{
private:
	CRenderComponent& mRenderComponent;			//レンダーコンポーネント
public:
	C2DTextureComponent(CActor& owner, std::string vertexShaderPath, std::string pixelShaderPath, int priority = 100);
};
