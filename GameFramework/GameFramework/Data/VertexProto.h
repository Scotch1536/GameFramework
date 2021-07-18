#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <string>

using namespace DirectX;

// 頂点
struct SVertexUV
{
	XMFLOAT3 Pos;			//位置
	XMFLOAT3 Normal;		//法線
	XMFLOAT2 Tex;			//UV座標
};

struct SVertexColor
{
	XMFLOAT3 Pos;		//位置
	XMFLOAT3 Normal;	//法線
	XMFLOAT4 Color;		//カラー
};

struct SVertex2D
{
	XMFLOAT3 Pos;		//位置
	XMFLOAT2 Tex;		//UV座標
};

// マテリアル
struct SMaterial
{
	float Alpha;
	XMFLOAT3 Diffuse;
	XMFLOAT3 Specular;
	float SpecularPower;
	XMFLOAT3 Ambient;
	XMFLOAT3 Emissive;

	SMaterial():Alpha(0) ,
		Diffuse(XMFLOAT3(0 , 0 , 0)) ,
		Specular(XMFLOAT3(0 , 0 , 0)) ,
		SpecularPower(0) ,
		Ambient(XMFLOAT3(0 , 0 , 0)) ,
		Emissive(XMFLOAT3(0 , 0 , 0))
	{}
};

// 定数バッファ定義（マテリアル）
struct SConstantBufferMaterial
{
	XMFLOAT4 AmbientMaterial;		// 環境光の反射率
	XMFLOAT4 DiffuseMaterial;		// ディフューズ光の反射率
	XMFLOAT4 SpecularMaterial;		// スペキュラ光の反射率
};

// テクスチャ構造体
struct STexture
{
	std::string Type;		// テクスチャ種類
	std::string Path;		// テクスチャパス名

	ID3D11ShaderResourceView* Texture;		// SRV
};