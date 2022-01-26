#pragma once
#include <DirectXMath.h>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

#include "CSquareDivisionComponent.h"

//!
//! @file
//! @brief 2Dアニメーションコンポーネントのヘッダーファイル
//!

using namespace DirectX;

//! @brief 2Dアニメーションコンポーネントクラス
class C2DAnimationComponent :public CSquareDivisionComponent
{
	//! @brief アニメデータ構造体
	struct SAnimData
	{
		std::string AnimInfoName;			//!< 再生するアニメ情報の名前

		XMFLOAT2* ChangeTargetUV1;		//!< 変更ターゲットのUV座標の参照1
		XMFLOAT2* ChangeTargetUV2;		//!< 変更ターゲットのUV座標の参照2
		XMFLOAT2* ChangeTargetUV3;		//!< 変更ターゲットのUV座標の参照3
		XMFLOAT2* ChangeTargetUV4;		//!< 変更ターゲットのUV座標の参照4

		std::function<void()> FunctionWhenChangingUV;		//!< UV更新時実行関数

		int AnimCounter = 0;			//!< アニメーションのカウンター
		int AnimStartIndex;				//!< アニメの開始するインデックス
		int AnimFrameMax;				//!< コマ数の最大値

		float TimeCounter = 0.0f;		//!< 経過時間のカウンター
		float AnimFrameTime;			//!< 一つのコマの時間

		bool IsPlay = false;			//!< 再生しているか
	};

private:
	std::vector<SAnimData> mAnimData;				//!< アニメデータ（アニメーションを行う際の変更先の情報）
	std::vector<std::string> mAnimDataAlias;		//!< アニメデータののエイリアス

	std::unordered_map<std::string , std::pair<float , bool>> mAnimInfo;		//!< アニメ情報（コマの範囲、１ループにかかる秒数、ループするかどうか）

	//! @brief 更新
	void Update()override;

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] divWidth アニメーション素材の横幅の分割数
	//! @param[in] divHeight アニメーション素材の縦幅の分割数
	//!
	C2DAnimationComponent(CActor& owner , int divWidth , int divHeight);

	//!
	//! @brief アニメデータの追加
	//! @param[in] changeUV1 変更するUV情報1つ目
	//! @param[in] changeUV2 変更するUV情報2つ目
	//! @param[in] changeUV3 変更するUV情報3つ目
	//! @param[in] changeUV4 変更するUV情報4つ目
	//! @param[in] functionWhenChangingUV UVが変更された時に追加で呼びたい関数
	//! @param[in] alias 別名
	//!
	void AddAnimData(XMFLOAT2* changeUV1 , XMFLOAT2* changeUV2 , XMFLOAT2* changeUV3 , XMFLOAT2* changeUV4 ,
		std::function<void()> functionWhenChangingUV , std::string alias = "NONE");

	//!
	//! @brief アニメ情報の追加
	//! @details 新規にアニメ情報を追加する際に利用する
	//! @param[in] animName アニメーションの名前 
	//! @param[in] start 開始のコマのインデックス
	//! @param[in] finish 終了のコマのインデックス
	//! @param[in] oneLoopTime アニメーションが一周する秒数
	//! @param[in] isLoop ループするか
	//!
	void AddAnimInfo(std::string animName , int start , int finish , float oneLoopTime , bool isLoop)
	{
		AddAlias(start , finish , animName);				//エイリアスの追加
		mAnimInfo[animName] = { oneLoopTime,isLoop };		//アニメ情報の初期化
	}

	//!
	//! @brief アニメ情報の追加
	//! @details 既にエイリアスで範囲分けしている部分にアニメ情報のみ追加する際に利用する
	//! @param[in] alias 
	//! @param[in] oneLoopTime アニメーションが一周する秒数
	//! @param[in] isLoop ループするか
	//!
	void AddAnimInfo(std::string alias , float oneLoopTime , bool isLoop)
	{
		//存在しているか
		if(mAlias.count(alias) != 0)
		{
			mAnimInfo[alias] = { oneLoopTime,isLoop };		//アニメ情報の初期化
		}
		else
		{
			MessageBox(NULL , "登録済みのエイリアスが見つかりませんでした" , "Error" , MB_OK);
		}
	}

	//!
	//! @brief アニメデータの削除
	//! @param[in] index アニメデータが格納されている配列のインデックス
	//!
	void DeleteAnimData(int index)
	{
		//インデックスが範囲内に収まっているか
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
	//! @brief アニメデータの削除
	//! @details アニメデータのエイリアスからアニメデータを削除する際に利用する
	//! @param[in] animDataAlias アニメデータのエイリアス
	//!
	void DeleteAnimData(std::string animDataAlias)
	{
		int index = 0;

		for(auto& indexAlias : mAnimDataAlias)
		{
			//一致するか
			if(indexAlias == animDataAlias)
			{
				DeleteAnimData(index);		//アニメデータの削除
				return;
			}
			else index++;
		}

		MessageBox(NULL , "登録済みのアニメデータのエイリアスが見つかりませんでした" , "Error" , MB_OK);
	}

	//!
	//! @brief アニメーションが再生されているかのチェック
	//! @param[in] index アニメデータが格納されている配列のインデックス
	//!
	bool CheckIsPlay(int index)
	{
		//インデックスが範囲内に収まっているか
		if(index >= 0 && index < mAnimData.size())
		{
			return mAnimData.at(index).IsPlay;
		}
		else
		{
			MessageBox(NULL , "アニメデータが見つかりませんでした" , "Error" , MB_OK);
			return false;
		}
	}	
	
	//!
	//! @brief アニメーションが再生されているかのチェック
	//! @details アニメデータのエイリアスからチェックしたい際に利用する
	//! @param[in] animDataAlias アニメデータのエイリアス
	//!
	bool CheckIsPlay(std::string animDataAlias)
	{
		int index = 0;

		for(auto& indexAlias : mAnimDataAlias)
		{
			//一致するか
			if(indexAlias == animDataAlias)
			{
				return CheckIsPlay(index);		//プレイしているかのチェック
			}
			else index++;
		}

		MessageBox(NULL , "登録済みのアニメデータのエイリアスが見つかりませんでした" , "Error" , MB_OK);
		return false;
	}

	//!
	//! @brief アニメ情報の削除
	//! @param[in] animName アニメーションの名前
	//!
	void DeleteAnimInfo(std::string animName)
	{
		//存在しているか
		if(mAnimInfo.count(animName) != 0)
		{
			DeleteAlias(animName);			//エイリアスの削除
			mAnimInfo.erase(animName);
		}
	}

	//!
	//! @brief アニメーションの再生
	//! @param[in] animName アニメーションの名前
	//! @param[in] animDataIndex アニメデータのインデックス
	//!
	void Play(std::string animName , int animDataIndex)
	{
		//アニメ情報の存在の確認、アニメデータインデックスの範囲の確認
		if(mAnimInfo.count(animName) != 0 && animDataIndex >= 0 && mAnimData.size() > animDataIndex)
		{
			//変数の初期化
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

			//UV更新時実行関数の呼び出し
			if(mAnimData[animDataIndex].FunctionWhenChangingUV != nullptr)mAnimData[animDataIndex].FunctionWhenChangingUV();
		}
		else
		{
			MessageBox(NULL , "登録済みのアニメ情報またはアニメデータが見つかりませんでした" , "Error" , MB_OK);
		}
	}

	//!
	//! @brief アニメーションの再生
	//! @details アニメデータのエイリアスからアニメーションを再生する際に利用する
	//! @param[in] animName アニメーションの名前
	//! @param[in] animDataAlias アニメデータのエイリアス
	//!
	void Play(std::string animName , std::string animDataAlias)
	{
		int index = 0;

		for(auto& animAlias : mAnimDataAlias)
		{
			//一致するか
			if(animAlias == animDataAlias)
			{
				Play(animName , index);
				return;
			}
			index++;
		}

		MessageBox(NULL , "登録済みのアニメデータのエイリアスが見つかりませんでした" , "Error" , MB_OK);
	}

	//!
	//! @brief アニメーションの停止
	//! @param[in] animDataIndex アニメデータのインデックス
	//!
	void Stop(int animDataIndex)
	{
		//範囲に収まっているか
		if(animDataIndex >= 0 && mAnimData.size() > animDataIndex)
		{
			//アニメデータを初期状態になるよう代入
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
	//! @brief アニメーションの停止
	//! @details アニメデータのエイリアスからアニメーションを停止する際に利用する
	//! @param[in] animDataAlias アニメデータのエイリアス
	//!
	void Stop(std::string animDataAlias)
	{
		int index = 0;

		for(auto& animAlias : mAnimDataAlias)
		{
			//一致するか
			if(animAlias == animDataAlias)
			{
				Stop(index);		//アニメーションの停止
				return;
			}
			index++;
		}

		MessageBox(NULL , "登録済みのアニメデータのエイリアスが見つかりませんでした" , "Error" , MB_OK);
	}

};