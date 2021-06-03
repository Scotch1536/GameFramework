#pragma once
#include <vector>
#include <memory>

#include "CActor.h"

class CLevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;
public:
	void Update();
	void DestroyActor(CActor* target);
};