#include "../Managers/CGameManager.h"

#include "C2DAnimationComponent.h"

//!
//! @file
//! @brief 2Dアニメーションコンポーネントのソースファイル
//!

C2DAnimationComponent::C2DAnimationComponent(CActor& owner , int divWidth , int divHeight)
	:CSquareDivisionComponent(owner , divWidth , divHeight)
{}

void C2DAnimationComponent::AddAnimData(XMFLOAT2* changeUV1 , XMFLOAT2* changeUV2 , XMFLOAT2* changeUV3 , XMFLOAT2* changeUV4 ,
	std::function<void()> functionWhenChangingUV , std::string alias)
{
	mAnimData.emplace_back();			//アニメデータ追加
	mAnimDataAlias.emplace_back();		//アニメデータエイリアス追加

	//メンバの初期化
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
		//アニメ情報のループ設定がtrueかつアニメが停止していたらアニメを再開する
		if(mAnimInfo[anim.AnimInfoName].second && !anim.IsPlay)anim.IsPlay = true;

		//アニメが停止している設定ならcontinueで処理をとばす
		if(!anim.IsPlay)continue;

		//タイムカウンターにデルタタイムを加算
		anim.TimeCounter += CGameManager::GetInstance().GetDeltaTime();

		//変更するコマ数を算出
		int changeNum = anim.TimeCounter / anim.AnimFrameTime;

		if(changeNum >= 1)
		{
			anim.AnimCounter += changeNum;								//アニメカウンター加算
			anim.TimeCounter -= anim.AnimFrameTime * changeNum;			//タイムカウンター減算

			//アニメカウンターがアニメのコマ数の最大値を超えているか
			if(anim.AnimCounter > anim.AnimFrameMax - 1)
			{
				//ループ設定がtrueか
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

			//インデックスの算出
			int index = anim.AnimStartIndex + anim.AnimCounter;

			//UVの変更
			*anim.ChangeTargetUV1 = mUVData.at(index).at(0);
			*anim.ChangeTargetUV2 = mUVData.at(index).at(1);
			*anim.ChangeTargetUV3 = mUVData.at(index).at(2);
			*anim.ChangeTargetUV4 = mUVData.at(index).at(3);

			//UV変更時実行関数の呼び出し
			if(anim.FunctionWhenChangingUV != nullptr)anim.FunctionWhenChangingUV();
		}
	}
}