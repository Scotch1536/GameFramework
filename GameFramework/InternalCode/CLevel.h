#pragma once
#include <vector>
#include <memory>

#include "CActor.h"

class IGame;
class CGame;

class ILevel
{
public:
	virtual ~ILevel() {};
	virtual void DestroyActor(CActor& target) = 0;
};

class CLevel :public ILevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;
	IGame& mOwnerInterface;

	//�R�s�[�֎~
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;
public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓��x���̑J�ڂ��Ӗ�����
	CLevel(CGame& owner);

	void Update();
	void DestroyActor(CActor& target)override;
};