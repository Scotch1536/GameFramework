#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "CComponent.h"
#include "VertexProto.h"

using Microsoft::WRL::ComPtr;

//�����_�[�R���|�[�l���g�N���X
class CRenderComponent :public CComponent
{
protected:
	//unsigned int mIndexSize = 0;		//�C���f�b�N�X�T�C�Y

	ComPtr<ID3D11VertexShader> mVertexShader;			// ���_�V�F�[�_�[
	ComPtr<ID3D11PixelShader> mPixelShader;				// �s�N�Z���V�F�[�_�[
	ComPtr<ID3D11InputLayout> mVertexLayout;			// ���_�t�H�[�}�b�g

	//ComPtr<ID3D11Resource> mTexRes;								// �e�N�X�`�����\�[�X
	//ID3D11ShaderResourceView* mShaderResourceView = nullptr;		// SRV

	//ID3D11Buffer* mVertexBuffer = nullptr;			// ���_�o�b�t�@
	//ID3D11Buffer* mIndexBuffer = nullptr;			// �C���f�b�N�X�o�b�t�@
	//ID3D11Buffer* mCBMaterial = nullptr;			// �}�e���A���p�R���X�^���g�o�b�t�@

public:
	CRenderComponent(IActor& owner);

	//���_�V�F�[�_����
	bool GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , const char* vsfile);

	//�s�N�Z���V�F�[�_����
	bool GeneratePixelShader(const char* psfile);

	////�f�[�^�̃Z�b�g�i�������j
	//void SetData(unsigned int indexSize ,
	//	ID3D11ShaderResourceView* shaderResourceView ,
	//	ID3D11Buffer* vertexBuffer ,
	//	ID3D11Buffer* indexBuffer ,
	//	ID3D11Buffer* cBMaterial);

	//�`��
	void Render(unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* cBMaterial);

	//�X�V
	void Update()override;
};