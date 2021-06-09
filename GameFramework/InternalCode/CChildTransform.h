#pragma once
#include "CTransform.h"

class CTransform;

class CChildTransform :public CTransform
{
private:
	CTransform& mParentTransform;		//親トランスフォーム

public:
	CChildTransform(CTransform& parent);
	~CChildTransform();

	void Update()override;
};