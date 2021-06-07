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

//�����_�[�R���|�[�l���g�N���X
class CRenderComponent :public CComponent , IRender
{
protected:
	unsigned int mIndexSize = 0;		//�C���f�b�N�X�T�C�Y

	ComPtr<ID3D11VertexShader> mVertexShader;			// ���_�V�F�[�_�[���ꕨ
	ComPtr<ID3D11PixelShader> mPixelShader;				// �s�N�Z���V�F�[�_�[���ꕨ
	ComPtr<ID3D11InputLayout> mVertexLayout;			// ���_�t�H�[�}�b�g��`

	//ComPtr<ID3D11Resource> mTexRes;								// �e�N�X�`�����\�[�X
	ID3D11ShaderResourceView* mShaderResourceView = nullptr;		// SRV

	ID3D11Buffer* mVertexBuffer = nullptr;			// ���_�o�b�t�@
	ID3D11Buffer* mIndexBuffer = nullptr;			// �C���f�b�N�X�o�b�t�@
	ID3D11Buffer* mCBMaterial = nullptr;			// �}�e���A���p�R���X�^���g�o�b�t�@

public:
	CRenderComponent(IActor& owner);

	bool GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , const char* vsfile);
	bool GeneratePixelShader(const char* psfile);

	//�f�[�^�̃Z�b�g�i�������j
	void SetData(unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* cBMaterial);

	void Render()override;
	void Update()override;
};