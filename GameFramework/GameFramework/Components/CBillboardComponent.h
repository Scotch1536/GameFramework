//!
//! @file
//! @brief ビルボードコンポーネントのヘッダーファイル
//!

#pragma once
#include "CPlaneMeshComponent.h"

//! @brief ビルボードコンポーネントクラス
class CBillboardComponent :public CPlaneMeshComponent<SVertexUV>
{
private:
	ID3D11ShaderResourceView* mTextureSRV;		//!< テクスチャSRV

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
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CBillboardComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
		std::string vertexShaderPath = "Shader/vs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	XMFLOAT2* GetUV(int index)
	{
		return &mVertices.at(index).Tex;
	};

};