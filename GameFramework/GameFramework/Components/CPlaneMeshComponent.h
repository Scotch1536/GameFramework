#pragma once
#include "CPrimitiveMeshComponent.h"

//!
//! @file
//! @brief 平面コンポーネントのヘッダーファイル
//!

//! @brief 平面コンポーネントクラス
template<class VertexType = SVertexColor>
class CPlaneMeshComponent :public CPrimitiveMeshComponent<VertexType>
{
protected:
	//! @brief 頂点データ作成
	void CreateVertexData()override;

	//! @brief インデックスデータ作成
	void CreateIndexData()override;

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] parentTans 親のトランスフォーム
	//! @param[in] color 色情報
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CPlaneMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl" , bool isInit = true);

};