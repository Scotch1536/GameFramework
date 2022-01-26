#include "../Actor/CActor.h"

#include "../Library/LCMath.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

//!
//! @file
//! @brief スフィアメッシュコンポーネントのソースファイル
//!

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color , int divNum , float radius ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPrimitiveMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath) ,
	mRadius(radius) ,
	mDivisionNumber(divNum)
{
	//初期化
	Init(vertexShaderPath , pixelShaderPath);
}

void CSphereMeshComponent::CreateVertexData()
{
	float azimuth = 0.0f;			//方位角
	float elevation = 0.0f;			//仰角

	XMFLOAT3 Normal;

	//方位角と仰角から球メッシュの頂点データを作成
	for(int y = 0; y <= mDivisionNumber; ++y)
	{
		//仰角をセット
		elevation = (XM_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);

		//仰角に応じた半径を算出
		float r = mRadius * sinf(elevation);

		for(int x = 0; x <= mDivisionNumber; ++x)
		{
			//方位角をセット
			azimuth = (2 * XM_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);

			//頂点作成
			SVertexColor v;
			v.Pos.x = r * cosf(azimuth);
			v.Pos.y = mRadius * cosf(elevation);
			v.Pos.z = r * sinf(azimuth);
			v.Normal = v.Pos;
			v.Color = mColor;

			mVertices.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndexData()
{
	for(int y = 0; y < mDivisionNumber; ++y)
	{
		for(int x = 0; x < mDivisionNumber; ++x)
		{
			int count = (mDivisionNumber + 1)*y + x;

			//上半分
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + 1);
			mIndices.emplace_back(count + 1 + (mDivisionNumber + 1));

			//下半分
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + (mDivisionNumber + 1) + 1);
			mIndices.emplace_back(count + (mDivisionNumber + 1));
		}
	}
}
