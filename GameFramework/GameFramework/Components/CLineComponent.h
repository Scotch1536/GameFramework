#pragma once

#include <array>
#include <string>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <d3d11.h>

#include "../Interfaces/IRender.h"
#include "../Data/VertexProto.h"
#include "CComponent.h"

//!
//! @file
//! @brief ラインコンポーネントのヘッダーファイル
//!

using Microsoft::WRL::ComPtr;

//! @brief ラインコンポーネントクラス
class CLineComponent :public CComponent , public IRender
{
private:
	ComPtr<ID3D11Buffer> mVertexBuffer;				//!< 頂点バッファ
	ComPtr<ID3D11PixelShader> mPixelShader;			//!< ピクセルシェーダー
	ComPtr<ID3D11VertexShader> mVertexShader;		//!< 頂点シェーダー
	ComPtr<ID3D11InputLayout> mVertexLayout;		//!< 頂点フォーマット定義

	std::array<SVertexLine , 2> mVertices;		//!< 頂点

	XMFLOAT3 mStartPoint;						//!< 始点
	XMFLOAT3 mEndPoint;							//!< 終点
	XMFLOAT4 mColor;							//!< 色

	//! @brief 親のトランスフォーム
	//! @details 適用したトランスフォームのワールド変換行列にスケーリングのみ除外した
	//! 変換が施されるので扱いに注意が必要
	CTransform* mParentTransform;

	bool mShouldUpdate = false;			//!< 更新すべきか

	//!
	//! @brief 初期化
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	void Init(std::string vertexShaderPath , std::string pixelShaderPath);

	//! @brief 描画
	void Render()override;

	//! @brief 更新
	void Update()override;

	//!
	//! @brief 頂点の更新
	//! @param[in] 
	void UpdateVertex(void* source , int size);

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

public:
	//!
	//! @brief コンストラクタ
	//! @details 始点と終点を結んだ線を作る場合のコンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] start 始点
	//! @param[in] end 終点
	//! @param[in] color 色情報
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//! @param[in] priority 優先度
	//!
	CLineComponent(CActor& owner , const XMFLOAT3& start ,const XMFLOAT3& end ,
		const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } , CTransform* parentTrans = nullptr ,
		std::string vertexShaderPath = "Shader/vsline.hlsl" , std::string pixelShaderPath = "Shader/psline.hlsl" , int priority = 90);

	//!
	//! @brief コンストラクタ
	//! @details 始点からの向きと長さで線を作る場合のコンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] start 始点
	//! @param[in] direction 向き
	//! @param[in] length 長さ
	//! @param[in] color 色情報
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//! @param[in] priority 優先度
	//!
	CLineComponent(CActor& owner ,const XMFLOAT3& start ,const XMFLOAT3& direction , float length ,
		const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } , CTransform* parentTrans = nullptr ,
		std::string vertexShaderPath = "Shader/vsline.hlsl" , std::string pixelShaderPath = "Shader/psline.hlsl" , int priority = 90);

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

	void SetColor(XMFLOAT4 color)
	{
		mVertices.at(0).Color = mVertices.at(1).Color = mColor = color;
	}
};