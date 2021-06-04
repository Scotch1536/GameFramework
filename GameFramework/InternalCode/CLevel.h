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

	//コピー禁止
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;
public:
	//★超重要★　コンストラクタを呼ぶことはレベルの遷移を意味する
	CLevel(CGame& owner);

	void Update();
	void DestroyActor(CActor* target);
};