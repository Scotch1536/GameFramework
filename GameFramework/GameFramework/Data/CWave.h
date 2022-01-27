//!
//! @file
//! @brief WAVE�t�@�C���N���X�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <windows.h>
#include <xaudio2.h>
#include <mmsystem.h>
#include <memory>

//! @brief WAVE�t�@�C���N���X
class CWave {
private:
	WAVEFORMATEX mWFEX;					//!< WAVE�t�H�[�}�b�g
	std::unique_ptr<char> mData;		//!< ���y�f�[�^
	XAUDIO2_BUFFER mXABuf;				//!< XAudio2�o�b�t�@

public:
	//!
	//! @brief ������
	//! @param[in] filePath �t�@�C���̃p�X
	//! @param[in] isLoop ���[�v���邩
	//! @return �������ɐ���������
	//!
	bool Init(const char* filePath, bool isLoop = true);

	const WAVEFORMATEX GetWFEX()const {
		return this->mWFEX;
	}

	const XAUDIO2_BUFFER GetXABuf()const {
		return this->mXABuf;
	}
};