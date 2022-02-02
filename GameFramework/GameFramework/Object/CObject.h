//!
//!	@file
//!	@brief オブジェクトシステムのヘッダーファイル
//!

#pragma once
#include <string>

//! @brief オブジェクトクラス
class CObject
{
private:
	std::string mID;		//!< オブジェクトID

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] id オブジェクトID
	//!
	CObject(std::string id):mID(id) {};

	//! @brief デストラクタ
	virtual ~CObject() = default;

	//! @brief 更新
	virtual void Update() = 0;

	//! @brief 描画
	virtual void Render() = 0;

	const std::string& GetID()
	{
		return mID;
	}

};