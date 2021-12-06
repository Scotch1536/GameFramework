#pragma once
#include <string>

#include "../Components/CDisplay2DComponent.h"

#include "CActor.h"

class CDisplay2DActor :public CActor
{
private:
	CDisplay2DComponent* mDisplay2D = nullptr;

public:
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