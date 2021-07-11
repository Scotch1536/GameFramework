#pragma once
#include <windows.h>
#include <xaudio2.h>
#include <mmsystem.h>
#include <memory>

class CWave {
private:
	WAVEFORMATEX wfex;					//WAVE�t�H�[�}�b�g
	std::unique_ptr<char> pData;		//���y�f�[�^
	XAUDIO2_BUFFER xaBuf;				//xAudio2�o�b�t�@
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