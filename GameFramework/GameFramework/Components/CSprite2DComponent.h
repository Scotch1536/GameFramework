#pragma once
#include <string>

#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../Interfaces/IRender.h"

#include "CComponent.h"

class CRenderComponent;

class CSprite2DComponent :public CComponent,public IRender
{
private:

	// 頂点構造体
	typedef struct {
		XMFLOAT3 pos; // 座標		
		XMFLOAT4 color; // カラー
		XMFLOAT2 tex; // テクスチャ;
	}Vertex;

	XMFLOAT2 mUv[4]; //角度
	XMFLOAT4 mColor = { 1.0f, 1.0f, 1.0f, 1.0f }; //色
	float mAngle;
	ComPtr<ID3D11Buffer> mVertexBuffer = nullptr; // 頂点バッファ
	ComPtr<ID3D11Buffer> mIndexBuffer = nullptr; // インデックスバッファ
	Vertex mVertex[4]; // 矩形４頂点
	XMFLOAT4X4 mWorldmtx; // ワールド変換行列
public:
	XMFLOAT2 mPos;			//座標
	XMFLOAT2 mBreadth;		//幅 x:width y:height
	CSprite2DComponent(CActor& owner, std::string fileName, int priority = 45);

	void Update()override;

	void Render()override;
};