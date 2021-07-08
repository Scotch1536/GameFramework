#pragma once
#include "GameFramework/Level/CLevel.h"

class CDice;
class CFighter;

class CTestLevel :public CLevel
{
private:
	CDice* mDice;
	CFighter* mFighter;
	int mCnt = 0;
	float mTime = 0;

public:
	/*
	�p���R���X�g���N�^���g�����ƂŊy�ɃR���X�g���N�^���p���ł���
	������CLevel�ɂ͓��ރR���X�g���N�^������̂ň��������
	�p���������ꍇ�͌ʂɏ������Ƃ𐄏�
	�ȉ��̃R�����g�A�E�g���Ă���R���X�g���N�^���ʂ̌p���̂�����
	*/
	using CLevel::CLevel;

	/*
	�����d�v��
	�Q�[�����s���Ɏn�߂������x����IGameManagerToLevel&�������ɂƂ�
	�R���X�g���N�^���I�[�o�[���C�h����
	*/
	//CTestLevel(IGameManagerToLevel& receiver):CLevel(receiver) {};

	/*
	�����d�v��
	�Q�[�����s���Ɏn�߂������x���ȊO��CGame&�������ɂƂ�
	�R���X�g���N�^���I�[�o�[���C�h����
	*/
	//CTestLevel(CGame& owner):CLevel(owner) {};

	/*
	�����d�v��
	�A�N�^�[�̒ǉ��͊�{�����ōs��
	�R���|�[�l���g�ǉ����邱�Ƃ��ł��邪�񐄏�
	�R���|�[�l���g�̓A�N�^�[�̃R���X�g���N�^�Œǉ����邱�Ƃ𐄏�
	*/
	void Init()override;

	void Tick()override;

	void ChangeFighterAngleToDirectionDice();
};

