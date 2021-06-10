#include "CTestLevel.h"
#include "CDice.h"
#include "CCameraComponent.h"
#include "CLightComponent.h"

#include "ExternalCode/DX11Settransform.h"

void CTestLevel::Init()
{
	CActor& dice = *new CDice(*this);

	CComponent* buf = nullptr;
	if(dice.GetComponentFromAttribute(CComponent::EAttribute::CAMERA , buf))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
		this->RequestSetCamera(camera);
	}
}