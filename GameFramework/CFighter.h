#pragma once
#include <memory>
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CParticleSystemComponent.h"
#include "CPointer.h"

class CParticleSystemComponent;
class CTransform;

class CFighter :public CActor
{
private:
	CPointer& mPointer;

	int mShotCnt = 0;

	float mSpeed = 50.0f;
	float mSpeedLimitMin , mSpeedLimitMax;

public:
	/*
	�����d�v��
	�R���|�[�l���g�̒ǉ��͊�{�I�ɃR���X�g���N�^���ōs��
	*/
	CFighter(ILevel& owner);

	void Shot();
	void ShotReset();
	void Move();
	void Particle(CParticleSystemComponent::Particle& key,CTransform& trans);
	void Rot(int dire);
	void SpeedChange(int type);

	void Tick()override;
	//void EventAtBeginCollide(CActor& collideActor)override;
	//void EventAtEndCollide(CActor& collideActor)override;

};