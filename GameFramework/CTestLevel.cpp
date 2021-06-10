#include "CTestLevel.h"
#include "CDice.h"
#include "CCameraComponent.h"
#include "CLightComponent.h"

#include "ExternalCode/DX11Settransform.h"

void CTestLevel::Init()
{
	
	CActor& buf = *new CDice(*this);

	CComponent* ref = nullptr;
	CComponent* glow = nullptr;
	if (buf.GetComponentFromAttribute(CComponent::EAttribute::CAMERA, ref))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*ref);
		this->RequestSetCamera(camera);
		if (buf.GetComponentFromAttribute(CComponent::EAttribute::LIGHT, glow))
		{
			CLightComponent& light = dynamic_cast<CLightComponent&>(*glow);
			light.Init(camera.GetEye(), XMFLOAT4(1, 1, -1, 0));
			light.SetAmbient(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));
			light.Update();
		}
	}
}