#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

//!
//! @file
//! @brief スフィアメッシュコンポーネントのヘッダーファイル
//!

//! @brief スフィアメッシュコンポーネントクラス
class CSphereMeshComponent :public CPrimitiveMeshComponent<>
{
private:
	float mRadius;				//!< 半径
	int mDivisionNumber;		//!< 分割数

	//! @brief 頂点データ作成
	void CreateVertexData()override;

	//! @brief インデックスデータ作成
	void CreateIndexData()override;

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] color 色情報
	//! @param[in] divNum 分割数
	//! @param[in] radius 半径
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CSphereMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } , int divNum = 50 , float radius = 0.5f ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");
};