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
	ILightManagerToLightComponent& mOwnerInterface;

	CLightComponent(CActor& owner) :CComponent(owner, 40),mOwnerInterface(CLightManager::GetInstance())
	{
		mOwnerInterface.AddLight(*this);
	}

public:
	static void Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location);
	static void Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location);

	virtual ~CLightComponent()
	{
		mOwnerInterface.ReleaseLight(*this);
	}

	const EType& GetType()const
	{
		return mType;
	}
};