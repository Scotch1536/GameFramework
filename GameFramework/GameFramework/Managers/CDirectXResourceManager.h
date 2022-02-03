//!
//! @file
//! @brief DirectXリソースマネージャーのヘッダーファイル
//!

#pragma once
#include <unordered_map>

#include "../ExternalCode/CDirectxGraphics.h"

//! @brief DirectXリソースマネージャークラス
class CDirectXResourceManager
{
private:
	std::unordered_map<std::string , ComPtr<ID3D11Resource>> mTextureResource;				//!< テクスチャリソース
	std::unordered_map<std::string , ComPtr<ID3D11ShaderResourceView>> mTextureSRV;			//!< テクスチャSRV
	std::unordered_map<std::string , ComPtr<ID3D11VertexShader>> mVertexShader;				//!< 頂点シェーダ
	std::unordered_map<std::string , ComPtr<ID3D11PixelShader>> mPixelShader;				//!< ピクセルシェーダ
	std::unordered_map<std::string , ComPtr<ID3D11InputLayout>> mVertexLayout;				//!< 頂点レイアウト

	//! @brief コンストラクタ
	CDirectXResourceManager();

	//コピー＆ムーブ禁止
	CDirectXResourceManager(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager& operator=(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager(CDirectXResourceManager&&) = delete;
	CDirectXResourceManager& operator=(CDirectXResourceManager&&) = delete;

public:
	//!
	//! @brief インスタンス取得
	//! @return CDirectXResourceManager& インスタンス
	//!
	static CDirectXResourceManager& GetInstance();

	//!
	//! @brief テクスチャSRV取得（作成）
	//! @param[in] filePath 取得したいテクスチャSRVの元のファイルのパス
	//! @return ID3D11ShaderResourceView* テクスチャSRV
	//!
	ID3D11ShaderResourceView* GetTextureSRV(std::string filePath);

	//!
	//! @brief 頂点シェーダ取得（作成）
	//! @param[in] filePath 取得したい頂点シェーダの元のファイルのパス
	//! @return ID3D11VertexShader* 頂点シェーダ
	//!
	ID3D11VertexShader* GetVertexShader(std::string filePath);

	//!
	//! @brief ピクセルシェーダ取得（作成）
	//! @param[in] filePath 取得したいピクセルシェーダの元のファイルのパス
	//! @return ID3D11PixelShader* ピクセルシェーダ
	//!
	ID3D11PixelShader* GetPixelShader(std::string filePath);

	//!
	//! @brief 頂点レイアウト作成
	//! @param[in] layout 作成したい頂点レイアウトの内容（配列の先頭ポインタ）
	//! @param[in] layoutSize 頂点レイアウトの大きさ
	//! @param[in] vsFilePath 作成したい頂点レイアウトと紐づく頂点シェーダのファイルのパス
	//!
	void CreateVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

	//!
	//! @brief 頂点レイアウト取得
	//! @param[in] vsFilePath 取得したい頂点レイアウトと紐づく頂点シェーダのファイルのパス
	//! @return ID3D11InputLayout* 頂点レイアウト
	//!
	ID3D11InputLayout* GetVertexLayout(std::string vsFilePath);
	
	//!
	//! @brief 頂点レイアウト取得
	//! @details 頂点レイアウトがなければ作成も行う際に利用する
	//! @param[in] layout 取得したい頂点レイアウトの内容（配列の先頭ポインタ）
	//! @param[in] layoutSize 頂点レイアウトの大きさ
	//! @param[in] vsFilePath 作取得したい頂点レイアウトと紐づく頂点シェーダのファイルのパス
	//! @return ID3D11InputLayout* 頂点レイアウト
	//!
	ID3D11InputLayout* GetVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

};