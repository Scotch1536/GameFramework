#pragma once
#include <string>
#include <unordered_map>

#include "../Data/CWave.h"

#undef PlaySound

class CSoundManager
{
private:
	//�T�E���h���\����
	struct SSoundInfo
	{
		std::string FilePath;		//�t�@�C���p�X
		float Volume;				//�{�����[��
		bool IsLoop;				//���[�v���邩
	};

	IXAudio2* mXAudio;								//XAudio2�{��
	IXAudio2MasteringVoice* mMasteringVoice;		//�}�X�^�[�{�C�X

	std::unordered_map<std::string , IXAudio2SourceVoice*> mSourceVoice;		//�\�[�X�{�C�X�i�[����
	std::unordered_map<std::string , CWave> mSoundData;							//�T�E���h�i�[����
	std::unordered_map<std::string , SSoundInfo> mSoundInfo;						//�T�E���h���i�[����

	/*
	XAudio�̏������̃^�C�~���O�ɂ���Ă̓e�N�X�`�����[�_�[�Ƃ̃G���[����������
	���������ɂ��ł������Ƃ𐄏�
	*/
	CSoundManager();
	~CSoundManager();

	void CreateSoundData(std::string key);

public:
	CSoundManager(const CSoundManager&) = delete;
	CSoundManager& operator=(const CSoundManager&) = delete;
	CSoundManager(CSoundManager&&) = delete;
	CSoundManager& operator=(CSoundManager&&) = delete;

	static CSoundManager& GetInstance()
	{
		static CSoundManager instance;
		return instance;
	}

	//�T�E���h���쐬
	void CreateSoundInfo(std::string filePath , float volume , bool isLoop , std::string alias = "NONE");

	//�Z�b�g�{�����[��
	void SetVolume(std::string key , float volume);
	void PlaySound(std::string key);
};

