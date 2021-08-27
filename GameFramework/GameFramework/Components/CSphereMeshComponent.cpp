#include "../Actor/CActor.h"
#include "../ExternalCode/dx11mathutil.h"

#include "../Library/LCMath.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color , int divNum , float radius ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPrimitiveMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath) ,
	mRadius(radius) ,
	mDivisionNumber(divNum)
{
	Init(vertexShaderPath , pixelShaderPath);
}

void CSphereMeshComponent::CreateVertexData()
{
	float azimuth = 0.0f;			// 方位角
	float elevation = 0.0f;			// 仰角

	XMFLOAT3 Normal;

	// 方位角と仰角から球メッシュの頂点データを作成
	for(int y = 0; y <= mDivisionNumber; ++y)
	{
		elevation = (XM_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);		// 仰角をセット

		float r = mRadius * sinf(elevation);			// 仰角に応じた半径を計算

		for(int x = 0; x <= mDivisionNumber; ++x)
		{
			azimuth = (2 * XM_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);		// 方位角をセット

			SVertexColor v;
			v.Pos.x = r * cosf(azimuth);
			v.Pos.y = mRadius * cosf(elevation);
			v.Pos.z = r * sinf(azimuth);

			XMFLOAT3 normVec;
			LCMath::CalcFloat3FromStartToGoal({ 0.0f,0.0f,0.0f } , v.Pos , normVec);

			DX11Vec3Normalize(Normal , normVec);		// 法線を計算
			v.Normal = Normal;							// 法線をセット

			v.Color = mColor;				// 頂点カラー

			mVertices.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndexData()
{
	// インデックス生成
	for(int y = 0; y < mDivisionNumber; ++y)
	{
		for(int x = 0; x < mDivisionNumber; ++x)
		{
			int count = (mDivisionNumber + 1)*y + x;		// 左上座標のインデックス

			// 上半分
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + 1);
			mIndices.emplace_back(count + 1 + (mDivisionNumber + 1));

			// 下半分
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + (mDivisionNumber + 1) + 1);
			mIndices.emplace_back(count + (mDivisionNumber + 1));
		}
	}
}
