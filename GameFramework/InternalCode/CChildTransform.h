#pragma once
#include "CTransform.h"

class CTransform;

class CChildTransform :public CTransform
{
private:
	CTransform& mParentTransform;		//�e�g�����X�t�H�[��

public:
	CChildTransform(CTransform& parent);
	~CChildTransform();

	void Update()override;
};