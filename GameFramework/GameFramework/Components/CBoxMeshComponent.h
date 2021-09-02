#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

class CBoxMeshComponent :public CPrimitiveMeshComponent<>
{
private:
	XMFLOAT3 mMin , mMax;		//原点と頂点との間の長さ

	void CreateVertexData()override;
	void CreateIndexData()override;

public:
	CBoxMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } ,
		XMFLOAT3 min = { -0.5f,-0.5f,-0.5f } , XMFLOAT3 max = { 0.5f,0.5f,0.5f } ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");
};