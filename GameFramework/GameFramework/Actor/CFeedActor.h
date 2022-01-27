//!
//! @file
//! @brief �t�F�[�h�A�N�^�[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <functional>

#include "../Game/CApplication.h"
#include "../Level/CLevel.h"

#include "CActor.h"
#include "CDisplay2DActor.h"

//! @brief �t�F�[�h�A�N�^�[�N���X
class CFeedActor :public CActor
{
public:
	//! @brief �t�F�[�h�I�v�V�����񋓌^
	enum class EOption
	{
		FEEDOUT ,
		FEEDIN
	};

private:
	EOption mOption;								//!< �t�F�[�h�I�v�V����

	CDisplay2DActor* mFeedScreen;					//!< �t�F�[�h�̂��߂̃X�N���[���T�C�Y��2D���b�V��

	std::function<void()> mDoAfterFeedEvent;		//!< �t�F�[�h�I����ɍs���C�x���g

	float mAlpha;									//!< �A���t�@�l
	float mIncreaseAlpha;							//!< �A���t�@�l�̑�����

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃A�N�^�[�����L���郌�x��
	//! @param[in] event �t�F�[�h�I����ɍs���C�x���g
	//! @param[in] feedOption �t�F�[�h�I�v�V�����p�X
	//! @param[in] color �F���
	//! @param[in] feedTime �t�F�[�h���I���܂łɂ�����b��
	//!
	CFeedActor(ILevel& partner , std::function<void()> event , EOption feedOption , XMFLOAT3 color = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f):CActor(partner) ,
		mDoAfterFeedEvent(event) , mOption(feedOption) , mIncreaseAlpha(1.0f / (feedTime*60.0f))
	{
		if(mOption == EOption::FEEDOUT)mAlpha = 0.0f;
		else if(mOption == EOption::FEEDIN)	mAlpha = 1.0f;

		//�t�F�[�h�X�N���[���쐬&������
		mFeedScreen = new CDisplay2DActor(mOwnerInterface , XMFLOAT4(color.x , color.y , color.z , mAlpha));
		mFeedScreen->Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH) / 2;
		mFeedScreen->Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT) / 2;
		mFeedScreen->Transform.Scale.x = CApplication::CLIENT_WIDTH;
		mFeedScreen->Transform.Scale.y = CApplication::CLIENT_HEIGHT;
	}

	void Tick()override
	{
		bool isFeedEnd = false;

		//�A���t�@�l�̍X�V
		if(mOption == EOption::FEEDOUT)mAlpha += mIncreaseAlpha;
		else if(mOption == EOption::FEEDIN)	mAlpha -= mIncreaseAlpha;

		//�t�F�[�h�̏I���̊m�F
		if(mOption == EOption::FEEDOUT)
		{
			if(mAlpha >= 1.0f)
			{
				mAlpha = 1.0f;
				isFeedEnd = true;
			}
		}
		else if(mOption == EOption::FEEDIN)
		{
			if(mAlpha <= 0.0f)
			{
				mAlpha = 0.0f;
				isFeedEnd = true;
			}
		}

		//�F�i�A���t�@�l�j�̍X�V
		XMFLOAT4 color = mFeedScreen->GetColor();
		color.w = mAlpha;
		mFeedScreen->SetColor(color);

		if(isFeedEnd)
		{
			//�t�F�[�h�I����C�x���g������Ȃ���s
			if(mDoAfterFeedEvent != nullptr)mDoAfterFeedEvent();

			//���g�̔j��
			Destroy();
		}
	}
};