#pragma once
#include <DirectXMath.h>

#include "CSquareDivisionComponent.h"

using namespace DirectX;

class C2DAnimationComponent :public CSquareDivisionComponent
{
private:
	XMFLOAT2& mChangeTargetUV1 , mChangeTargetUV2 , mChangeTargetUV3 , mChangeTargetUV4;		//�ύX�^�[�Q�b�g��UV���W�̎Q��

	int mAnimCounter = 0;			//�A�j���[�V�����̃J�E���^�[�imUVDivisionData�̃C���f�b�N�X�j
	int mAnimFrameMax;				//�R�}���̍ő�l

	float mTimeCounter = 0.0f;		//�o�ߎ��Ԃ̃J�E���^�[
	float mAnimFrameTime;			//��̃R�}�̎���

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