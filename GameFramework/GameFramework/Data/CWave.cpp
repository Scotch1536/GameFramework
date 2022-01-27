//!
//! @file
//! @brief WAVEファイルクラスのソースファイル
//!

#include "CWave.h"
#include <xaudio2.h>

bool CWave::Init(const char* filePath , bool isLoop)
{
	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	//Waveファイルオープン
	memset(&mmioInfo , 0 , sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)filePath , &mmioInfo , MMIO_READ);
	if(!hMmio)return false;			//ファイルオープン失敗

	//RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W' , 'A' , 'V' , 'E');
	mmRes = mmioDescend(hMmio , &riffChunk , NULL , MMIO_FINDRIFF);
	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio , 0);
		return false;
	}

	//フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f' , 'm' , 't' , ' ');
	mmRes = mmioDescend(hMmio , &formatChunk , &riffChunk , MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio , 0);
		return false;
	}

	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio , (HPSTR)&this->mWFEX , fmsize);
	if(size != fmsize)
	{
		mmioClose(hMmio , 0);
		return false;
	}

	mmioAscend(hMmio , &formatChunk , 0);

	//データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d' , 'a' , 't' , 'a');
	mmRes = mmioDescend(hMmio , &dataChunk , &riffChunk , MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio , 0);
		return false;
	}

	//音データ格納
	this->mData.reset(new char[dataChunk.cksize]);
	size = mmioRead(hMmio , (HPSTR)this->mData.get() , dataChunk.cksize);
	if(size != dataChunk.cksize)
	{
		this->mData.reset();
		return false;
	}

	mmioClose(hMmio , 0);

	this->mXABuf.AudioBytes = size;								//バッファのバイト数
	this->mXABuf.pAudioData = (BYTE*)this->mData.get();			//バッファの先頭アドレス
	this->mXABuf.Flags = XAUDIO2_END_OF_STREAM;

	if(isLoop)this->mXABuf.LoopCount = XAUDIO2_LOOP_INFINITE;
	else this->mXABuf.LoopCount = 0;

	return true;
}