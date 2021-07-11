#include "CWave.h"
#include <xaudio2.h>

bool CWave::Init(const char* filepath, bool isloop) {
	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Waveファイルオープン
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)filepath, &mmioInfo, MMIO_READ);
	if (!hMmio)return false;	// ファイルオープン失敗

	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}

	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}

	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)&this->wfex, fmsize);
	if (size != fmsize) {
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}

	//音データ格納
	this->pData.reset(new char[dataChunk.cksize]);
	size = mmioRead(hMmio, (HPSTR)this->pData.get(), dataChunk.cksize);
	if (size != dataChunk.cksize) {
		this->pData.reset();
		return false;
	}

	mmioClose(hMmio, 0);

	this->xaBuf.AudioBytes = size;							//バッファのバイト数
	this->xaBuf.pAudioData = (BYTE*)this->pData.get();		//バッファの先頭アドレス
	this->xaBuf.Flags = XAUDIO2_END_OF_STREAM;

	if (isloop)this->xaBuf.LoopCount = XAUDIO2_LOOP_INFINITE;
	else this->xaBuf.LoopCount = 0;

	return true;
}