//!
//! @file
//! @brief ���C���Q�[�����x���̃w�b�_�[�t�@�C��
//!

#pragma once
#include "GameFramework/Level/CLevel.h"

//! @brief ���C���Q�[�����x���N���X
class CMainGameLevel :public CLevel
{
private:
	float mTime = 60.0f;		//!< ��������
	int mScore = 0;				//!< �X�R�A

	bool mIsEnd = false;		//!< �I�����ǂ���

public:
	using CLevel::CLevel;

	//! @brief ������
	void Init()override;

	//! @brief �e�B�b�N
	void Tick()override;

	//!
	//! @brief �ʒm
	//! @param[in] actor �ʒm���̃A�N�^�[
	void Notice(CActor& actor)override;

};

