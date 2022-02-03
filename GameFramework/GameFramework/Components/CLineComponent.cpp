//!
//! @file
//! @brief ラインコンポーネントのソースファイル
//!

#include "../Actor/CActor.h"
#include "../Managers/CDirectXResourceManager.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/Shader.h"
#include "../Library/LCMath.h"

#include "CLineComponent.h"

CLineComponent::CLineComponent(CActor& owner , const XMFLOAT3& start , const XMFLOAT3& end ,
	const XMFLOAT4& color , CTransform* parentTrans , std::string vertexShaderPath ,
	std::string pixelShaderPath , int priority):CComponent(owner , priority) ,
	mStartPoint(start) , mEndPoint(end) , mColor(color) , mParentTransform(parentTrans)
{
	//頂点初期化
	mVertices.at(0).Pos = mStartPoint;
	mVertices.at(1).Pos = mEndPoint;
	mVertices.at(0).Color = mVertices.at(1).Color = mColor;

	//初期化
	Init(vertexShaderPath , pixelShaderPath);
}

CLineComponent::CLineComponent(CActor& owner , const XMFLOAT3& start , const XMFLOAT3& direction , float length ,
	const XMFLOAT4& color , CTransform* parentTrans , std::string vertexShaderPath ,
	std::string pixelShaderPath , int priority):CComponent(owner , priority) ,
	mStartPoint(start) , mColor(color) , mParentTransform(parentTrans)
{
	XMFLOAT3 dire = direction;

	//正規化
	LCMath::CalcFloat3Normalize(dire , dire);

	//頂点初期化
	mVertices.at(0).Pos = mStartPoint;
	mVertices.at(1).Pos = mEndPoint = LCMath::CalcFloat3Scalar(dire , length);
	mVertices.at(0).Color = mVertices.at(1).Color = mColor;

	//初期化
	Init(vertexShaderPath , pixelShaderPath);
}

void CLineComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	CDirectXResourceManager& buf = CDirectXResourceManager::GetInstance();

	mVertexShader = buf.GetVertexShader(vertexShaderPath);
	mVertexLayout = buf.GetVertexLayout(layout , numElements , vertexShaderPath);
	mPixelShader = buf.GetPixelShader(pixelShaderPath);

	//頂点バッファ作成
	CreateVertexBufferWrite(CDirectXGraphics::GetInstance()->GetDXDevice() ,
		sizeof(SVertexLine) , mVertices.size() , mVertices.data() , mVertexBuffer.GetAddressOf());

	//親のトランスフォームが存在するなら
	if(mParentTransform != nullptr)
	{
		//トランスフォームの行列更新時イベントに自身のメソッドを追加
		mParentTransform->AddEventWhenMatrixUpdate(std::bind(&CLineComponent::SetShouldUpdate , std::ref(*this) , true));
	}
}

void CLineComponent::Render()
{
	ID3D11DeviceContext* devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	//頂点バッファをセットする
	unsigned int stride = sizeof(SVertexLine);
	unsigned offset = 0;
	devcontext->IASetVertexBuffers(0 , 1 , mVertexBuffer.GetAddressOf() , &stride , &offset);		//頂点バッファセット

	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);			//トポロジーをセット（旧プリミティブタイプ）
	devcontext->IASetInputLayout(mVertexLayout.Get());								//頂点レイアウトセット

	devcontext->VSSetShader(mVertexShader.Get() , nullptr , 0);			//頂点シェーダーをセット
	devcontext->PSSetShader(mPixelShader.Get() , nullptr , 0);			//ピクセルシェーダーをセット

	devcontext->Draw(2 , 0);		//ドローコール
}

void CLineComponent::Update()
{
	if(mShouldUpdate)
	{
		//親のトランスフォームがあるなら
		if(mParentTransform != nullptr)
		{
			mShouldUpdate = false;

			XMFLOAT3 scale = mParentTransform->GetWorldScale();						//親のトランスフォームのワールドのスケール情報取得
			XMFLOAT4X4 resultMTX = mParentTransform->GetWorldMatrix();		//親のトランスフォームのワールド変換行列取得
			XMFLOAT4X4 scaleMTX;

			DX11MtxScale(scale.x , scale.y , scale.z , scaleMTX);				//スケール行列作成
			LCMath::InverseMatrix(scaleMTX , scaleMTX);							//スケール行列を逆行列化する
			LCMath::CalcMatrixMultply(resultMTX , scaleMTX , resultMTX);		//親のトランスフォームのワールド変換行列からスケール情報のみ除外する

			std::vector<SVertexLine> vertices;

			for(auto& v : mVertices)
			{
				SVertexLine vertex;
				LCMath::CalcFloat3MultplyMatrix(v.Pos , resultMTX , vertex.Pos);		//頂点をワールド変換する
				vertex.Color = mColor;
				vertices.emplace_back(vertex);
			}

			//頂点バッファ更新
			UpdateVertex(vertices.data() , vertices.size());
		}
		else
		{
			//頂点バッファ更新
			UpdateVertex(mVertices.data() , mVertices.size());
		}
	}

	//描画命令追加
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPACITY3D });
}

void CLineComponent::UpdateVertex(void* source , int size)
{
	D3D11_MAPPED_SUBRESOURCE pData;

	//頂点バッファを更新
	HRESULT hr = CDirectXGraphics::GetInstance()->GetImmediateContext()->Map(mVertexBuffer.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &pData);
	if(SUCCEEDED(hr))
	{
		memcpy_s(pData.pData , pData.RowPitch , source , sizeof(SVertexLine) * size);
		CDirectXGraphics::GetInstance()->GetImmediateContext()->Unmap(mVertexBuffer.Get() , 0);
	}
}
