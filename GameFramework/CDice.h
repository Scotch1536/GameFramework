#pragma once
#include "GameFramework/Actor/CActor.h"

class CDice :public CActor
{
public:
	/*
	�����d�v��
	�R���|�[�l���g�̒ǉ��͊�{�I�ɃR���X�g���N�^���ōs��
	*/
	CDice(CLevel& owner);

	void GamePause();
};

