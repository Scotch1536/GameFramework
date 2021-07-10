#pragma once
#include "CPlaneMeshComponent.h"

class CBillboardComponent :public CPlaneMeshComponent<SVertexUV>
{
private:
	ID3D11ShaderResourceView* mTextureSRV;

	void Init(std::string vertexShaderPath , std::string pixelShaderPath)override;

public:
	CBillboardComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
		std::string vertexShaderPath = "Shader/vs.hlsl" , std::string pixelShaderPath = "Shader/pstexcol.hlsl");

	void Update()override;
	void Render()override;
};