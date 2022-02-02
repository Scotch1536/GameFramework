//!
//!	@file
//!	@brief レンダーインターフェースのヘッダーファイル
//!

#pragma once

//! @brief レンダーインターフェースクラス
class IRender
{
public:
	//! @brief デストラクタ
	virtual ~IRender() {};

	//! @brief 描画
	virtual void Render() = 0;
};
