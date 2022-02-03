//!
//! @file
//! @brief �T�E���h�}�l�[�W���[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <string>
#include <unordered_map>

#include "../Data/CWave.h"

#undef PlaySound

//! @brief �T�E���h�}�l�[�W���[�N���X
class CSoundManager
{
private:
	//! @brief �T�E���h���\����
	struct SSoundInfo
	{
		std::string FilePath;		//!< �t�@�C���p�X
		float Volume;				//!< �{�����[��
		bool IsLoop;				//!< ���[�v���邩
	};

	IXAudio2* mXAudio;															//!< XAudio2�{��
	IXAudio2MasteringVoice* mMasteringVoice;									//!< �}�X�^�[�{�C�X

	std::unordered_map<std::string , IXAudio2SourceVoice*> mSourceVoice;		//!< �\�[�X�{�C�X
	std::unordered_map<std::string , CWave> mSoundData;							//!< �T�E���hWAVE�f�[�^
	std::unordered_map<std::string , SSoundInfo> mSoundInfo;					//!< �T�E���h���

	//!
	//! @brief �R���X�g���N�^
	//! @details XAudio�̏������̃^�C�~���O�ɂ���Ă̓e�N�X�`�����[�_�[�Ƃ̃G���[����������̂ŏ����i�K�ŌĂԂ��Ƃ𐄏�
	//!
	CSoundManager();

	//! @brief �f�X�g���N�^
	~CSoundManager();

	//!
	//! @brief �T�E���h�f�[�^�쐬
	//! @param[in] key �T�E���h�f�[�^�����R���e�i�̃L�[
	//!
	void CreateSoundData(std::string key);

public:
	//�R�s�[&���[�u�֎~
	CSoundManager(const CSoundManager&) = delete;
	CSoundManager& operator=(const CSoundManager&) = delete;
	CSoundManager(CSoundManager&&) = delete;
	CSoundManager& operator=(CSoundManager&&) = delete;

	//!
	//! @brief �C���X�^���X�擾
	//! @return CSoundManager& �C���X�^���X
	//!
	static CSoundManager& GetInstance()
	{
		static CSoundManager instance;
		return instance;
	}

	//!
	//! @brief �T�E���h���쐬
	//! @param[in] filePath �쐬����T�E���h��WAVE�t�@�C���̃p�X
	//! @param[in] volume �{�����[��
	//! @param[in] isLoop ���[�v���邩
	//! @param[in] alias �G�C���A�X
	//!
	void CreateSoundInfo(std::string filePath , float volume , bool isLoop , std::string alias = "NONE");

	//!
	//! @brief �{�����[���̃Z�b�g
	//! @param[in] key �L�[�ƂȂ�l�i�t�@�C���p�Xor�G�C���A�X�j
	//! @param[in] volume �{�����[��
	//!
	void SetVolume(std::string key , float volume);

	//!
	//! @brief �T�E���h�̍Đ�
	//! @param[in] key �L�[�ƂȂ�l�i�t�@�C���p�Xor�G�C���A�X�j
	//!
	void PlaySound(std::string key);

};

