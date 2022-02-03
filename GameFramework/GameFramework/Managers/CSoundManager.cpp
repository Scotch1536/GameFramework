//!
//! @file
//! @brief �T�E���h�}�l�[�W���[�̃\�[�X�t�@�C��
//!

#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	//�G���[�����̊֐��I�u�W�F�N�g
	auto xAudioError = []
	{
		MessageBox(nullptr , "XAudio2 Init �G���[" , "Error" , MB_OK);
		exit(1);
	};

	//XAudio2�̏���������
	if(FAILED(CoInitializeEx(0 , COINIT_MULTITHREADED)))xAudioError();
	if(FAILED(XAudio2Create(&this->mXAudio)))xAudioError();
	if(FAILED(this->mXAudio->CreateMasteringVoice(&this->mMasteringVoice)))xAudioError();
}

CSoundManager::~CSoundManager()
{
	for(auto& sv : this->mSourceVoice)
	{
		sv.second->DestroyVoice();
	}

	if(this->mMasteringVoice != nullptr)
	{
		this->mMasteringVoice->DestroyVoice();
		this->mMasteringVoice = nullptr;
	}

	if(this->mXAudio != nullptr)
	{
		this->mXAudio->Release();
		this->mXAudio = nullptr;
	}

	CoUninitialize();
}

void CSoundManager::CreateSoundData(std::string key)
{
	std::string filePath = mSoundInfo[key].FilePath;

	//���݂��Ȃ����
	if(mSoundData.count(filePath) == 0)
	{
		mSoundData[filePath];		//�T�E���h�f�[�^�쐬
		mSourceVoice[filePath];		//�\�[�X�{�C�X�쐬

		//�T�E���h�f�[�^������
		if(!mSoundData[filePath].Init(filePath.c_str() , mSoundInfo[key].IsLoop))
		{
			MessageBox(nullptr , "WaveRead �G���[" , "Error" , MB_OK);
			exit(1);
		}

		//�\�[�X�{�C�X������
		if(FAILED(mXAudio->CreateSourceVoice(&mSourceVoice[filePath] , &mSoundData[filePath].GetWFEX())))
		{
			MessageBox(nullptr , "XAudio2 Init �G���[" , "Error" , MB_OK);
			exit(1);
		}

		//�{�����[���Z�b�g
		SetVolume(key , mSoundInfo[key].Volume);
	}
}

void CSoundManager::CreateSoundInfo(std::string filePath , float volume , bool isLoop , std::string alias)
{
	if(alias != "NONE")
	{
		//���݂��Ȃ����
		if(mSoundInfo.count(alias) == 0)
		{
			//�T�E���h���쐬
			mSoundInfo[alias] = { filePath,volume,isLoop };
		}

		//�T�E���h�f�[�^�쐬
		CreateSoundData(alias);
	}
	else
	{
		//���݂��Ȃ����
		if(mSoundInfo.count(filePath) == 0)
		{
			//�T�E���h���쐬
			mSoundInfo[filePath] = { filePath,volume,isLoop };
		}

		//�T�E���h�f�[�^�쐬
		CreateSoundData(filePath);
	}
}

void CSoundManager::SetVolume(std::string key , float volume)
{
	//���݂��Ȃ����
	if(mSoundInfo.count(key) == 0)
	{
		MessageBox(nullptr , "�T�E���h��񂪌�����܂���ł���" , "Error" , MB_OK);
		return;
	}
	else
	{
		mSourceVoice[mSoundInfo[key].FilePath]->SetVolume(volume);
	}
}

void CSoundManager::PlaySound(std::string key)
{
	std::string filePath;

	//���݂��Ȃ����
	if(mSoundInfo.count(key) == 0)
	{
		MessageBox(nullptr , "�T�E���h��񂪌�����܂���ł���" , "Error" , MB_OK);
		return;
	}
	else
	{
		filePath = mSoundInfo[key].FilePath;
	}

	XAUDIO2_VOICE_STATE state;

	mSourceVoice[filePath]->GetState(&state);

	//���Ɏw��̃T�E���h���Đ�������Ă���ꍇ
	if(state.BuffersQueued)
	{
		//���[�v���Ȃ��ꍇ
		if(mSoundData[filePath].GetXABuf().LoopCount == 0)
		{
			//�T�E���h���~�߂ă\�[�X�o�b�t�@������
			mSourceVoice[filePath]->Stop();
			mSourceVoice[filePath]->FlushSourceBuffers();
		}
		else return;
	}

	//�\�[�X�o�b�t�@��o�^���ăT�E���h�𗬂�
	mSourceVoice[filePath]->SubmitSourceBuffer(&mSoundData[filePath].GetXABuf());
	mSourceVoice[filePath]->Start();
}