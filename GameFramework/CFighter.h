#pragma once
#include <memory>
#include "GameFramework/Actor/CActor.h"
#include "CPointer.h"

class CFighter :public CActor
{
private:
	CPointer& mPointer;

	int mShotCnt = 0;
	bool mIsHit = false;

	std::unique_ptr<XMFLOAT4> mTargetRot;
	XMFLOAT4 mStartRot;

	float mAlpha = 0.f;
	float mIncrementAlpha = 0.f;

public:
	/*
	★超重要★
	コンポーネントの追加は基本的にコンストラクタ内で行う
	*/
	CFighter(ILevel& owner);

	void Shot();
	void ShotReset();
	void Move();
	void Rot();
	void EventAtBeginCollide(CActor& collideActor)override;
	void EventAtEndCollide(CActor& collideActor)override;
	void Tick()override;

	bool GetIsHit()const
	{
		return mIsHit;
	}
};

