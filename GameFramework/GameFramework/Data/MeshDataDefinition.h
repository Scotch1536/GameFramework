//!
//! @file
//! @brief メッシュデータ定義ヘッダーファイル
//!

#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <string>

using namespace DirectX;

//! @brief テクスチャ3Dメッシュ用頂点構造体
struct SVertexUV
{
	XMFLOAT3 Pos;			//!< 位置
	XMFLOAT3 Normal;		//!< 法線
	XMFLOAT2 Tex;			//!< UV座標
};

//! @brief カラー3Dメッシュ用頂点構造体
struct SVertexColor
{
	XMFLOAT3 Pos;			//!< 位置
	XMFLOAT3 Normal;		//!< 法線
	XMFLOAT4 Color;			//!< 色情報
};

//! @brief 線メッシュ用頂点構造体
struct SVertexLine
{
	XMFLOAT3 Pos;			//!< 位置
	XMFLOAT4 Color;			//!< 色情報
};

//! @brief 2Dメッシュ用頂点構造体
struct SVertex2D
{
	XMFLOAT3 Pos;			//!< 位置
	XMFLOAT4 Color;			//!< カラー
	XMFLOAT2 Tex;			//!< UV座標
};

//! @brief マテリアル構造体
struct SMaterial
{
	float Alpha;			//!< アルファ
	XMFLOAT3 Diffuse;		//!< ディフューズ
	XMFLOAT3 Specular;		//!< スペキュラ
	float SpecularPower;	//!< スペキュラパワー
	XMFLOAT3 Ambient;		//!< アンビエント
	XMFLOAT3 Emissive;		//!< エミッシブ

	//! @brief コンストラクタ
	SMaterial():Alpha(0) ,
		Diffuse(XMFLOAT3(0 , 0 , 0)) ,
		Specular(XMFLOAT3(0 , 0 , 0)) ,
		SpecularPower(0) ,
		Ambient(XMFLOAT3(0 , 0 , 0)) ,
		Emissive(XMFLOAT3(0 , 0 , 0))
	{}
};

//! @brief マテリアル定数バッファ構造体
struct SConstantBufferMaterial
{
	XMFLOAT4 AmbientMaterial;		//!< アンビエントマテリアル
	XMFLOAT4 DiffuseMaterial;		//!< ディフューズマテリアル
	XMFLOAT4 SpecularMaterial;		//!< スペキュラマテリアル
};

//! @brief テクスチャ構造体
struct STexture
{
	std::string Type;				//!< テクスチャタイプ
	std::string Path;				//!< テクスチャファイルのパス

	ID3D11ShaderResourceView* TextureSRV;		//!< SRV
};