#pragma once

#include "../Interfaces/IRender.h"
#include "CComponent.h"
#include <DirectXMath.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
#include "../ExternalCode/Shader.h"

using Microsoft::WRL::ComPtr;

class CLineComponent :public CComponent, public IRender
{
private:
	ComPtr<ID3D11Buffer>		mVertexBuffer;			// 頂点バッファ
	ComPtr<ID3D11PixelShader>	mPixelShader;				// ピクセルシェーダー
	ComPtr<ID3D11VertexShader>	mVertexShader;				// 頂点シェーダー
	ComPtr<ID3D11InputLayout>   mLayout;			// 頂点フォーマット定義
	size_t						mVertexSize;			// 頂点数
	std::vector<XMFLOAT3>       mVertices;
	XMFLOAT4		mColor = {1.0f,1.0f,1.0f,1.0f};
	CTransform* mOwnerTransform;

	bool mShouldUpdate = true;

	void Init(std::string vertexShaderPath, std::string pixelShaderPath);

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}
public:

	CLineComponent(CActor& owner,XMFLOAT3 vertex1, XMFLOAT3 vertex2,
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }, CTransform* parentTrans=nullptr,
		std::string vertexShaderPath="Shader/vsline.hlsl", 
		std::string pixelShaderPath = "Shader/psline.hlsl", int priority = 90);

	//頂点セット
	//void SetVertex(std::vector<XMFLOAT3>& v);

	//カラーセット
	void SetColor(XMFLOAT4 color) { mColor = color; }

	//描画
	void Render()override;

	//更新
	void Update()override;
};