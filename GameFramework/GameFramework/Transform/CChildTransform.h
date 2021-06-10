#pragma once
#include "CTransform.h"

class CTransform;

//子トランスフォームクラス
class CChildTransform :public CTransform
{
private:
	CTransform& mParentTransform;		//親トランスフォーム

public:
	CChildTransform(CTransform& parent);
	~CChildTransform();

	//更新
	void Update()override;
};