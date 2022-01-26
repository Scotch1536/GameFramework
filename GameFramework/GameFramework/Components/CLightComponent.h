#pragma once
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

#include "CComponent.h"
#include "../Managers/CLightManager.h"

//!
//! @file
//! @brief ライトコンポーネントのヘッダーファイル
//!

class CTransform;

//! @brief ライトコンポーネントクラス
class CLightComponent :public CComponent
{
public:
	//! @brief ライトタイプ列挙型
	enum EType
	{
		NONE ,
		POINT ,
		SPOT ,
	};

protected:
	EType mType = EType::NONE;								//!< ライトタイプ
	ILightManagerToLightComponent& mOwnerInterface;			//!< ライトマネージャーのインターフェース

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//!
	CLightComponent(CActor& owner):CComponent(owner , 40) , mOwnerInterface(CLightManager::GetInstance())
	{
		//ライトマネージャーに自身のライトを追加してもらう
		mOwnerInterface.AddLight(*this);
	}

public:
	//!
	//! @brief ライトを作成
	//! @details ポイントライトが作成される
	//! param[in] owner このコンポーネントの所有者
	//! param[in] parentTrans 親のトランスフォーム
	//! param[in] attenuation 減衰率
	//! param[in] location ロケーション
	//!
	static void Create(CActor& owner , CTransform& parentTrans , XMFLOAT4 attenuation , XMFLOAT3 location);

	//!
	//! @brief ライトを作成
	//! @details スポットライトが作成される
	//! param[in] owner このコンポーネントの所有者
	//! param[in] parentTrans 親のトランスフォーム
	//! param[in] attenuation 減衰率
	//! param[in] direction 向き
	//! param[in] angle 角度（ライトの広がり）
	//! param[in] location ロケーション
	//!
	static void Create(CActor& owner , CTransform& parentTrans , XMFLOAT4 attenuation , XMFLOAT3 direction , float angle , XMFLOAT3 location);

	//! @brief デストラクタ
	virtual ~CLightComponent()
	{
		//ライトマネージャーに自身のライトを切り離してもらう
		mOwnerInterface.ReleaseLight(*this);
	}

	const EType& GetType()const
	{
		return mType;
	}
};