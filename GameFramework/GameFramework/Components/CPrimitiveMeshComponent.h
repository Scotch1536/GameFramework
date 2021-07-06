#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

#include "../Interfaces/IRender.h"
#include "../Data/VertexProto.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class CRenderComponent;

class CPrimitiveMeshComponent :public CComponent , public IRender
{
protected:
	ComPtr<ID3D11Buffer> mVertexBuffer;			//頂点バッファ
	ComPtr<ID3D11Buffer> mIndexBuffer;			//インデックスバッファ

	CRenderComponent& mRenderComponent;

	std::vector<SVertexColor> mVertices;		//頂点データ
	std::vector<unsigned int> mIndices;			//インデックスデータ

	XMFLOAT4 mColor;		//カラー

	bool isTranslucent = false;		//半透明かどうか

	virtual void CreateVertexData() = 0;
	virtual void CreateIndexData() = 0;

	void GenerateVertexAndIndexBuffer();

public:
	CTransform Transform;			//トランスフォーム

	CPrimitiveMeshComponent(CActor& owner , XMFLOAT4 color , std::string vertexShaderPath , std::string pixelShaderPath);

	void Update()override;
	void Render()override;

};