#pragma once
#include "CPlaneMeshComponent.h"

class CBillboardComponent :public CPlaneMeshComponent
{
private:
	void Init(std::string vertexShaderPath , std::string pixelShaderPath)override;

public:
	CBillboardComponent(CActor& owner , CTransform& parentTrans ,
		std::string vertexShaderPath = "Shader/vs.hlsl" , std::string pixelShaderPath = "Shader/ps.hlsl");
};