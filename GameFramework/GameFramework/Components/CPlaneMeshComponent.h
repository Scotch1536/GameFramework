#pragma once
#include "CPrimitiveMeshComponent.h"

template<class VertexType = SVertexColor>
class CPlaneMeshComponent :public CPrimitiveMeshComponent<VertexType>
{
protected:
	void CreateVertexData()override;
	void CreateIndexData()override;

public:
	CPlaneMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl" , bool isInit = true);
};