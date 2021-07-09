#pragma once
#include "CPrimitiveMeshComponent.h"

class CPlaneMeshComponent :public CPrimitiveMeshComponent
{
protected:
	void CreateVertexData()override;
	void CreateIndexData()override;

public:
	CPlaneMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl" , bool isInit = true);
};