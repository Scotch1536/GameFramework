//!
//! @file
//! @brief サウンドマネージャーのソースファイル
//!

#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	//エラー処理の関数オブジェクト
	auto xAudioError = []
	{
		MessageBox(nullptr , "XAudio2 Init エラー" , "Error" , MB_OK);
		exit(1);
	};

	//XAudio2の初期化処理
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

	//存在しなければ
	if(mSoundData.count(filePath) == 0)
	{
		mSoundData[filePath];		//サウンドデータ作成
		mSourceVoice[filePath];		//ソースボイス作成

		//サウンドデータ初期化
		if(!mSoundData[filePath].Init(filePath.c_str() , mSoundInfo[key].IsLoop))
		{
			MessageBox(nullptr , "WaveRead エラー" , "Error" , MB_OK);
			exit(1);
		}

		//ソースボイス初期化
		if(FAILED(mXAudio->CreateSourceVoice(&mSourceVoice[filePath] , &mSoundData[filePath].GetWFEX())))
		{
			MessageBox(nullptr , "XAudio2 Init エラー" , "Error" , MB_OK);
			exit(1);
		}

		//ボリュームセット
		SetVolume(key , mSoundInfo[key].Volume);
	}
}

void CSoundManager::CreateSoundInfo(std::string filePath , float volume , bool isLoop , std::string alias)
{
	if(alias != "NONE")
	{
		//存在しなければ
		if(mSoundInfo.count(alias) == 0)
		{
			//サウンド情報作成
			mSoundInfo[alias] = { filePath,volume,isLoop };
		}

		//サウンドデータ作成
		CreateSoundData(alias);
	}
	else
	{
		//存在しなければ
		if(mSoundInfo.count(filePath) == 0)
		{
			//サウンド情報作成
			mSoundInfo[filePath] = { filePath,volume,isLoop };
		}

		//サウンドデータ作成
		CreateSoundData(filePath);
	}
}

void CSoundManager::SetVolume(std::string key , float volume)
{
	//存在しなければ
	if(mSoundInfo.count(key) == 0)
	{
		MessageBox(nullptr , "サウンド情報が見つかりませんでした" , "Error" , MB_OK);
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

	//存在しなければ
	if(mSoundInfo.count(key) == 0)
	{
		MessageBox(nullptr , "サウンド情報が見つかりませんでした" , "Error" , MB_OK);
		return;
	}
	else
	{
		filePath = mSoundInfo[key].FilePath;
	}

	XAUDIO2_VOICE_STATE state;

	mSourceVoice[filePath]->GetState(&state);

	//既に指定のサウンドが再生中されている場合
	if(state.BuffersQueued)
	{
		//ループしない場合
		if(mSoundData[filePath].GetXABuf().LoopCount == 0)
		{
			//サウンドを止めてソースバッファを消す
			mSourceVoice[filePath]->Stop();
			mSourceVoice[filePath]->FlushSourceBuffers();
		}
		else return;
	}

	//ソースバッファを登録してサウンドを流す
	mSourceVoice[filePath]->SubmitSourceBuffer(&mSoundData[filePath].GetXABuf());
	mSourceVoice[filePath]->Start();
}