//!
//! @file
//! @brief カメラアクターのヘッダーファイル
//!

#pragma once
#include <string>

#include "../Components/CDisplay2DComponent.h"

#include "CActor.h"

//! @brief ディスプレイ2Dアクタークラス
class CDisplay2DActor :public CActor
{
private:
	CDisplay2DComponent* mDisplay2D = nullptr;		//!< ディスプレイ2Dコンポーネント

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] partner このアクターを所有するレベル
	//! @param[in] color 色情報
	//! @param[in] texturePath テクスチャファイルのパス
	//!
	CDisplay2DActor(ILevel& partner , const XMFLOAT4& color , std::string texturePath = "NONE"):CActor(partner)
	{
		if(texturePath == "NONE")
		{
			mDisplay2D = new CDisplay2DComponent(*this , Transform , color);
		}
		else
		{
			mDisplay2D = new CDisplay2DComponent(*this , Transform , texturePath , color);
		}
	}

	//!
	//! @brief コンストラクタ
	//! @param[in] partner このアクターを所有するレベル
	//! @param[in] texturePath テクスチャファイルのパス
	//!
	CDisplay2DActor(ILevel& partner , std::string texturePath):CActor(partner)
	{
		mDisplay2D = new CDisplay2DComponent(*this , Transform , texturePath , { 1.0f,1.0f,1.0f,1.0f });
	}

	const XMFLOAT4& GetColor()const
	{
		return mDisplay2D->GetColor();
	}

	CDisplay2DComponent& GetDisplay2D()
	{
		return *mDisplay2D;
	}

	void SetColor(const XMFLOAT4& color)
	{
		if(mDisplay2D != nullptr)mDisplay2D->SetColor(color);
	}
};