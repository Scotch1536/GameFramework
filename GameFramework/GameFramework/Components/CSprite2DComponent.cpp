#include "CSprite2DComponent.h"
#include "../ExternalCode/shaderhashmap.h"

CSprite2DComponent::CSprite2DComponent(CActor& owner, std::string fileName, int priority) :CComponent(owner, priority)
{
	// 使用する頂点シェーダー名
	const char* vsfilename[] = {
		"shader/basicvs.hlsl"
	};

	// 使用するピクセルシェーダー名
	const char* psfilename[] = {
		"shader/basicps.hlsl", //テクスチャ貼る用
		"shader/basicnotexps.hlsl" //テクスチャ貼らない用
	};

	// デバイスを取得する
	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

	DX11MtxIdentity(mWorldmtx); // 初期姿勢

	// ピクセルシェーダーを生成
	bool sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error(basicps.hlsl)", "error", MB_OK);
		return;
	}

	// ピクセルシェーダーを生成
	sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename[1]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error(basicnotexps.hlsl)", "error", MB_OK);
		return;
	}

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// エレメント数
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーを生成
	sts = ShaderHashmap::GetInstance()->SetVertexShader(vsfilename[0], layout, numElements);
	// 第1引数：頂点シェーダーファイル名
	// 第2引数：頂点レイアウト
	// 第3引数：エレメント数

// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	sts = CreateVertexBufferWrite(device, sizeof(Vertex), 4, mVertex, &(mVertexBuffer));
	// 第1引数：デバイスオブジェクト
	// 第2引数：1頂点当たりバイト数
	// 第3引数：頂点数
	// 第4引数：頂点データ格納メモリ先頭アドレス
	// 第5引数：頂点バッファ

	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return;
	}

	// インデックスバッファを生成
	uint32_t index[4] = { 0,1,2,3 };
	sts = CreateIndexBuffer(device, 4, index, &(mIndexBuffer));
	// 第1引数：デバイスオブジェクト
	// 第2引数：インデックス数
	// 第3引数：インデックス格納メモリ先頭アドレス
	// 第4引数：インデックスバッファ

	if (!sts) {
		MessageBox(nullptr, "CreateIndexBuffer error", "error", MB_OK);
		return;
	}

	//UV座標初期値代入
	mUv[0].x = 0.0f;
	mUv[0].y = 0.0f;
	mUv[1].x = 1.0f;
	mUv[1].y = 0.0f;
	mUv[2].x = 0.0f;
	mUv[2].y = 1.0f;
	mUv[3].x = 1.0f;
	mUv[3].y = 1.0f;
}

void CSprite2DComponent::Update()
{
	// Z軸回転
	DX11MtxRotationZ(mAngle, mWorldmtx);

	// 位置をセット
	mWorldmtx._41 = mPos.x;
	mWorldmtx._42 = mPos.y;
	mWorldmtx._43 = 0;

	// 頂点データ更新
	Vertex	v[4] = {
		// 座標                                             // カラー    // UV	
		XMFLOAT3(-mBreadth.x / 2.0f,-mBreadth.y / 2.0f, 0), mColor, mUv[0],
		XMFLOAT3( mBreadth.x / 2.0f,-mBreadth.y / 2.0f, 0), mColor, mUv[1],
		XMFLOAT3(-mBreadth.x / 2.0f, mBreadth.y / 2.0f, 0), mColor, mUv[2],
		XMFLOAT3( mBreadth.x / 2.0f, mBreadth.y / 2.0f, 0), mColor, mUv[3]
	};

	for (int i = 0; i < 4; i++) {
		mVertex[i] = v[i];
	}

	// 頂点バッファ更新
	D3D11_MAPPED_SUBRESOURCE pData;
	ID3D11DeviceContext* devcontext;
	devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();
	HRESULT hr = devcontext->Map(mVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(mVertex), sizeof(Vertex) * 4);
		devcontext->Unmap(mVertexBuffer.Get(), 0);
	}
}