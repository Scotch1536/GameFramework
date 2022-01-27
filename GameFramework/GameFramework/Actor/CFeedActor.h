//!
//! @file
//! @brief フェードアクターのヘッダーファイル
//!

#pragma once
#include <functional>

#include "../Game/CApplication.h"
#include "../Level/CLevel.h"

#include "CActor.h"
#include "CDisplay2DActor.h"

//! @brief フェードアクタークラス
class CFeedActor :public CActor
{
public:
	//! @brief フェードオプション列挙型
	enum class EOption
	{
		FEEDOUT ,
		FEEDIN
	};

private:
	EOption mOption;								//!< フェードオプション

	CDisplay2DActor* mFeedScreen;					//!< フェードのためのスクリーンサイズの2Dメッシュ

	std::function<void()> mDoAfterFeedEvent;		//!< フェード終了後に行うイベント

	float mAlpha;									//!< アルファ値
	float mIncreaseAlpha;							//!< アルファ値の増加量

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] partner このアクターを所有するレベル
	//! @param[in] event フェード終了後に行うイベント
	//! @param[in] feedOption フェードオプションパス
	//! @param[in] color 色情報
	//! @param[in] feedTime フェードが終わるまでにかかる秒数
	//!
	CFeedActor(ILevel& partner , std::function<void()> event , EOption feedOption , XMFLOAT3 color = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f):CActor(partner) ,
		mDoAfterFeedEvent(event) , mOption(feedOption) , mIncreaseAlpha(1.0f / (feedTime*60.0f))
	{
		if(mOption == EOption::FEEDOUT)mAlpha = 0.0f;
		else if(mOption == EOption::FEEDIN)	mAlpha = 1.0f;

		//フェードスクリーン作成&初期化
		mFeedScreen = new CDisplay2DActor(mOwnerInterface , XMFLOAT4(color.x , color.y , color.z , mAlpha));
		mFeedScreen->Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH) / 2;
		mFeedScreen->Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT) / 2;
		mFeedScreen->Transform.Scale.x = CApplication::CLIENT_WIDTH;
		mFeedScreen->Transform.Scale.y = CApplication::CLIENT_HEIGHT;
	}

	void Tick()override
	{
		bool isFeedEnd = false;

		//アルファ値の更新
		if(mOption == EOption::FEEDOUT)mAlpha += mIncreaseAlpha;
		else if(mOption == EOption::FEEDIN)	mAlpha -= mIncreaseAlpha;

		//フェードの終了の確認
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

		//色（アルファ値）の更新
		XMFLOAT4 color = mFeedScreen->GetColor();
		color.w = mAlpha;
		mFeedScreen->SetColor(color);

		if(isFeedEnd)
		{
			//フェード終了後イベントがあるなら実行
			if(mDoAfterFeedEvent != nullptr)mDoAfterFeedEvent();

			//自身の破壊
			Destroy();
		}
	}
};