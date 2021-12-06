#pragma once
#include <string>

#include "../Components/CDisplay2DComponent.h"

#include "CActor.h"

class CDisplay2DActor :public CActor
{
private:
	CDisplay2DComponent* mDisplay2D = nullptr;

public:
	CDisplay2DActor(ILevel& partner , const XMFLOAT4& color , std::string texturePath):CActor(partner)
	{
		mDisplay2D = new CDisplay2DComponent(*this , Transform , color , texturePath);
	}

	CDisplay2DActor(ILevel& partner , const XMFLOAT4& color):CActor(partner)
	{
		mDisplay2D = new CDisplay2DComponent(*this , Transform , color);
	}
	
	CDisplay2DActor(ILevel& partner , std::string texturePath):CActor(partner)
	{
		mDisplay2D = new CDisplay2DComponent(*this , Transform , texturePath);
	}

	const XMFLOAT4& GetColor()const
	{
		return mDisplay2D->GetColor();
	}

	XMFLOAT2& GetUV(int index)
	{
		return mDisplay2D->GetUV(index);
	}

	void SetColor(const XMFLOAT4& color)
	{
		if(mDisplay2D != nullptr)mDisplay2D->SetColor(color);
	}
};