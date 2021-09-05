#pragma once
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

#include "CComponent.h"
#include "../Managers/CLightManager.h"

class CLightComponent :public CComponent
{
private:
	
	XMFLOAT4 mLightPos;			
	
public:
	CLightComponent(CActor& owner , int priority = 40):CComponent(owner , priority)
	{		
		CLightManager::GetInstance().AddLight(*this);
	}
	
	~CLightComponent()
	{
		CLightManager::GetInstance().ReleaseLight(*this);
	}

	//çXêV
	void Update()override
	{
		
	}

	void SetLightPos(XMFLOAT4 pos)
	{
		mLightPos = pos;
	}

};