//!
//! @file
//! @brief DirectX���\�[�X�}�l�[�W���[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <unordered_map>

#include "../ExternalCode/CDirectxGraphics.h"

//! @brief DirectX���\�[�X�}�l�[�W���[�N���X
class CDirectXResourceManager
{
private:
	std::unordered_map<std::string , ComPtr<ID3D11Resource>> mTextureResource;				//!< �e�N�X�`�����\�[�X
	std::unordered_map<std::string , ComPtr<ID3D11ShaderResourceView>> mTextureSRV;			//!< �e�N�X�`��SRV
	std::unordered_map<std::string , ComPtr<ID3D11VertexShader>> mVertexShader;				//!< ���_�V�F�[�_
	std::unordered_map<std::string , ComPtr<ID3D11PixelShader>> mPixelShader;				//!< �s�N�Z���V�F�[�_
	std::unordered_map<std::string , ComPtr<ID3D11InputLayout>> mVertexLayout;				//!< ���_���C�A�E�g

	//! @brief �R���X�g���N�^
	CDirectXResourceManager();

	//�R�s�[�����[�u�֎~
	CDirectXResourceManager(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager& operator=(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager(CDirectXResourceManager&&) = delete;
	CDirectXResourceManager& operator=(CDirectXResourceManager&&) = delete;

public:
	//!
	//! @brief �C���X�^���X�擾
	//! @return CDirectXResourceManager& �C���X�^���X
	//!
	static CDirectXResourceManager& GetInstance();

	//!
	//! @brief �e�N�X�`��SRV�擾�i�쐬�j
	//! @param[in] filePath �擾�������e�N�X�`��SRV�̌��̃t�@�C���̃p�X
	//! @return ID3D11ShaderResourceView* �e�N�X�`��SRV
	//!
	ID3D11ShaderResourceView* GetTextureSRV(std::string filePath);

	//!
	//! @brief ���_�V�F�[�_�擾�i�쐬�j
	//! @param[in] filePath �擾���������_�V�F�[�_�̌��̃t�@�C���̃p�X
	//! @return ID3D11VertexShader* ���_�V�F�[�_
	//!
	ID3D11VertexShader* GetVertexShader(std::string filePath);

	//!
	//! @brief �s�N�Z���V�F�[�_�擾�i�쐬�j
	//! @param[in] filePath �擾�������s�N�Z���V�F�[�_�̌��̃t�@�C���̃p�X
	//! @return ID3D11PixelShader* �s�N�Z���V�F�[�_
	//!
	ID3D11PixelShader* GetPixelShader(std::string filePath);

	//!
	//! @brief ���_���C�A�E�g�쐬
	//! @param[in] layout �쐬���������_���C�A�E�g�̓��e�i�z��̐擪�|�C���^�j
	//! @param[in] layoutSize ���_���C�A�E�g�̑傫��
	//! @param[in] vsFilePath �쐬���������_���C�A�E�g�ƕR�Â����_�V�F�[�_�̃t�@�C���̃p�X
	//!
	void CreateVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

	//!
	//! @brief ���_���C�A�E�g�擾
	//! @param[in] vsFilePath �擾���������_���C�A�E�g�ƕR�Â����_�V�F�[�_�̃t�@�C���̃p�X
	//! @return ID3D11InputLayout* ���_���C�A�E�g
	//!
	ID3D11InputLayout* GetVertexLayout(std::string vsFilePath);
	
	//!
	//! @brief ���_���C�A�E�g�擾
	//! @details ���_���C�A�E�g���Ȃ���΍쐬���s���ۂɗ��p����
	//! @param[in] layout �擾���������_���C�A�E�g�̓��e�i�z��̐擪�|�C���^�j
	//! @param[in] layoutSize ���_���C�A�E�g�̑傫��
	//! @param[in] vsFilePath ��擾���������_���C�A�E�g�ƕR�Â����_�V�F�[�_�̃t�@�C���̃p�X
	//! @return ID3D11InputLayout* ���_���C�A�E�g
	//!
	ID3D11InputLayout* GetVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

};