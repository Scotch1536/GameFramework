#pragma once
#include <vector>
#include <DirectXMath.h>

#include "../Interfaces/IRender.h"
#include "../Data/VertexProto.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;

class CRenderComponent;

class CSphereMeshComponent :public CComponent , public IRender
{
private:
	// インデックスデータ
	struct Face
	{
		unsigned int idx[3];
	};

	ComPtr<ID3D11Buffer>  mVertexBuffer;		// 頂点バッファ
	ComPtr<ID3D11Buffer>  mIndexBuffer;			// インデックスバッファ

	CRenderComponent& mRenderComponent;

	std::vector<SVertexColor> mVertex;		//頂点データ
	std::vector<Face> mFace;				//インデックスデータ

	XMFLOAT4 mColor;

	float mRadius;
	int mDivisionNumber;

	bool isAlpha = false;

	void CreateVertex();
	void CreateIndex();

public:
	CTransform Transform;			//トランスフォーム

	CSphereMeshComponent(CActor& owner , float radius , int divNum , XMFLOAT4 color);

	void Update()override;

	void Render()override;
};