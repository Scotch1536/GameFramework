#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

class CBoxMeshComponent :public CPrimitiveMeshComponent<>
{
private:
	XMFLOAT3 mMin , mMax;		//���_�ƒ��_�Ƃ̊Ԃ̒���

	void CreateVertexData()override;
	void CreateIndexData()override;

public:
	CBoxMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT3 min , XMFLOAT3 max , XMFLOAT4 color ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");

};