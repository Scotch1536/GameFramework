#include "../Managers/CGameManager.h"

#include "C2DAnimationComponent.h"

//!
//! @file
//! @brief 2D�A�j���[�V�����R���|�[�l���g�̃\�[�X�t�@�C��
//!

C2DAnimationComponent::C2DAnimationComponent(CActor& owner , int divWidth , int divHeight)
	:CSquareDivisionComponent(owner , divWidth , divHeight)
{}

void C2DAnimationComponent::AddAnimData(XMFLOAT2* changeUV1 , XMFLOAT2* changeUV2 , XMFLOAT2* changeUV3 , XMFLOAT2* changeUV4 ,
	std::function<void()> functionWhenChangingUV , std::string alias)
{
	mAnimData.emplace_back();			//�A�j���f�[�^�ǉ�
	mAnimDataAlias.emplace_back();		//�A�j���f�[�^�G�C���A�X�ǉ�

	//�����o�̏�����
	mAnimData.back().AnimInfoName = "NONE";
	mAnimData.back().ChangeTargetUV1 = changeUV1;
	mAnimData.back().ChangeTargetUV2 = changeUV2;
	mAnimData.back().ChangeTargetUV3 = changeUV3;
	mAnimData.back().ChangeTargetUV4 = changeUV4;
	mAnimData.back().FunctionWhenChangingUV = functionWhenChangingUV;

	if(alias != "NONE")
	{
		mAnimDataAlias.back() = alias;
	}
}

void C2DAnimationComponent::Update()
{
	for(auto& anim : mAnimData)
	{
		//�A�j�����̃��[�v�ݒ肪true���A�j������~���Ă�����A�j�����ĊJ����
		if(mAnimInfo[anim.AnimInfoName].second && !anim.IsPlay)anim.IsPlay = true;

		//�A�j������~���Ă���ݒ�Ȃ�continue�ŏ������Ƃ΂�
		if(!anim.IsPlay)continue;

		//�^�C���J�E���^�[�Ƀf���^�^�C�������Z
		anim.TimeCounter += CGameManager::GetInstance().GetDeltaTime();

		//�ύX����R�}�����v�Z
		int changeNum = anim.TimeCounter / anim.AnimFrameTime;

		if(changeNum >= 1)
		{
			anim.AnimCounter += changeNum;								//�A�j���J�E���^�[���Z
			anim.TimeCounter -= anim.AnimFrameTime * changeNum;			//�^�C���J�E���^�[���Z

			//�A�j���J�E���^�[���A�j���̃R�}���̍ő�l�𒴂��Ă��邩
			if(anim.AnimCounter > anim.AnimFrameMax - 1)
			{
				//���[�v�ݒ肪true��
				if(mAnimInfo[anim.AnimInfoName].second)
				{
					anim.AnimCounter = anim.AnimCounter % (anim.AnimFrameMax - 1);
				}
				else
				{
					anim.AnimCounter = anim.AnimFrameMax - 1;
					anim.IsPlay = false;
				}
			}

			//�C���f�b�N�X�̌v�Z
			int index = anim.AnimStartIndex + anim.AnimCounter;

			//UV�̕ύX
			*anim.ChangeTargetUV1 = mUVDivisionData.at(index).at(0);
			*anim.ChangeTargetUV2 = mUVDivisionData.at(index).at(1);
			*anim.ChangeTargetUV3 = mUVDivisionData.at(index).at(2);
			*anim.ChangeTargetUV4 = mUVDivisionData.at(index).at(3);

			//UV�ύX�����s�֐��̌Ăяo��
			if(anim.FunctionWhenChangingUV != nullptr)anim.FunctionWhenChangingUV();
		}
	}
}