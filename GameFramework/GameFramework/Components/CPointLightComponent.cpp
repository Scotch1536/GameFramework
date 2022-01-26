#include <functional>
#include "../Actor/CActor.h"

#include "CPointLightComponent.h"

CPointLightComponent::CPointLightComponent(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location) :
	CLightComponent(owner),
	mAttenuation(attenuation),
	Transform(owner, parentTrans)
{
	mType = EType::POINT;
	Transform.Location = location;

	//�g�����X�t�H�[���̍s��X�V�����s�֐��Ɏ��g�̃��\�b�h��ǉ�
	Transform.AddMatrixUpdateTimeFunction(std::bind(&CLightManager::Notice, std::ref(CLightManager::GetInstance())));
}