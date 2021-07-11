#pragma once
#include <windows.h>
#include <xaudio2.h>
#include <mmsystem.h>
#include <memory>

class CWave {
private:
	WAVEFORMATEX wfex;					//WAVEフォーマット
	std::unique_ptr<char> pData;		//音楽データ
	XAUDIO2_BUFFER xaBuf;				//xAudio2バッファ
public:
	CWave() = default;

	bool Init(const char* filepath, bool isloop = true);

	const WAVEFORMATEX GetWFEX()const {
		return this->wfex;
	}

	const XAUDIO2_BUFFER GetXABuf()const {
		return this->xaBuf;
	}
};