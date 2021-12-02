#pragma once
#include <DirectXMath.h>

#include "CSquareDivisionComponent.h"

using namespace DirectX;

class C2DAnimationComponent :public CSquareDivisionComponent
{
private:
	XMFLOAT2& mChangeTargetUV1 , mChangeTargetUV2 , mChangeTargetUV3 , mChangeTargetUV4;		//変更ターゲットのUV座標の参照

	int mAnimCounter = 0;			//アニメーションのカウンター（mUVDivisionDataのインデックス）
	int mAnimFrameMax;				//コマ数の最大値

	float mTimeCounter = 0.0f;		//経過時間のカウンター
	float mAnimFrameTime;			//一つのコマの時間

	bool mIsLoop;
	bool mShouldUpdate = true;

public:
	C2DAnimationComponent(CActor& owner , int divWidth , int divHeight , float oneLoopTime , bool isLoop ,
		XMFLOAT2& changeUV1 , XMFLOAT2& changeUV2 , XMFLOAT2& changeUV3 , XMFLOAT2& changeUV4);

	void Update()override;

	void SetIsLoop(bool flg)
	{
		mIsLoop = flg;
	}
};