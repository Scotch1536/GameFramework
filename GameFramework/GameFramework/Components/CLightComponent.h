#pragma once
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

#include "CComponent.h"
#include "../Managers/CLightManager.h"

class CTransform;

class CLightComponent :public CComponent
{
public:
	enum EType
	{
		POINT,
		SPOT,
		NONE
	};

protected:
	EType mType = EType::NONE;

	CLightComponent(CActor& owner, int priority) :CComponent(owner, priority)
	{
		CLightManager::GetInstance().AddLight(*this);
	}

public:
	static void Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location);
	static void Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location);

	virtual ~CLightComponent()
	{
		CLightManager::GetInstance().ReleaseLight(*this);
	}

	const EType& GetType()const
	{
		return mType;
	}
};