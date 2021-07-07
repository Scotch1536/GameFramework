#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

class CSphereMeshComponent :public CPrimitiveMeshComponent
{
private:
	float mRadius;				//”¼Œa
	int mDivisionNumber;		//•ªŠ„”

	void CreateVertexData()override;
	void CreateIndexData()override;

public:
	CSphereMeshComponent(CActor& owner , CTransform& parentTrans , float radius , int divNum , XMFLOAT4 color ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");

};