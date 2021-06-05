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

	//コピー禁止
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;
public:
	//★超重要★　コンストラクタを呼ぶことはレベルの遷移を意味する
	CLevel(CGame& owner);

	void Update();
	void DestroyActor(CActor& target)override;
};