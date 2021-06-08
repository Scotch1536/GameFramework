#include "CTestLevel.h"
#include "CDice.h"
#include "CCameraComponent.h"

#include "ExternalCode/CLight.h"
#include "ExternalCode/DX11Settransform.h"

void CTestLevel::Init()
{
	CLight* light = new CLight;

	CActor& buf = *new CDice(*this);

	CComponent* ref = nullptr;
	if(buf.GetComponentFromAttribute(CComponent::EAttribute::CAMERA , ref))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*ref);
		this->RequestSetCamera(camera);
		light->Init(camera.GetEye() , XMFLOAT4(1 , 1 , -1 , 0));
		light->SetAmbient(XMFLOAT4(0.0f , 0.0f , 0.0f , 0.0f));
		light->Update();
	}

	XMFLOAT4X4 worldMTX;
	XMFLOAT3 rot = { 0.f,0.f,0.f };
	XMFLOAT3 trans = { 0.f,0.f,0.f };
	DX11MakeWorldMatrix(worldMTX , rot , trans);
	DX11MtxIdentity(worldMTX);

	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , worldMTX);
}