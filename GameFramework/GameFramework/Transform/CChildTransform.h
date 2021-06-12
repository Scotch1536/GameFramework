#pragma once
#include "CTransform.h"

class CTransform;

//子トランスフォームクラス
class CChildTransform :public CTransform
{
private:
	CTransform& mParentTransform;		//親トランスフォーム

	XMFLOAT4X4 mParentCompositionMatrix;

public:
	CChildTransform(CTransform& parent);
	~CChildTransform();

	//更新
	void Update()override;

	void RequestSetMatrix()override;
};