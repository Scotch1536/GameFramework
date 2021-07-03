#define _USE_MATH_DEFINES
#include <cmath>

#include "../Actor/CActor.h"
#include "../ExternalCode/dx11mathutil.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , float radius , int divNum , XMFLOAT4 color)
	:CComponent(owner , 0) ,
	mRenderComponent(*new CRenderComponent(owner)) ,
	mColor(color) ,
	mRadius(radius) ,
	mDivisionNumber(divNum)
{
	//アクター(owner)にレンダー担当のコンポーネントとして登録
	mOwnerInterface.RegisterRenderComponent(*this);

	CreateVertex();
	CreateIndex();

}

void CSphereMeshComponent::CreateVertex()
{
	float azimuth = 0.0f;			// 方位角
	float elevation = 0.0f;			// 仰角

	XMFLOAT3 Normal;

	// 方位角と仰角から球メッシュの頂点データを作成
	for(unsigned int y = 0; y <= mDivisionNumber; y++)
	{
		elevation = (M_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);		// 仰角をセット

		float r = mRadius * sinf(elevation);					// 仰角に応じた半径を計算

		for(unsigned int x = 0; x <= mDivisionNumber; x++)
		{
			azimuth = (2 * M_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);		// 方位角をセット

			VertexColor v;
			v.m_Pos.x = r * cosf(azimuth);
			v.m_Pos.y = mRadius * cosf(elevation);
			v.m_Pos.z = r * sinf(azimuth);

			DX11Vec3Normalize(v.m_Pos , Normal);			// 法線を計算
			v.m_Normal = Normal;							// 法線をセット

			v.m_Color = mColor;				// 頂点カラー

			mVertex.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndex()
{
	// インデックス生成
	for(unsigned int y = 0; y < mDivisionNumber; y++)
	{
		for(unsigned int x = 0; x < mDivisionNumber; x++)
		{
			int count = (mDivisionNumber + 1)*y + x;			// 左上座標のインデックス

			Face f;
			// 上半分
			f.idx[0] = count;
			f.idx[1] = count + 1;
			f.idx[2] = count + 1 + (mDivisionNumber + 1);

			mFace.emplace_back(f);

			// 下半分
			f.idx[0] = count;
			f.idx[1] = count + (mDivisionNumber + 1) + 1;
			f.idx[2] = count + (mDivisionNumber + 1);

			mFace.emplace_back(f);
		}
	}
}