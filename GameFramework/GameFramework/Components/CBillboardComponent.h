#pragma once
#include "CPlaneMeshComponent.h"

class CBillboardComponent :public CPlaneMeshComponent<SVertexUV>
{
private:
	ID3D11ShaderResourceView* mTextureSRV;

	void Init(std::string vertexShaderPath , std::string pixelShaderPath)override;

	void Update()override;
	void Render()override;

public:
	CBillboardComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
		std::string vertexShaderPath = "Shader/vs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	XMFLOAT2* GetUV(int index)
	{
		return &mVertices.at(index).Tex;
	};

};