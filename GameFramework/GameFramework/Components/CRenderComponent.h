//!
//! @file
//! @brief レンダーコンポーネントのヘッダーファイル
//!

#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "../Data/MeshDataDefinition.h"

#include "CComponent.h"

using Microsoft::WRL::ComPtr;

//! @brief レンダーコンポーネントクラス
class CRenderComponent :public CComponent
{
private:
	ID3D11VertexShader* mVertexShader = nullptr;		//!< 頂点シェーダー
	ID3D11PixelShader* mPixelShader = nullptr;			//!< ピクセルシェーダー
	ID3D11InputLayout* mVertexLayout = nullptr;			//!< 頂点フォーマット

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] priority 優先度
	//!
	CRenderComponent(CActor& owner , int priority = 100);

	//!
	//! @brief 頂点シェーダ生成
	//! @param[in] layout 頂点フォーマット
	//! @param[in] layoutSize 頂点フォーマットの大きさ
	//! @param[in] vsFilePath 頂点シェーダのパス
	//!
	void GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

	//!
	//! @brief ピクセルシェーダ生成
	//! @param[in] psFilePath ピクセルシェーダのパス
	//!
	void GeneratePixelShader(std::string psFilePath);

	//!
	//! @brief ピクセルシェーダ生成
	//! @param[in] stride ストライド（頂点構造体のサイズ）
	//! @param[in] indexSize インデックスデータのサイズ
	//! @param[in] shaderResourceView シェーダリソースビュー
	//! @param[in] vertexBuffer 頂点バッファ
	//! @param[in] indexBuffer インデックスバッファ
	//! @param[in] materialCB マテリアル定数バッファ
	//!
	void Render(unsigned int stride,
		unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* materialCB);

};