//!
//! @file
//! @brief サウンドマネージャーのヘッダーファイル
//!

#pragma once
#include <string>
#include <unordered_map>

#include "../Data/CWave.h"

#undef PlaySound

//! @brief サウンドマネージャークラス
class CSoundManager
{
private:
	//! @brief サウンド情報構造体
	struct SSoundInfo
	{
		std::string FilePath;		//!< ファイルパス
		float Volume;				//!< ボリューム
		bool IsLoop;				//!< ループするか
	};

	IXAudio2* mXAudio;															//!< XAudio2本体
	IXAudio2MasteringVoice* mMasteringVoice;									//!< マスターボイス

	std::unordered_map<std::string , IXAudio2SourceVoice*> mSourceVoice;		//!< ソースボイス
	std::unordered_map<std::string , CWave> mSoundData;							//!< サウンドWAVEデータ
	std::unordered_map<std::string , SSoundInfo> mSoundInfo;					//!< サウンド情報

	//!
	//! @brief コンストラクタ
	//! @details XAudioの初期化のタイミングによってはテクスチャローダーとのエラーが発生するので初期段階で呼ぶことを推奨
	//!
	CSoundManager();

	//! @brief デストラクタ
	~CSoundManager();

	//!
	//! @brief サウンドデータ作成
	//! @param[in] key サウンドデータ辞書コンテナのキー
	//!
	void CreateSoundData(std::string key);

public:
	//コピー&ムーブ禁止
	CSoundManager(const CSoundManager&) = delete;
	CSoundManager& operator=(const CSoundManager&) = delete;
	CSoundManager(CSoundManager&&) = delete;
	CSoundManager& operator=(CSoundManager&&) = delete;

	//!
	//! @brief インスタンス取得
	//! @return CSoundManager& インスタンス
	//!
	static CSoundManager& GetInstance()
	{
		static CSoundManager instance;
		return instance;
	}

	//!
	//! @brief サウンド情報作成
	//! @param[in] filePath 作成するサウンドのWAVEファイルのパス
	//! @param[in] volume ボリューム
	//! @param[in] isLoop ループするか
	//! @param[in] alias エイリアス
	//!
	void CreateSoundInfo(std::string filePath , float volume , bool isLoop , std::string alias = "NONE");

	//!
	//! @brief ボリュームのセット
	//! @param[in] key キーとなる値（ファイルパスorエイリアス）
	//! @param[in] volume ボリューム
	//!
	void SetVolume(std::string key , float volume);

	//!
	//! @brief サウンドの再生
	//! @param[in] key キーとなる値（ファイルパスorエイリアス）
	//!
	void PlaySound(std::string key);

};

