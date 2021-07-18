#pragma once
#include "CPlaneMeshComponent.h"

class CDisplay2DComponent :public CPlaneMeshComponent<SVertex2D>
{
private:
	ID3D11ShaderResourceView* mTextureSRV;

	void Init(std::string vertexShaderPath , std::string pixelShaderPath)override;

public:
	CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
		std::string vertexShaderPath = "Shader/basicvs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	void Update()override;
	void Render()override;
};