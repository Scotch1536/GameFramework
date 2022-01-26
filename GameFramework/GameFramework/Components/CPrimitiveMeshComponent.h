#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <string>

#include "../Interfaces/IRender.h"
#include "../Data/VertexProto.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

//!
//! @file
//! @brief プリミティブメッシュコンポーネントのヘッダーファイル
//!

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class CRenderComponent;

//! @brief プリミティブメッシュコンポーネントクラス
template<class VertexType = SVertexColor>
class CPrimitiveMeshComponent :public CComponent , public IRender
{
protected:
	ComPtr<ID3D11Buffer> mVertexBuffer;			//!< 頂点バッファ
	ComPtr<ID3D11Buffer> mIndexBuffer;			//!< インデックスバッファ

	CRenderComponent& mRenderComponent;			//!< レンダーコンポーネント

	std::vector<VertexType> mVertices;			//!< 頂点データ
	std::vector<unsigned int> mIndices;			//!< インデックスデータ

	XMFLOAT4 mColor;							//!< 色情報

	bool mIsTranslucent = false;				//!< 半透明かどうか

	//!
	//! @brief 初期化
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	virtual void Init(std::string vertexShaderPath , std::string pixelShaderPath);

	//! @brief 頂点データ作成
	virtual void CreateVertexData() = 0;

	//! @brief インデックスデータ作成
	virtual void CreateIndexData() = 0;

	//! @brief 頂点&インデックスバッファ生成
	void GenerateVertexAndIndexBuffer();

	//! @brief 不透明かどうかのチェック
	void CheckTranslucent()
	{
		//アルファ値が1未満なら
		if(mColor.w < 1.0f)
		{
			mIsTranslucent = true;
		}
	}

	//! @brief 更新
	void Update()override;

	//! @brief 描画
	void Render()override;

public:
	CTransform Transform;			//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] color 色情報
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CPrimitiveMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color , std::string vertexShaderPath , std::string pixelShaderPath);

	//! @brief 頂点バッファ更新
	void UpdateVertexBuffer();

	const XMFLOAT4& GetColor()const
	{
		return mColor;
	}

	void SetColor(const XMFLOAT4& color);

};