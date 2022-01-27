//!
//! @file
//! @brief WAVE�t�@�C���N���X�̃\�[�X�t�@�C��
//!

#include "CWave.h"
#include <xaudio2.h>

bool CWave::Init(const char* filePath , bool isLoop)
{
	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	//Wave�t�@�C���I�[�v��
	memset(&mmioInfo , 0 , sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)filePath , &mmioInfo , MMIO_READ);
	if(!hMmio)return false;			//�t�@�C���I�[�v�����s

	//RIFF�`�����N����
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W' , 'A' , 'V' , 'E');
	mmRes = mmioDescend(hMmio , &riffChunk , NULL , MMIO_FINDRIFF);
	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio , 0);
		return false;
	}

	//�t�H�[�}�b�g�`�����N����
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

	//�f�[�^�`�����N����
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d' , 'a' , 't' , 'a');
	mmRes = mmioDescend(hMmio , &dataChunk , &riffChunk , MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio , 0);
		return false;
	}

	//���f�[�^�i�[
	this->mData.reset(new char[dataChunk.cksize]);
	size = mmioRead(hMmio , (HPSTR)this->mData.get() , dataChunk.cksize);
	if(size != dataChunk.cksize)
	{
		this->mData.reset();
		return false;
	}

	mmioClose(hMmio , 0);

	this->mXABuf.AudioBytes = size;								//�o�b�t�@�̃o�C�g��
	this->mXABuf.pAudioData = (BYTE*)this->mData.get();			//�o�b�t�@�̐擪�A�h���X
	this->mXABuf.Flags = XAUDIO2_END_OF_STREAM;

	if(isLoop)this->mXABuf.LoopCount = XAUDIO2_LOOP_INFINITE;
	else this->mXABuf.LoopCount = 0;

	return true;
}