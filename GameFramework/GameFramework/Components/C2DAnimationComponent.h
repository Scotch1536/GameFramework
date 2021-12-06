#pragma once
#include <DirectXMath.h>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

#include "CSquareDivisionComponent.h"

using namespace DirectX;

class C2DAnimationComponent :public CSquareDivisionComponent
{
	struct SAnimData
	{
		std::string AnimName;

		XMFLOAT2* ChangeTargetUV1;		//�ύX�^�[�Q�b�g��UV���W�̎Q��
		XMFLOAT2* ChangeTargetUV2;
		XMFLOAT2* ChangeTargetUV3;
		XMFLOAT2* ChangeTargetUV4;

		std::function<void()> FunctionWhenChangingUV;		//UV�X�V�����s�֐�

		int AnimCounter = 0;			//�A�j���[�V�����̃J�E���^�[
		int AnimStartIndex;				//�A�j���̊J�n����C���f�b�N�X
		int AnimFrameMax;				//�R�}���̍ő�l

		float TimeCounter = 0.0f;		//�o�ߎ��Ԃ̃J�E���^�[
		float AnimFrameTime;			//��̃R�}�̎���

		bool IsPlay = false;			//�Đ����Ă��邩
	};

private:
	std::vector<SAnimData> mAnimData;					//�A�j���f�[�^
	std::vector<std::string> mAnimDataIndexAlias;		//�A�j���f�[�^�̃C���f�b�N�X�̕ʖ�

	std::unordered_map<std::string , std::pair<float , bool>> mAnimInfo;		//�A�j�����i�R�}�͈̔́A�P���[�v�ɂ�����b���A���[�v���邩�ǂ����j

	void Update()override;

public:
	C2DAnimationComponent(CActor& owner , int divWidth , int divHeight);

	void AddAnimData(XMFLOAT2* changeUV1 , XMFLOAT2* changeUV2 , XMFLOAT2* changeUV3 , XMFLOAT2* changeUV4 ,
		std::function<void()> functionWhenChangingUV , std::string alias = "NONE");

	void AddAnimInfo(std::string animName , float oneLoopTime , bool isLoop)
	{
		if(mAlias.count(animName) != 0)
		{
			mAnimInfo[animName] = { oneLoopTime,isLoop };
		}
		else
		{
			MessageBox(NULL , "�o�^�ς݂̃A�j������������܂���ł���" , "Error" , MB_OK);
		}
	}

	void AddAnimInfo(std::string animName , int first , int finish , float oneLoopTime , bool isLoop)
	{
		AddAlias(first , finish , animName);
		mAnimInfo[animName] = { oneLoopTime,isLoop };
	}

	void DeleteAnimData(int index)
	{
		if(index < mAnimData.size())
		{
			auto itr = mAnimData.begin();
			auto itr2 = mAnimDataIndexAlias.begin();

			mAnimData.erase(itr + index);
			mAnimDataIndexAlias.erase(itr2 + index);
			mAnimData.shrink_to_fit();
			mAnimDataIndexAlias.shrink_to_fit();
		}
	}

	void DeleteAnimInfo(std::string animName)
	{
		if(mAnimInfo.count(animName) != 0)
		{
			DeleteAlias(animName);
			mAnimInfo.erase(animName);
		}
	}

	void Play(std::string animName , int animDataIndex)
	{
		if(mAnimInfo.count(animName) != 0 && mAnimData.size() > animDataIndex)
		{
			mAnimData[animDataIndex].AnimName = animName;
			mAnimData[animDataIndex].IsPlay = true;

			mAnimData[animDataIndex].AnimCounter = 0;
			mAnimData[animDataIndex].AnimStartIndex = mAlias[animName].first;
			mAnimData[animDataIndex].AnimFrameMax = mAlias[animName].second - mAlias[animName].first;

			mAnimData[animDataIndex].TimeCounter = 0.0f;
			mAnimData[animDataIndex].AnimFrameTime = mAnimInfo[animName].first / mAnimData[animDataIndex].AnimFrameMax;

			int index = mAnimData[animDataIndex].AnimStartIndex + mAnimData[animDataIndex].AnimCounter;

			*mAnimData[animDataIndex].ChangeTargetUV1 = mUVDivisionData.at(index).at(0);
			*mAnimData[animDataIndex].ChangeTargetUV2 = mUVDivisionData.at(index).at(1);
			*mAnimData[animDataIndex].ChangeTargetUV3 = mUVDivisionData.at(index).at(2);
			*mAnimData[animDataIndex].ChangeTargetUV4 = mUVDivisionData.at(index).at(3);

			mAnimData[animDataIndex].FunctionWhenChangingUV();
		}
		else
		{
			MessageBox(NULL , "�o�^�ς݂̃A�j�����܂��̓A�j���f�[�^��������܂���ł���" , "Error" , MB_OK);
		}
	}

	void Play(std::string animName , std::string animDataAlias)
	{
		int index = 0;

		for(auto& animAlias : mAnimDataIndexAlias)
		{
			if(animAlias == animDataAlias)
			{
				Play(animName , index);
				return;
			}
			index++;
		}

		MessageBox(NULL , "�o�^�ς݂̃A�j���f�[�^�̕ʖ���������܂���ł���" , "Error" , MB_OK);
	}

	void Stop(int animDataIndex)
	{
		if(mAnimData.size() > animDataIndex)
		{
			mAnimData[animDataIndex].AnimName = "NONE";
			mAnimData[animDataIndex].IsPlay = false;

			mAnimData[animDataIndex].AnimCounter = 0;
			mAnimData[animDataIndex].AnimStartIndex = 0;
			mAnimData[animDataIndex].AnimFrameMax = 0;

			mAnimData[animDataIndex].TimeCounter = 0.0f;
			mAnimData[animDataIndex].AnimFrameTime = 0.0f;
		}
	}

	void Stop(std::string animDataAlias)
	{
		int index = 0;

		for(auto& animAlias : mAnimDataIndexAlias)
		{
			if(animAlias == animDataAlias)
			{
				Stop(index);
				return;
			}
			index++;
		}

		MessageBox(NULL , "�o�^�ς݂̃A�j���f�[�^�̕ʖ���������܂���ł���" , "Error" , MB_OK);
	}

};