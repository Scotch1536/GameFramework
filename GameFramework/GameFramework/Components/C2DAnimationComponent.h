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

		XMFLOAT2* ChangeTargetUV1;		//変更ターゲットのUV座標の参照
		XMFLOAT2* ChangeTargetUV2;
		XMFLOAT2* ChangeTargetUV3;
		XMFLOAT2* ChangeTargetUV4;

		std::function<void()> FunctionWhenChangingUV;		//UV更新時実行関数

		int AnimCounter = 0;			//アニメーションのカウンター
		int AnimStartIndex;				//アニメの開始するインデックス
		int AnimFrameMax;				//コマ数の最大値

		float TimeCounter = 0.0f;		//経過時間のカウンター
		float AnimFrameTime;			//一つのコマの時間

		bool IsPlay = false;			//再生しているか
	};

private:
	std::vector<SAnimData> mAnimData;					//アニメデータ
	std::vector<std::string> mAnimDataIndexAlias;		//アニメデータのインデックスの別名

	std::unordered_map<std::string , std::pair<float , bool>> mAnimInfo;		//アニメ情報（コマの範囲、１ループにかかる秒数、ループするかどうか）

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
			MessageBox(NULL , "登録済みのアニメ名が見つかりませんでした" , "Error" , MB_OK);
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
			MessageBox(NULL , "登録済みのアニメ情報またはアニメデータが見つかりませんでした" , "Error" , MB_OK);
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

		MessageBox(NULL , "登録済みのアニメデータの別名が見つかりませんでした" , "Error" , MB_OK);
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

		MessageBox(NULL , "登録済みのアニメデータの別名が見つかりませんでした" , "Error" , MB_OK);
	}

};