#pragma once
#include <DirectXMath.h>
#include <vector>
#include <array>
#include <unordered_map>
#include <string>

#include "CComponent.h"

//!
//! @file
//! @brief 四角分割コンポーネントのヘッダーファイル
//!

using namespace DirectX;

//! @brief 四角分割コンポーネントクラス
class  CSquareDivisionComponent :public CComponent
{
protected:
	std::unordered_map<std::string , std::pair<int , int>> mAlias;		//!< 別名
	std::vector<std::array<XMFLOAT2 , 4>> mUVData;						//!< UVデータ

	//!
	//! @brief 別名の追加
	//! @details 範囲指定で別名を追加する際に利用する
	//! 子クラスの2Dアニメーションで使用するメソッド
	//! @param[in] start 開始のUVデータ配列のインデックス
	//! @param[in] finish 終了のUVデータ配列のインデックス
	//! @param[in] alias 追加したい別名
	//!
	void AddAlias(int start , int finish , std::string alias)
	{
		mAlias[alias].first = start;
		mAlias[alias].second = finish;
	};

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] divWidth 横幅の分割数
	//! @param[in] divHeight 縦幅の分割数
	//!
	CSquareDivisionComponent(CActor& owner , int divWidth , int divHeight);

	//!
	//! @brief UVデータの取得
	//! @details UVデータ配列のインデックスからUVデータを取得する際に利用する
	//! @param[in] index 取得したいUVデータ配列のインデックス
	//! @param[out] result 結果のUVデータ
	//!
	void GetUV(int index , std::array<XMFLOAT2 , 4>& result);

	//!
	//! @brief UVデータの取得
	//! @details 別名からUVデータを取得する際に利用する
	//! @param[in] alias 取得したいUVデータの別名
	//! @param[out] result 結果のUVデータ
	//!
	void GetUV(std::string alias , std::array<XMFLOAT2 , 4>& result);

	//!
	//! @brief 別名の追加
	//! @details 1つのインデックスに別名を追加する際に利用する
	//! @param[in] index 開始のUVデータ配列のインデックス
	//! @param[in] alias 追加したい別名
	//!
	void AddAlias(int index , std::string alias)
	{
		mAlias[alias].first = index;
		mAlias[alias].second = index;
	};

	//!
	//! @brief 別名の削除
	//! @param[in] alias 削除したい別名
	//!
	void DeleteAlias(std::string alias)
	{
		//引数の別名が存在するなら削除する
		if(mAlias.count(alias) != 0)mAlias.erase(alias);
	}

};