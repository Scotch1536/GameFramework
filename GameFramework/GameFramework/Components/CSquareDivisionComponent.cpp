//!
//! @file
//! @brief 四角分割コンポーネントのソースファイル
//!

#include <algorithm>

#include "CSquareDivisionComponent.h"

CSquareDivisionComponent::CSquareDivisionComponent(CActor& owner , int divWidth , int divHeight):CComponent(owner)
{
	int arraySize = divWidth * divHeight;		//配列のサイズを算出
	float ratioWidth = 1.0f / divWidth;			//分割後の横幅の比率を算出
	float ratioHeight = 1.0f / divHeight;		//分割後の縦幅の比率を算出

	mUVData.resize(arraySize);		//UVデータ配列のサイズを再設定

	//UVデータの初期化処理
	for(int i = 0; i < arraySize; ++i)
	{
		if(i == 0)
		{
			mUVData.at(i).at(0).x = 0.0f;
			mUVData.at(i).at(0).y = 0.0f;
		}
		else
		{
			if(i < divWidth)
			{
				mUVData.at(i).at(0).x = i * ratioWidth;
			}
			else
			{
				mUVData.at(i).at(0).x = i % divWidth*ratioWidth;
			}

			mUVData.at(i).at(0).y = i / divWidth * ratioHeight;
		}

		mUVData.at(i).at(1).x = mUVData.at(i).at(0).x + ratioWidth;
		mUVData.at(i).at(1).y = mUVData.at(i).at(0).y;

		mUVData.at(i).at(2).x = mUVData.at(i).at(0).x;
		mUVData.at(i).at(2).y = mUVData.at(i).at(0).y + ratioHeight;

		mUVData.at(i).at(3).x = mUVData.at(i).at(1).x;
		mUVData.at(i).at(3).y = mUVData.at(i).at(2).y;
	}
}

void CSquareDivisionComponent::GetUV(int index , std::array<XMFLOAT2 , 4>& result)
{
	//インデックスをクランプ
	index = std::clamp(index , 0 , static_cast<int>(mUVData.size() - 1));

	result = mUVData.at(index);
}

void CSquareDivisionComponent::GetUV(std::string alias , std::array<XMFLOAT2 , 4>& result)
{
	//引数の別名が存在するなら
	if(mAlias.count(alias) != 0)
	{
		if(mAlias[alias].first == mAlias[alias].second)
		{
			result = mUVData.at(mAlias[alias].first);
		}
	}
}
