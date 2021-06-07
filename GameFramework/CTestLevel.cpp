#include "CTestLevel.h"
#include "CDice.h"
#include "CCameraComponent.h"

void CTestLevel::Init()
{
	CActor& buf = *new CDice(*this);
	//mActors.emplace_back(new CDice(*this));

	CComponent* ref = nullptr;
	if(buf.GetComponentFromAttribute(CComponent::EAttribute::CAMERA , ref))
	{
		this->RequestSetCamera(dynamic_cast<CCameraComponent&>(*ref));
	}
}