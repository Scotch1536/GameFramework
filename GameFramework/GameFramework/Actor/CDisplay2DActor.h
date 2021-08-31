#pragma once
#include <string>

#include "../Components/CDisplay2DComponent.h"

#include "CActor.h"

class CDisplay2DActor :public CActor
{
private:
	CDisplay2DComponent<SVertex2DColor>* mDisplay2DColor = nullptr;

public:
	CDisplay2DActor(ILevel& partner , XMFLOAT4 color):CActor(partner)
	{
		mDisplay2DColor = new CDisplay2DComponent<SVertex2DColor>(*this , Transform , color);
	}
	CDisplay2DActor(ILevel& partner , std::string texturePath):CActor(partner)
	{
		new CDisplay2DComponent<SVertex2DUV>(*this , Transform , texturePath);
	}

	void SetColor(const XMFLOAT4& color)
	{
		if(mDisplay2DColor != nullptr)mDisplay2DColor->SetColor(color);
	}
};