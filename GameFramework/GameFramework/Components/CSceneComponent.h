//!
//! @file
//! @brief �V�[���R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "../Transform/CTransform.h"
#include "../Actor/CActor.h"

#include "CComponent.h"

//! @brief �V�[���R���|�[�l���g�N���X
class CSceneComponent :public CComponent
{
public:
	CTransform Transform;		//!< �g�����X�t�H�[��

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//!
	CSceneComponent(CActor& owner , CTransform& parentTrans):CComponent(owner) , Transform(owner , parentTrans) {};

};