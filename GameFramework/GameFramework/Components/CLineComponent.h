#pragma once

#include "../Interfaces/IRender.h"
#include "CComponent.h"
#include <DirectXMath.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <array>
#include "../ExternalCode/Shader.h"
#include "../Data/VertexProto.h"

using Microsoft::WRL::ComPtr;

class CLineComponent :public CComponent, public IRender
{
private:
	ComPtr<ID3D11Buffer> mVertexBuffer;				// 頂点バッファ
	ComPtr<ID3D11PixelShader> mPixelShader;			// ピクセルシェーダー
	ComPtr<ID3D11VertexShader> mVertexShader;		// 頂点シェーダー
	ComPtr<ID3D11InputLayout> mLayout;				// 頂点フォーマット定義

	std::array<SVertexLine, 2> mVertices;

	XMFLOAT3 mStartPoint;
	XMFLOAT3 mEndPoint;
	XMFLOAT4 mColor;

	CTransform* mOwnerTransform;

	bool mShouldUpdate = true;
	
	void Init(std::string vertexShaderPath, std::string pixelShaderPath);

	void UpdateVertex(void* source, int size);

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}
public:

	CLineComponent(CActor& owner,XMFLOAT3 vertex1, XMFLOAT3 vertex2,
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }, CTransform* parentTrans=nullptr,
		std::string vertexShaderPath="Shader/vsline.hlsl", 
		std::string pixelShaderPath = "Shader/psline.hlsl", int priority = 90);

	CLineComponent(CActor& owner,XMFLOAT3 start, XMFLOAT3 direction,float length,
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }, CTransform* parentTrans=nullptr,
		std::string vertexShaderPath="Shader/vsline.hlsl", 
		std::string pixelShaderPath = "Shader/psline.hlsl", int priority = 90);

	//ポイント座標セット
	void SetStartPoint(const XMFLOAT3& point)
	{
		mShouldUpdate = true;

		mVertices.at(0).Pos = mStartPoint = point;
	}

	void SetEndPoint(const XMFLOAT3& point)
	{
		mShouldUpdate = true;

		mVertices.at(1).Pos = mEndPoint = point;
	}	

	//カラーセット
	void SetColor(XMFLOAT4 color) 
	{ 
		mColor = color; 
	}

	//描画
	void Render()override;

	//更新
	void Update()override;
};