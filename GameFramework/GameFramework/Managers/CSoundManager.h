#pragma once
#include <string>
#include <unordered_map>

#include "../Data/CWave.h"

#undef PlaySound

class CSoundManager
{
private:
	//サウンド情報構造体
	struct SSoundInfo
	{
		std::string FilePath;		//ファイルパス
		float Volume;				//ボリューム
		bool IsLoop;				//ループするか
	};

	IXAudio2* mXAudio;								//XAudio2本体
	IXAudio2MasteringVoice* mMasteringVoice;		//マスターボイス

	std::unordered_map<std::string , IXAudio2SourceVoice*> mSourceVoice;		//ソースボイス格納辞書
	std::unordered_map<std::string , CWave> mSoundData;							//サウンド格納辞書
	std::unordered_map<std::string , SSoundInfo> mSoundInfo;						//サウンド情報格納辞書

	/*
	XAudioの初期化のタイミングによってはテクスチャローダーとのエラーが発生する
	早いうちによんでおくことを推奨
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

	//サウンド情報作成
	void CreateSoundInfo(std::string filePath , float volume , bool isLoop , std::string alias = "NONE");

	//セットボリューム
	void SetVolume(std::string key , float volume);
	void PlaySound(std::string key);
};

