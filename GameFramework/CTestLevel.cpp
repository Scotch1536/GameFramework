#include "CTestLevel.h"
#include "CDice.h"
#include "CCameraComponent.h"
#include "CLightComponent.h"

#include "ExternalCode/DX11Settransform.h"

void CTestLevel::Init()
{
	CActor& buf = *new CDice(*this);

	CComponent* ref = nullptr;
	if (buf.GetComponentFromAttribute(CComponent::EAttribute::CAMERA, ref))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*ref);
		this->RequestSetCamera(camera);
	}
}