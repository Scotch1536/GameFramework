#pragma once
#include "CTransform.h"

class CTransform;

//�q�g�����X�t�H�[���N���X
class CChildTransform :public CTransform
{
private:
	CTransform& mParentTransform;		//�e�g�����X�t�H�[��

public:
	CChildTransform(CTransform& parent);
	~CChildTransform();

	//�X�V
	void Update()override;
};