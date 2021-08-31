#pragma once
#include "CPlaneMeshComponent.h"

template <class VertexType>
class CDisplay2DComponent :public CPlaneMeshComponent<VertexType>
{
private:
	ID3D11ShaderResourceView* mTextureSRV = nullptr;

	void Init(std::string vertexShaderPath , std::string pixelShaderPath)override;

public:
	CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
		std::string vertexShaderPath = "Shader/basicvs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	CDisplay2DComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
		std::string vertexShaderPath = "Shader/basicnotexvs.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");

	void Update()override;
	void Render()override;
};