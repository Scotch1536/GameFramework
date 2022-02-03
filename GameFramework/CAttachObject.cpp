//!
//! @file
//! @brief �A�^�b�`�I�u�W�F�N�g�A�N�^�[�̃\�[�X�t�@�C��
//!

#include <random>

#include "GameFramework/Components/CBoxMeshComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CAttachObject.h"

CAttachObject::CAttachObject(ILevel& partner):CActor(partner)
{
	//����������쐬
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> colorGenerator(0.0f , 1.0f);
	std::uniform_real_distribution<float> scaleGenerator(15.0f , 20.0f);

	//�^�O�ǉ�
	AddTag("AttachObject");

	CColliderComponent* collider = nullptr;

	int randomNum = mt() % 2;

	if(randomNum == 0)
	{
		//�{�b�N�X���b�V���R���|�[�l���g�ǉ�&������
		CBoxMeshComponent& box = *new CBoxMeshComponent(*this , Transform , { colorGenerator(mt),colorGenerator(mt),colorGenerator(mt),1.0f });
		box.Transform.Scale = { scaleGenerator(mt),scaleGenerator(mt) ,scaleGenerator(mt) };
		mMesh = &box;

		//AABB�R���C�_�[�R���|�[�l���g�ǉ�
		collider = new CAABBColliderComponent(*this , mMesh->Transform);
	}
	else if(randomNum == 1)
	{
		//�X�t�B�A���b�V���R���|�[�l���g�ǉ�&������
		CSphereMeshComponent& sphere = *new CSphereMeshComponent(*this , Transform , { colorGenerator(mt),colorGenerator(mt),colorGenerator(mt),1.0f });
		sphere.Transform.Scale = { scaleGenerator(mt),scaleGenerator(mt) ,scaleGenerator(mt) };
		mMesh = &sphere;

		//�X�t�B�A�R���C�_�[�R���|�[�l���g�ǉ�
		collider = new CSphereColliderComponent(*this , mMesh->Transform);
	}

	collider->SetShouldUpdate(false);				//���g�ł̍X�V�����Ȃ�����
	collider->SetObjectType("AttachObject");		//�I�u�W�F�N�g�^�C�v�Z�b�g

	//�T�E���h���쐬
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/attach.wav" , 0.1f , false , "Attach");
}

void CAttachObject::EventAtBeginCollide(CActor& collideActor)
{
	//���������A�N�^�[���퓬�@�Ȃ�
	if(collideActor.HasTag("Fighter"))
	{
		//�퓬�@�Ɏ��g���A�^�b�`
		collideActor.Transform.AttachTransform(Transform);

		//�F�ύX
		XMFLOAT4 color = mMesh->GetColor();
		color.w = 0.5f;
		mMesh->SetColor(color);

		//�A�^�b�`�T�E���h�𗬂�
		CSoundManager::GetInstance().PlaySound("Attach");

		//���x���ɒʒm
		mOwnerInterface.Notice(*this);
	}
}