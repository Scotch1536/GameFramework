#pragma once
#include "CRotator.h"
#include "dx11mathutil.h"

class CTransform
{
private:
	XMFLOAT3 mLocation;
	XMFLOAT3 mScale;
	CRotator mRotator;

	void MakeMatrix();
	void SetMatrix();
public:
	void Update();

};