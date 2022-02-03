//!
//!	@file
//!	@brief ローテーターシステムのヘッダーファイル
//!

#pragma once
#include <memory>
#include <DirectXMath.h>

#include "../Library/LCMath.h"

using namespace DirectX;

class CTransform;

//! @brief ローテータークラス
class CRotator
{
private:
	CTransform& mPartner;								//!< 自身を所有するトランスフォーム

	XMFLOAT4 mQuaternion;								//!< クォータニオン
	XMFLOAT4 mLastFrameQuaternion;						//!< 1フレーム前のクォータニオン

	bool mIsSameQuaternionToBeforeFrame = true;			//!< 1フレーム前のクォータニオンと同じか

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] partner このローテーターを所有するトランスフォーム
	//!
	CRotator(CTransform& partner);

	//! @brief 更新
	void Update();

	//!
	//! @brief 行列生成
	//! @return XMFLOAT4X4 生成した行列
	//!
	XMFLOAT4X4 GenerateMatrix();

	//!
	//! @brief 指定のロケーションに向くクォータニオンに変更する
	//! @param[in] location 向きたいロケーション
	//!
	void ChangeQuaternionToLocation(XMFLOAT3 location);

	//!
	//! @brief 指定のロケーションに向くクォータニオンを算出する
	//! @param[in] location 向きたいロケーション
	//! @param[out] result 結果のクォータニオン
	//!
	void CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& result);

	//!
	//! @brief 角度セット
	//! @param[in] angle セットする角度（オイラー角）
	//!
	void SetAngle(const XMFLOAT3& angle);

	//!
	//! @brief 角度追加（ローカル）
	//! @param[in] angle 追加する角度（オイラー角）
	//!
	void AddAngleLocal(const XMFLOAT3& angle);

	//!
	//! @brief 角度追加（ワールド）
	//! @param[in] angle 追加する角度（オイラー角）
	//!
	void AddAngleWorld(const XMFLOAT3& angle);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const bool& GetIsSameQuaternionToBeforeFrame()const
	{
		return mIsSameQuaternionToBeforeFrame;
	}

	void SetQuaternion(const XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}

};