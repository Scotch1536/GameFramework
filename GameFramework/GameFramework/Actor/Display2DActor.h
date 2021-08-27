#pragma once
#include "../Components/CDisplay2DComponent.h"

#include "CActor.h"

class CDisplay2DActor :public CActor
{
private:
	CDisplay2DComponent<SVertex2DColor>* mDisplay2D = nullptr;

public:
	CDisplay2DActor(ILevel& partner , XMFLOAT4 color):CActor(partner)
	{
		mDisplay2D = new CDisplay2DComponent<SVertex2DColor>(*this , Transform , color);
	}

	void SetColor(const XMFLOAT4& color)
	{
		mDisplay2D->SetColor(color);
	}
};