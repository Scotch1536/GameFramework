//!
//! @file
//! @brief �X�J�C�h�[���A�N�^�[�̃\�[�X�t�@�C��
//!

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"

#include "CSkyDome.h"

CSkyDome::CSkyDome(ILevel& owner):CActor(owner)
{
	//�X�^�e�B�b�N���b�V���R���|�[�l���g�ǉ�&������
	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Skydome/Dome_BB601.x" , "Assets/Models/Skydome/") ,
		"Shader/vs.hlsl" , "Shader/pstexcol.hlsl");
	mesh.Transform.Scale = { 10.0f,10.0f,10.0f };
}