#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"

#include "CTestLevel.h"
#include "CDice.h"

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