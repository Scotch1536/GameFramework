#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

class CSphereMeshComponent :public CPrimitiveMeshComponent<>
{
private:
	float mRadius;				//���a
	int mDivisionNumber;		//������

	void CreateVertexData()override;
	void CreateIndexData()override;

public:
	CSphereMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f } , int divNum = 50 , float radius = 0.5f ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");
};