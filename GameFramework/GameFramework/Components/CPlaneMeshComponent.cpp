#include "CPlaneMeshComponent.h"

template<class VertexType>
CPlaneMeshComponent<VertexType>::CPlaneMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color ,
	std::string vertexShaderPath , std::string pixelShaderPath , bool isInit)
	:CPrimitiveMeshComponent<VertexType>(owner , parentTrans , color , vertexShaderPath , pixelShaderPath)
{
	if(isInit)this->Init(vertexShaderPath , pixelShaderPath);
}

void CPlaneMeshComponent<SVertexColor>::CreateVertexData()
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

void CPlaneMeshComponent<SVertexUV>::CreateVertexData()
{
	mVertices.resize(4);

	mVertices.at(0).Pos = { -1.0f,1.0f,0.0f };
	mVertices.at(1).Pos = { 1.0f,1.0f,0.0f };
	mVertices.at(2).Pos = { -1.0f,-1.0f,0.0f };
	mVertices.at(3).Pos = { 1.0f,-1.0f,0.0f };

	mVertices.at(0).Tex = { 0.0f,0.0f };
	mVertices.at(1).Tex = { 1.0f,0.0f };
	mVertices.at(2).Tex = { 0.0f,1.0f };
	mVertices.at(3).Tex = { 1.0f,1.0f };

	for(auto& vertex : mVertices)
	{
		XMFLOAT3 vec , normal;
		LCMath::CalcFloat3FromStartToGoal({ 0.0f,0.0f,0.0f } , vertex.Pos , vec);
		LCMath::CalcFloat3Normalize(vec , normal);

		vertex.Normal = normal;
	}
}

template<class VertexType>
void CPlaneMeshComponent<VertexType>::CreateIndexData()
{
	std::vector<unsigned int> indices = { 0 , 1 , 2 , 2 , 1 , 3 };

	this->mIndices = indices;
}

template class CPlaneMeshComponent<SVertexColor>;
template class CPlaneMeshComponent<SVertexUV>;