#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <string>

//using Microsoft::WRL::ComPtr;

// 頂点
struct VertexUV {
	DirectX::XMFLOAT3 m_Pos;		//位置
	DirectX::XMFLOAT3 m_Normal;		//法線
	DirectX::XMFLOAT2 m_Tex;		//UV座標
};

struct VertexColor {
	DirectX::XMFLOAT3 m_Pos;		//位置
	DirectX::XMFLOAT3 m_Normal;		//法線
	DirectX::XMFLOAT4 m_Color;		//カラー
};

// マテリアル
struct Material {
	float m_Alpha;
	DirectX::XMFLOAT3 m_Diffuse;
	DirectX::XMFLOAT3 m_Specular;
	float	m_SpecularPower;
	DirectX::XMFLOAT3 m_Ambient;
	DirectX::XMFLOAT3 m_Emissive;

	Material()
		: m_Alpha(0),
		m_Diffuse(DirectX::XMFLOAT3(0, 0, 0)),
		m_Specular(DirectX::XMFLOAT3(0, 0, 0)),
		m_SpecularPower(0),
		m_Ambient(DirectX::XMFLOAT3(0, 0, 0)),
		m_Emissive(DirectX::XMFLOAT3(0, 0, 0))
	{
	}
};

// 定数バッファ定義（マテリアル）
struct ConstantBufferMaterial {
	DirectX::XMFLOAT4	AmbientMaterial;		// 環境光の反射率
	DirectX::XMFLOAT4	DiffuseMaterial;		// ディフューズ光の反射率
	DirectX::XMFLOAT4	SpecularMaterial;		// スペキュラ光の反射率
};

// テクスチャ構造体
struct Texture
{
	std::string type;		// テクスチャ種類
	std::string path;		// テクスチャパス名

	ID3D11Resource* texres;					// テクスチャリソース
	ID3D11ShaderResourceView* texture;		// SRV
};