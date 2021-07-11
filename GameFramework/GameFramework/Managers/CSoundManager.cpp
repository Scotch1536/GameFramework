#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	//エラーの処理
	auto xAudioError = []
	{
		MessageBox(nullptr , "XAudio2 Init エラー" , "error!!" , MB_OK);
		exit(1);
	};

	//XAudio2の初期化
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

	if(this->mMasteringVoice)
	{
		this->mMasteringVoice->DestroyVoice();
		this->mMasteringVoice = nullptr;
	}

	if(this->mXAudio)
	{
		this->mXAudio->Release();
		this->mXAudio = nullptr;
	}

	CoUninitialize();
}

void CSoundManager::CreateSoundData(std::string key)
{
	std::string filePath = mSoundInfo[key].FilePath;

	if(mSoundData.count(filePath) == 0)
	{
		mSoundData[filePath];		//サウンドデータ作成
		mSourceVoice[filePath];		//ソースボイス作成

		//サウンドデータ初期化
		if(!mSoundData[filePath].Init(filePath.c_str() , mSoundInfo[key].IsLoop))
		{
			MessageBox(nullptr , "WaveRead エラー" , "error!!" , MB_OK);
			exit(1);
		}

		//ソースボイス初期化
		if(FAILED(mXAudio->CreateSourceVoice(&mSourceVoice[filePath] , &mSoundData[filePath].GetWFEX())))
		{
			MessageBox(nullptr , "XAudio2 Init エラー" , "error!!" , MB_OK);
			exit(1);
		}

		SetVolume(key , mSoundInfo[key].Volume);			//ボリュームセット
	}
}

void CSoundManager::CreateSoundInfo(std::string filePath , float volume , bool isLoop , std::string alias)
{
	if(alias != "NONE")
	{
		if(mSoundInfo.count(alias) == 0)
		{
			mSoundInfo[alias] = { filePath,volume,isLoop };
		}
		CreateSoundData(alias);
	}
	else
	{
		if(mSoundInfo.count(filePath) == 0)
		{
			mSoundInfo[filePath] = { filePath,volume,isLoop };
		}
		CreateSoundData(filePath);
	}
}

void CSoundManager::SetVolume(std::string key , float volume)
{
	if(mSoundInfo.count(key) == 0)
	{
		MessageBox(nullptr , "Not Found SoundInfo" , "error" , MB_OK);
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

	if(mSoundInfo.count(key) == 0)
	{
		MessageBox(nullptr , "Not Found SoundInfo" , "error" , MB_OK);
		return;
	}
	else
	{
		filePath = mSoundInfo[key].FilePath;
	}

	XAUDIO2_VOICE_STATE state;

	mSourceVoice[filePath]->GetState(&state);

	//既にその音を再生中の場合
	if(state.BuffersQueued)
	{
		if(mSoundData[filePath].GetXABuf().LoopCount == 0)
		{
			mSourceVoice[filePath]->Stop();
			mSourceVoice[filePath]->FlushSourceBuffers();
		}
		else return;
	}

	mSourceVoice[filePath]->SubmitSourceBuffer(&mSoundData[filePath].GetXABuf());
	mSourceVoice[filePath]->Start();
}