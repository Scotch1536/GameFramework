//!
//! @file
//! @brief 平面コンポーネントのソースファイル
//!

#include "CPlaneMeshComponent.h"

template<class VertexType>
CPlaneMeshComponent<VertexType>::CPlaneMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
	std::string vertexShaderPath , std::string pixelShaderPath , bool isInit)
	:CPrimitiveMeshComponent<VertexType>(owner , parentTrans , color , vertexShaderPath , pixelShaderPath)
{
	//初期化
	if(isInit)this->Init(vertexShaderPath , pixelShaderPath);
}

void CPlaneMeshComponent<SVertexColor>::CreateVertexData()
{
	//頂点数の拡張と初期化
	mVertices.resize(4);

	mVertices.at(0).Pos = { -0.5f,0.5f,0.0f };
	mVertices.at(1).Pos = { 0.5f,0.5f,0.0f };
	mVertices.at(2).Pos = { -0.5f,-0.5f,0.0f };
	mVertices.at(3).Pos = { 0.5f,-0.5f,0.0f };

	for(auto& vertex : mVertices)
	{
		//法線の算出
		XMFLOAT3 vec , normal;
		LCMath::CalcFloat3FromStartToGoal({ 0.0f,0.0f,0.0f } , vertex.Pos , vec);
		LCMath::CalcFloat3Normalize(vec , normal);

		vertex.Normal = normal;
		vertex.Color = mColor;
	}
}

void CPlaneMeshComponent<SVertexUV>::CreateVertexData()
{
	//頂点数の拡張と初期化
	mVertices.resize(4);

	mVertices.at(0).Pos = { -0.5f,0.5f,0.0f };
	mVertices.at(1).Pos = { 0.5f,0.5f,0.0f };
	mVertices.at(2).Pos = { -0.5f,-0.5f,0.0f };
	mVertices.at(3).Pos = { 0.5f,-0.5f,0.0f };

	mVertices.at(0).Tex = { 0.0f,0.0f };
	mVertices.at(1).Tex = { 1.0f,0.0f };
	mVertices.at(2).Tex = { 0.0f,1.0f };
	mVertices.at(3).Tex = { 1.0f,1.0f };

	for(auto& vertex : mVertices)
	{
		//法線の算出
		XMFLOAT3 vec , normal;
		LCMath::CalcFloat3FromStartToGoal({ 0.0f,0.0f,0.0f } , vertex.Pos , vec);
		LCMath::CalcFloat3Normalize(vec , normal);

		vertex.Normal = normal;
	}
}

void CPlaneMeshComponent<SVertex2D>::CreateVertexData()
{
	//頂点数の拡張と初期化
	mVertices.resize(4);

	mVertices.at(0).Pos = { -0.5f,-0.5f,0.0f };
	mVertices.at(1).Pos = { 0.5f,-0.5f,0.0f };
	mVertices.at(2).Pos = { -0.5f,0.5f,0.0f };
	mVertices.at(3).Pos = { 0.5f,0.5f,0.0f };

	mVertices.at(0).Color = mColor;
	mVertices.at(1).Color = mColor;
	mVertices.at(2).Color = mColor;
	mVertices.at(3).Color = mColor;

	mVertices.at(0).Tex = { 0.0f,0.0f };
	mVertices.at(1).Tex = { 1.0f,0.0f };
	mVertices.at(2).Tex = { 0.0f,1.0f };
	mVertices.at(3).Tex = { 1.0f,1.0f };
}

template<class VertexType>
void CPlaneMeshComponent<VertexType>::CreateIndexData()
{
	std::vector<unsigned int> indices = { 0 , 1 , 2 , 2 , 1 , 3 };

	this->mIndices = indices;
}

template class CPlaneMeshComponent<SVertexColor>;
template class CPlaneMeshComponent<SVertexUV>;
template class CPlaneMeshComponent<SVertex2D>;