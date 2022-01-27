//!
//! @file
//! @brief ディスプレイ2Dコンポーネントのヘッダーファイル
//!

#pragma once
#include "CPlaneMeshComponent.h"

//! @brief ディスプレイ2Dコンポーネントクラス
class CDisplay2DComponent :public CPlaneMeshComponent<SVertex2D>
{
private:
	ID3D11ShaderResourceView* mTextureSRV = nullptr;		//!< テクスチャSRV

	//!
	//! @brief 初期化
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	void Init(std::string vertexShaderPath , std::string pixelShaderPath)override;

	//! @brief 更新
	void Update()override;

	//! @brief 描画
	void Render()override;

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] texturePath テクスチャファイルのパス
	//! @param[in] color 色情報
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath , const XMFLOAT4& color,
		std::string vertexShaderPath = "Shader/basicvs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	//!
	//! @brief コンストラクタ
	//! @details テクスチャがない場合のコンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] color 色情報
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CDisplay2DComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
		std::string vertexShaderPath = "Shader/basicvs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	//!
	//! @brief UV情報の取得
	//! @details アニメーション機能を付けたい時などに使用することを想定
	//! @param[in] index 頂点配列のインデックス
	//!
	XMFLOAT2* GetUV(int index);

};