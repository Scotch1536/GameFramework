#pragma once
#include "GameFramework/Level/CLevel.h"

class CTestLevel :public CLevel
{
public:
	/*
	�����d�v��
	�Q�[�����s���Ɏn�߂������x����IGameManagerToLevel&�������ɂƂ�
	�R���X�g���N�^���I�[�o�[���C�h����
	*/
	CTestLevel(IGameManagerToLevel& receiver):CLevel(receiver) {};

	/*
	�����d�v��
	�Q�[�����s���Ɏn�߂������x���ȊO��CGame&�������ɂƂ�
	�R���X�g���N�^���I�[�o�[���C�h����
	*/
	CTestLevel(CGame& owner):CLevel(owner) {};

	/*
	�����d�v��
	�A�N�^�[�̒ǉ��͊�{�����ōs��
	�R���|�[�l���g�ǉ����邱�Ƃ��ł��邪�񐄏�
	�R���|�[�l���g�̓A�N�^�[�̃R���X�g���N�^�Œǉ����邱�Ƃ𐄏�
	*/
	void Init()override;
};

