#pragma once
#include <string>

#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

class CRenderComponent;

class C2DTextureComponent :public CComponent, public IRender
{
private:
	CRenderComponent& mRenderComponent;			//�����_�[�R���|�[�l���g
public:
	C2DTextureComponent(CActor& owner, std::string vertexShaderPath, std::string pixelShaderPath, int priority = 100);
};
