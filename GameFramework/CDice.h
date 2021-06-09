#pragma once
#include "CActor.h"

class CDice :public CActor
{
public:
	CDice(CLevel& owner);

	void Test();

	void Rot(int dire);

	void Update()override;
};

