#pragma once
#include <vector>
#include <memory>

#include "CActor.h"
#include "CGame.h"

class CLevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;
	CGame& mOwner;

	//�R�s�[�֎~
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;
public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓��x���̑J�ڂ��Ӗ�����
	CLevel(CGame& owner);

	void Update();
	void DestroyActor(CActor* target);
};