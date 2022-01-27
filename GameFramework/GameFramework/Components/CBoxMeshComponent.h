//!
//! @file
//! @brief ボックスメッシュコンポーネントのヘッダーファイル
//!

#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

class CBoxMeshComponent :public CPrimitiveMeshComponent<>
{
private:
	XMFLOAT3 mMin , mMax;		//!< 原点と頂点との間の長さの最小最大値

	//! @brief 頂点データ作成
	void CreateVertexData()override;

	//! @brief インデックスデータ作成
	void CreateIndexData()override;

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] color 色情報
	//! @param[in] min 最小値
	//! @param[in] max 最大値
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CBoxMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } ,
		XMFLOAT3 min = { -0.5f,-0.5f,-0.5f } , XMFLOAT3 max = { 0.5f,0.5f,0.5f } ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");
};