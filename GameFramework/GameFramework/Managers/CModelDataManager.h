//!
//! @file
//! @brief ���f���f�[�^�}�l�[�W���[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <string>

#include "../Data/CModelData.h"

//! @brief ���f���f�[�^�}�l�[�W���[�N���X
class CModelDataManager
{
private:
	std::unordered_map<std::string , CModelData> mModelData;				//!< ���f���f�[�^

	std::filesystem::path mModelDataCachePath = "./ModelDataCache";			//!< ���f���f�[�^�̃L���b�V���̃f�B���N�g���p�X
	std::string mExtension = ".bin";										//!< �g���q

	//! @brief �R���X�g���N�^
	CModelDataManager() = default;

	//!
	//! @brief �t�@�C�����̍쐬
	//! @param[in] filePath �t�@�C���p�X
	//!
	std::string MakeFileName(std::string filePath);

	//!
	//! @brief �L���b�V���f�[�^�̓���
	//! @param[in] target �Ώۂ̃��f���f�[�^
	//! @param[in] filePath �t�@�C���p�X
	//! @return bool ���͂����������� ���L���b�V���f�[�^���Ȃ��ꍇ���s�ƂȂ�
	//!
	bool InputCache(CModelData& target , std::string filePath);

	//!
	//! @brief �L���b�V���f�[�^�̏o��
	//! @param[in] target �Ώۂ̃��f���f�[�^
	//! @param[in] filePath �t�@�C���p�X
	//!
	void OutputCache(CModelData& target , std::string filePath);

public:
	//�R�s�[&���[�u�֎~
	CModelDataManager(const CModelDataManager&) = delete;
	CModelDataManager& operator=(const CModelDataManager&) = delete;
	CModelDataManager(CModelDataManager&&) = delete;
	CModelDataManager& operator=(CModelDataManager&&) = delete;

	//!
	//! @brief �C���X�^���X�擾
	//! @return CModelDataManager& �C���X�^���X
	//!
	static CModelDataManager& GetInstance()
	{
		static CModelDataManager instance;
		return instance;
	}

	//!
	//! @brief ���f���f�[�^�擾
	//! @param[in] filePath �t�@�C���p�X
	//! @param[in] resourceFolderPath ���f���̃��\�[�X�i�e�N�X�`���Ȃǁj���u���Ă���t�H���_�̃p�X
	//!
	CModelData& GetModel(std::string filePath , std::string resourceFolderPath);
};
