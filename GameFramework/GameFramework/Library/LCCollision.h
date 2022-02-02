//!
//!	@file
//!	@brief コリジョンライブラリのヘッダーファイル
//!

#pragma once
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

//! @brief コリジョンライブラリクラス
static class LCCollision
{
public:
	//!
	//! @brief 当たり判定
	//! @details AABBとAABBの当たり判定の際に利用する
	//! @param[in] min1 1つ目のAABBの最小値
	//! @param[in] max1 1つ目のAABBの最大値
	//! @param[in] min2 1つ目のAABBの最小値
	//! @param[in] max2 1つ目のAABBの最大値
	//! @return bool 当たっているか
	//!
	static bool IsCollide(const XMFLOAT3& min1, const XMFLOAT3& max1, const XMFLOAT3& min2, const XMFLOAT3& max2);

	//!
	//! @brief 当たり判定
	//! @details AABBと点の当たり判定の際に利用する
	//! @param[in] min AABBの最小値
	//! @param[in] max AABBの最大値
	//! @param[in] point 点のロケーション
	//! @return bool 当たっているか
	//!
	static bool IsCollide(const XMFLOAT3& min, const XMFLOAT3& max, const XMFLOAT3& point);

	//!
	//! @brief 当たり判定
	//! @details スフィアとスフィアの当たり判定の際に利用する
	//! @param[in] center1 1つ目のスフィアの中心座標
	//! @param[in] radius1 1つ目のスフィアの半径
	//! @param[in] center2 2つ目のスフィアの中心座標
	//! @param[in] radius2 2つ目のスフィアの半径
	//! @return bool 当たっているか
	//!
	static bool IsCollide(const XMFLOAT3& center1,const float& radius1, const XMFLOAT3& center2, const float& radius2);

	//!
	//! @brief 当たり判定
	//! @details AABBとスフィアの当たり判定の際に利用する
	//! @param[in] min AABBの最小値
	//! @param[in] max AABBの最大値
	//! @param[in] center スフィアの中心座標
	//! @param[in] radius スフィアの半径
	//! @return bool 当たっているか
	//!
	static bool IsCollide(const XMFLOAT3& min, const XMFLOAT3& max, const XMFLOAT3& center, const float& radius);
};
