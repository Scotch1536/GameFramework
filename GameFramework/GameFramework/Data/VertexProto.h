#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <string>

using namespace DirectX;

// ���_
struct SVertexUV
{
	XMFLOAT3 Pos;			//�ʒu
	XMFLOAT3 Normal;		//�@��
	XMFLOAT2 Tex;			//UV���W
};

struct SVertexColor
{
	XMFLOAT3 Pos;		//�ʒu
	XMFLOAT3 Normal;	//�@��
	XMFLOAT4 Color;		//�J���[
};

struct SVertexLine
{
	XMFLOAT3 Pos;       //�ʒu
	XMFLOAT4 Color;		//�J���[
};

struct SVertex2D
{
	XMFLOAT3 Pos;		//�ʒu
	XMFLOAT4 Color;		//�J���[
	XMFLOAT2 Tex;		//UV���W
};

// �}�e���A��
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

// �萔�o�b�t�@��`�i�}�e���A���j
struct SConstantBufferMaterial
{
	XMFLOAT4 AmbientMaterial;		// �����̔��˗�
	XMFLOAT4 DiffuseMaterial;		// �f�B�t���[�Y���̔��˗�
	XMFLOAT4 SpecularMaterial;		// �X�y�L�������̔��˗�
};

// �e�N�X�`���\����
struct STexture
{
	std::string Type;		// �e�N�X�`�����
	std::string Path;		// �e�N�X�`���p�X��

	ID3D11ShaderResourceView* Texture;		// SRV
};