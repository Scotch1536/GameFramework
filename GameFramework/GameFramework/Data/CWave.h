//!
//! @file
//! @brief WAVEファイルクラスのヘッダーファイル
//!

#pragma once
#include <windows.h>
#include <xaudio2.h>
#include <mmsystem.h>
#include <memory>

//! @brief WAVEファイルクラス
class CWave {
private:
	WAVEFORMATEX mWFEX;					//!< WAVEフォーマット
	std::unique_ptr<char> mData;		//!< 音楽データ
	XAUDIO2_BUFFER mXABuf;				//!< XAudio2バッファ

public:
	//!
	//! @brief 初期化
	//! @param[in] filePath ファイルのパス
	//! @param[in] isLoop ループするか
	//! @return 初期化に成功したか
	//!
	bool Init(const char* filePath, bool isLoop = true);

	const WAVEFORMATEX GetWFEX()const {
		return this->mWFEX;
	}

	const XAUDIO2_BUFFER GetXABuf()const {
		return this->mXABuf;
	}
};