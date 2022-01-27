//!
//! @file
//! @brief 2D�A�j���[�V�����R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <DirectXMath.h>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

#include "CSquareDivisionComponent.h"

using namespace DirectX;

//! @brief 2D�A�j���[�V�����R���|�[�l���g�N���X
class C2DAnimationComponent :public CSquareDivisionComponent
{
	//! @brief �A�j���f�[�^�\����
	struct SAnimData
	{
		std::string AnimInfoName;		//!< �Đ�����A�j�����̖��O

		XMFLOAT2* ChangeTargetUV1;		//!< �ύX�^�[�Q�b�g��UV���W�̎Q��1
		XMFLOAT2* ChangeTargetUV2;		//!< �ύX�^�[�Q�b�g��UV���W�̎Q��2
		XMFLOAT2* ChangeTargetUV3;		//!< �ύX�^�[�Q�b�g��UV���W�̎Q��3
		XMFLOAT2* ChangeTargetUV4;		//!< �ύX�^�[�Q�b�g��UV���W�̎Q��4

		std::function<void()> FunctionWhenChangingUV;		//!< UV�X�V�����s�֐�

		int AnimCounter = 0;			//!< �A�j���[�V�����̃J�E���^�[
		int AnimStartIndex;				//!< �A�j���̊J�n����C���f�b�N�X
		int AnimFrameMax;				//!< �R�}���̍ő�l

		float TimeCounter = 0.0f;		//!< �o�ߎ��Ԃ̃J�E���^�[
		float AnimFrameTime;			//!< ��̃R�}�̎���

		bool IsPlay = false;			//!< �Đ����Ă��邩
	};

private:
	std::vector<SAnimData> mAnimData;				//!< �A�j���f�[�^�i�A�j���[�V�������s���ۂ̕ύX��̏��j
	std::vector<std::string> mAnimDataAlias;		//!< �A�j���f�[�^�̂̃G�C���A�X

	std::unordered_map<std::string , std::pair<float , bool>> mAnimInfo;		//!< �A�j�����i�R�}�͈̔́A�P���[�v�ɂ�����b���A���[�v���邩�ǂ����j

	//! @brief �X�V
	void Update()override;

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] divWidth �A�j���[�V�����f�ނ̉����̕�����
	//! @param[in] divHeight �A�j���[�V�����f�ނ̏c���̕�����
	//!
	C2DAnimationComponent(CActor& owner , int divWidth , int divHeight);

	//!
	//! @brief �A�j���f�[�^�̒ǉ�
	//! @param[in] changeUV1 �ύX����UV���1��
	//! @param[in] changeUV2 �ύX����UV���2��
	//! @param[in] changeUV3 �ύX����UV���3��
	//! @param[in] changeUV4 �ύX����UV���4��
	//! @param[in] functionWhenChangingUV UV���ύX���ꂽ���ɒǉ��ŌĂт����֐�
	//! @param[in] alias �ʖ�
	//!
	void AddAnimData(XMFLOAT2* changeUV1 , XMFLOAT2* changeUV2 , XMFLOAT2* changeUV3 , XMFLOAT2* changeUV4 ,
		std::function<void()> functionWhenChangingUV , std::string alias = "NONE");

	//!
	//! @brief �A�j�����̒ǉ�
	//! @details �V�K�ɃA�j������ǉ�����ۂɗ��p����
	//! @param[in] animName �A�j���[�V�����̖��O 
	//! @param[in] start �J�n�̃R�}�̃C���f�b�N�X
	//! @param[in] finish �I���̃R�}�̃C���f�b�N�X
	//! @param[in] oneLoopTime �A�j���[�V�������������b��
	//! @param[in] isLoop ���[�v���邩
	//!
	void AddAnimInfo(std::string animName , int start , int finish , float oneLoopTime , bool isLoop)
	{
		AddAlias(start , finish , animName);				//�G�C���A�X�̒ǉ�
		mAnimInfo[animName] = { oneLoopTime,isLoop };		//�A�j�����̏�����
	}

	//!
	//! @brief �A�j�����̒ǉ�
	//! @details ���ɃG�C���A�X�Ŕ͈͕������Ă��镔���ɃA�j�����̂ݒǉ�����ۂɗ��p����
	//! @param[in] alias 
	//! @param[in] oneLoopTime �A�j���[�V�������������b��
	//! @param[in] isLoop ���[�v���邩
	//!
	void AddAnimInfo(std::string alias , float oneLoopTime , bool isLoop)
	{
		//���݂��Ă��邩
		if(mAlias.count(alias) != 0)
		{
			mAnimInfo[alias] = { oneLoopTime,isLoop };		//�A�j�����̏�����
		}
		else
		{
			MessageBox(NULL , "�o�^�ς݂̃G�C���A�X��������܂���ł���" , "Error" , MB_OK);
		}
	}

	//!
	//! @brief �A�j���f�[�^�̍폜
	//! @param[in] index �A�j���f�[�^���i�[����Ă���z��̃C���f�b�N�X
	//!
	void DeleteAnimData(int index)
	{
		//�C���f�b�N�X���͈͓��Ɏ��܂��Ă��邩
		if(index >= 0 && index < mAnimData.size())
		{
			auto itr = mAnimData.begin();
			auto itr2 = mAnimDataAlias.begin();

			mAnimData.erase(itr + index);
			mAnimDataAlias.erase(itr2 + index);
			mAnimData.shrink_to_fit();
			mAnimDataAlias.shrink_to_fit();
		}
	}

	//!
	//! @brief �A�j���f�[�^�̍폜
	//! @details �A�j���f�[�^�̃G�C���A�X����A�j���f�[�^���폜����ۂɗ��p����
	//! @param[in] animDataAlias �A�j���f�[�^�̃G�C���A�X
	//!
	void DeleteAnimData(std::string animDataAlias)
	{
		int index = 0;

		for(auto& indexAlias : mAnimDataAlias)
		{
			//��v���邩
			if(indexAlias == animDataAlias)
			{
				DeleteAnimData(index);		//�A�j���f�[�^�̍폜
				return;
			}
			else index++;
		}

		MessageBox(NULL , "�o�^�ς݂̃A�j���f�[�^�̃G�C���A�X��������܂���ł���" , "Error" , MB_OK);
	}

	//!
	//! @brief �A�j���[�V�������Đ�����Ă��邩�̃`�F�b�N
	//! @param[in] index �A�j���f�[�^���i�[����Ă���z��̃C���f�b�N�X
	//! @return bool �Đ�����Ă��邩
	//!
	bool CheckIsPlay(int index)
	{
		//�C���f�b�N�X���͈͓��Ɏ��܂��Ă��邩
		if(index >= 0 && index < mAnimData.size())
		{
			return mAnimData.at(index).IsPlay;
		}
		else
		{
			MessageBox(NULL , "�A�j���f�[�^��������܂���ł���" , "Error" , MB_OK);
			return false;
		}
	}	
	
	//!
	//! @brief �A�j���[�V�������Đ�����Ă��邩�̃`�F�b�N
	//! @details �A�j���f�[�^�̃G�C���A�X����`�F�b�N�������ۂɗ��p����
	//! @param[in] animDataAlias �A�j���f�[�^�̃G�C���A�X
	//! @return bool �Đ�����Ă��邩
	//!
	bool CheckIsPlay(std::string animDataAlias)
	{
		int index = 0;

		for(auto& indexAlias : mAnimDataAlias)
		{
			//��v���邩
			if(indexAlias == animDataAlias)
			{
				return CheckIsPlay(index);		//�v���C���Ă��邩�̃`�F�b�N
			}
			else index++;
		}

		MessageBox(NULL , "�o�^�ς݂̃A�j���f�[�^�̃G�C���A�X��������܂���ł���" , "Error" , MB_OK);
		return false;
	}

	//!
	//! @brief �A�j�����̍폜
	//! @param[in] animName �A�j���[�V�����̖��O
	//!
	void DeleteAnimInfo(std::string animName)
	{
		//���݂��Ă��邩
		if(mAnimInfo.count(animName) != 0)
		{
			DeleteAlias(animName);			//�G�C���A�X�̍폜
			mAnimInfo.erase(animName);
		}
	}

	//!
	//! @brief �A�j���[�V�����̍Đ�
	//! @param[in] animName �A�j���[�V�����̖��O
	//! @param[in] animDataIndex �A�j���f�[�^�̃C���f�b�N�X
	//!
	void Play(std::string animName , int animDataIndex)
	{
		//�A�j�����̑��݂̊m�F�A�A�j���f�[�^�C���f�b�N�X�͈̔͂̊m�F
		if(mAnimInfo.count(animName) != 0 && animDataIndex >= 0 && mAnimData.size() > animDataIndex)
		{
			//�ϐ��̏�����
			mAnimData[animDataIndex].AnimInfoName = animName;
			mAnimData[animDataIndex].IsPlay = true;

			mAnimData[animDataIndex].AnimCounter = 0;
			mAnimData[animDataIndex].AnimStartIndex = mAlias[animName].first;
			mAnimData[animDataIndex].AnimFrameMax = (mAlias[animName].second - mAlias[animName].first) + 1;

			mAnimData[animDataIndex].TimeCounter = 0.0f;
			mAnimData[animDataIndex].AnimFrameTime = mAnimInfo[animName].first / mAnimData[animDataIndex].AnimFrameMax;

			int index = mAnimData[animDataIndex].AnimStartIndex + mAnimData[animDataIndex].AnimCounter;

			*mAnimData[animDataIndex].ChangeTargetUV1 = mUVData.at(index).at(0);
			*mAnimData[animDataIndex].ChangeTargetUV2 = mUVData.at(index).at(1);
			*mAnimData[animDataIndex].ChangeTargetUV3 = mUVData.at(index).at(2);
			*mAnimData[animDataIndex].ChangeTargetUV4 = mUVData.at(index).at(3);

			//UV�X�V�����s�֐��̌Ăяo��
			if(mAnimData[animDataIndex].FunctionWhenChangingUV != nullptr)mAnimData[animDataIndex].FunctionWhenChangingUV();
		}
		else
		{
			MessageBox(NULL , "�o�^�ς݂̃A�j�����܂��̓A�j���f�[�^��������܂���ł���" , "Error" , MB_OK);
		}
	}

	//!
	//! @brief �A�j���[�V�����̍Đ�
	//! @details �A�j���f�[�^�̃G�C���A�X����A�j���[�V�������Đ�����ۂɗ��p����
	//! @param[in] animName �A�j���[�V�����̖��O
	//! @param[in] animDataAlias �A�j���f�[�^�̃G�C���A�X
	//!
	void Play(std::string animName , std::string animDataAlias)
	{
		int index = 0;

		for(auto& animAlias : mAnimDataAlias)
		{
			//��v���邩
			if(animAlias == animDataAlias)
			{
				Play(animName , index);
				return;
			}
			index++;
		}

		MessageBox(NULL , "�o�^�ς݂̃A�j���f�[�^�̃G�C���A�X��������܂���ł���" , "Error" , MB_OK);
	}

	//!
	//! @brief �A�j���[�V�����̒�~
	//! @param[in] animDataIndex �A�j���f�[�^�̃C���f�b�N�X
	//!
	void Stop(int animDataIndex)
	{
		//�͈͂Ɏ��܂��Ă��邩
		if(animDataIndex >= 0 && mAnimData.size() > animDataIndex)
		{
			//�A�j���f�[�^��������ԂɂȂ�悤���
			mAnimData[animDataIndex].AnimInfoName = "NONE";
			mAnimData[animDataIndex].IsPlay = false;

			mAnimData[animDataIndex].AnimCounter = 0;
			mAnimData[animDataIndex].AnimStartIndex = 0;
			mAnimData[animDataIndex].AnimFrameMax = 0;

			mAnimData[animDataIndex].TimeCounter = 0.0f;
			mAnimData[animDataIndex].AnimFrameTime = 0.0f;
		}
	}

	//!
	//! @brief �A�j���[�V�����̒�~
	//! @details �A�j���f�[�^�̃G�C���A�X����A�j���[�V�������~����ۂɗ��p����
	//! @param[in] animDataAlias �A�j���f�[�^�̃G�C���A�X
	//!
	void Stop(std::string animDataAlias)
	{
		int index = 0;

		for(auto& animAlias : mAnimDataAlias)
		{
			//��v���邩
			if(animAlias == animDataAlias)
			{
				Stop(index);		//�A�j���[�V�����̒�~
				return;
			}
			index++;
		}

		MessageBox(NULL , "�o�^�ς݂̃A�j���f�[�^�̃G�C���A�X��������܂���ł���" , "Error" , MB_OK);
	}

};