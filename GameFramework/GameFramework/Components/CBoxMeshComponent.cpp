//!
//! @file
//! @brief ボックスメッシュコンポーネントのソースファイル
//!

#include "../Library/LCMath.h"

#include "CBoxMeshComponent.h"

CBoxMeshComponent::CBoxMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color ,
	XMFLOAT3 min , XMFLOAT3 max ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPrimitiveMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath) ,
	mMin(min) , mMax(max)
{
	//初期化
	Init(vertexShaderPath , pixelShaderPath);
}

void CBoxMeshComponent::CreateVertexData()
{
	//頂点数の拡張と初期化
	mVertices.resize(8);
	mVertices.at(0).Pos = { mMin.x,mMax.y,mMin.z };
	mVertices.at(1).Pos = { mMax.x,mMax.y,mMin.z };
	mVertices.at(2).Pos = { mMax.x,mMax.y,mMax.z };
	mVertices.at(3).Pos = { mMin.x,mMax.y,mMax.z };
	mVertices.at(4).Pos = { mMin.x,mMin.y,mMax.z };
	mVertices.at(5).Pos = { mMax.x,mMin.y,mMax.z };
	mVertices.at(6).Pos = { mMax.x,mMin.y,mMin.z };
	mVertices.at(7).Pos = { mMin.x,mMin.y,mMin.z };

	for(auto& vertex : mVertices)
	{
		XMFLOAT3 vec , normal;

		//法線の算出
		LCMath::CalcFloat3FromStartToEnd({ 0.0f,0.0f,0.0f } , vertex.Pos , vec);
		LCMath::CalcFloat3Normalize(vec , normal);

		vertex.Normal = normal;
		vertex.Color = mColor;
	}
}

void CBoxMeshComponent::CreateIndexData()
{
	//インデックスデータ作成
	std::vector<unsigned int> indices =
	{
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		3,2,5,3,5,4,
		2,1,6,2,6,5,
		1,7,6,1,0,7,
		0,3,4,0,4,7
	};

	mIndices = indices;
}
