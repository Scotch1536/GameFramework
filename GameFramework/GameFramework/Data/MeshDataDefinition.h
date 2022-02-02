//!
//! @file
//! @brief ���b�V���f�[�^��`�w�b�_�[�t�@�C��
//!

#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <string>

using namespace DirectX;

//! @brief �e�N�X�`��3D���b�V���p���_�\����
struct SVertexUV
{
	XMFLOAT3 Pos;			//!< �ʒu
	XMFLOAT3 Normal;		//!< �@��
	XMFLOAT2 Tex;			//!< UV���W
};

//! @brief �J���[3D���b�V���p���_�\����
struct SVertexColor
{
	XMFLOAT3 Pos;			//!< �ʒu
	XMFLOAT3 Normal;		//!< �@��
	XMFLOAT4 Color;			//!< �F���
};

//! @brief �����b�V���p���_�\����
struct SVertexLine
{
	XMFLOAT3 Pos;			//!< �ʒu
	XMFLOAT4 Color;			//!< �F���
};

//! @brief 2D���b�V���p���_�\����
struct SVertex2D
{
	XMFLOAT3 Pos;			//!< �ʒu
	XMFLOAT4 Color;			//!< �J���[
	XMFLOAT2 Tex;			//!< UV���W
};

//! @brief �}�e���A���\����
struct SMaterial
{
	float Alpha;			//!< �A���t�@
	XMFLOAT3 Diffuse;		//!< �f�B�t���[�Y
	XMFLOAT3 Specular;		//!< �X�y�L����
	float SpecularPower;	//!< �X�y�L�����p���[
	XMFLOAT3 Ambient;		//!< �A���r�G���g
	XMFLOAT3 Emissive;		//!< �G�~�b�V�u

	//! @brief �R���X�g���N�^
	SMaterial():Alpha(0) ,
		Diffuse(XMFLOAT3(0 , 0 , 0)) ,
		Specular(XMFLOAT3(0 , 0 , 0)) ,
		SpecularPower(0) ,
		Ambient(XMFLOAT3(0 , 0 , 0)) ,
		Emissive(XMFLOAT3(0 , 0 , 0))
	{}
};

//! @brief �}�e���A���萔�o�b�t�@�\����
struct SConstantBufferMaterial
{
	XMFLOAT4 AmbientMaterial;		//!< �A���r�G���g�}�e���A��
	XMFLOAT4 DiffuseMaterial;		//!< �f�B�t���[�Y�}�e���A��
	XMFLOAT4 SpecularMaterial;		//!< �X�y�L�����}�e���A��
};

//! @brief �e�N�X�`���\����
struct STexture
{
	std::string Type;				//!< �e�N�X�`���^�C�v
	std::string Path;				//!< �e�N�X�`���t�@�C���̃p�X

	ID3D11ShaderResourceView* TextureSRV;		//!< SRV
};