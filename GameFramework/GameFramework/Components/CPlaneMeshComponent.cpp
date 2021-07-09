#include "CPlaneMeshComponent.h"

CPlaneMeshComponent::CPlaneMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color ,
	std::string vertexShaderPath , std::string pixelShaderPath , bool isInit)
	:CPrimitiveMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath)
{
	if(isInit)Init(vertexShaderPath , pixelShaderPath);
}

void CPlaneMeshComponent::CreateVertexData()
{
	mVertices.resize(4);

	mVertices.at(0).Pos = { -1.0f,1.0f,0.0f };
	mVertices.at(1).Pos = { 1.0f,1.0f,0.0f };
	mVertices.at(2).Pos = { -1.0f,-1.0f,0.0f };
	mVertices.at(3).Pos = { 1.0f,-1.0f,0.0f };

	for(auto& vertex : mVertices)
	{
		XMFLOAT3 vec , normal;
		LCMath::CalcFloat3FromStartToGoal({ 0.0f,0.0f,0.0f } , vertex.Pos , vec);
		LCMath::CalcFloat3Normalize(vec , normal);

		vertex.Normal = normal;
		vertex.Color = mColor;
	}
}

void CPlaneMeshComponent::CreateIndexData()
{
	std::vector<unsigned int> indices = { 0 , 1 , 2 , 2 , 1 , 3 };

	mIndices = indices;
}