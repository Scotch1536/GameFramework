#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "CComponent.h"
#include "VertexProto.h"

using Microsoft::WRL::ComPtr;

//�C���^�[�t�F�[�X
class IRender
{
public:
	virtual ~IRender() {};
	virtual void Render() = 0;
};

class CRenderComponent :public CComponent,IRender
{
protected:
	using CComponent::CComponent;

	unsigned int mIndexSize;
	ComPtr<ID3D11VertexShader> mVertexShader;			// ���_�V�F�[�_�[���ꕨ
	ComPtr<ID3D11PixelShader> mPixelShader;				// �s�N�Z���V�F�[�_�[���ꕨ
	ComPtr<ID3D11InputLayout> mVertexLayout;			// ���_�t�H�[�}�b�g��`

	//ComPtr<ID3D11Resource> mTexRes;						// �e�N�X�`�����\�[�X
	ComPtr<ID3D11ShaderResourceView> mTexture;			// SRV

	ComPtr<ID3D11Buffer>  mVertexBuffer;				// ���_�o�b�t�@
	ComPtr<ID3D11Buffer>  mIndexBuffer;					// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D11Buffer>  mCBMaterial;					// �}�e���A���p�R���X�^���g�o�b�t�@

public:
	void Render()override;
	void Update()override;
};