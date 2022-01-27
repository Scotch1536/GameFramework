//!
//! @file
//! @brief ���C�g�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

#include "CComponent.h"
#include "../Managers/CLightManager.h"

class CTransform;

//! @brief ���C�g�R���|�[�l���g�N���X
class CLightComponent :public CComponent
{
public:
	//! @brief ���C�g�^�C�v�񋓌^
	enum EType
	{
		NONE ,
		POINT ,
		SPOT ,
	};

protected:
	EType mType = EType::NONE;								//!< ���C�g�^�C�v
	ILightManagerToLightComponent& mOwnerInterface;			//!< ���C�g�}�l�[�W���[�̃C���^�[�t�F�[�X

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//!
	CLightComponent(CActor& owner):CComponent(owner , 40) , mOwnerInterface(CLightManager::GetInstance())
	{
		//���C�g�}�l�[�W���[�Ɏ��g�̃��C�g��ǉ����Ă��炤
		mOwnerInterface.AddLight(*this);
	}

public:
	//!
	//! @brief ���C�g���쐬
	//! @details �|�C���g���C�g���쐬�����
	//! param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! param[in] parentTrans �e�̃g�����X�t�H�[��
	//! param[in] attenuation ������
	//! param[in] location ���P�[�V����
	//!
	static void Create(CActor& owner , CTransform& parentTrans , XMFLOAT4 attenuation , XMFLOAT3 location);

	//!
	//! @brief ���C�g���쐬
	//! @details �X�|�b�g���C�g���쐬�����
	//! param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! param[in] parentTrans �e�̃g�����X�t�H�[��
	//! param[in] attenuation ������
	//! param[in] direction ����
	//! param[in] angle �p�x�i���C�g�̍L����j
	//! param[in] location ���P�[�V����
	//!
	static void Create(CActor& owner , CTransform& parentTrans , XMFLOAT4 attenuation , XMFLOAT3 direction , float angle , XMFLOAT3 location);

	//! @brief �f�X�g���N�^
	virtual ~CLightComponent()
	{
		//���C�g�}�l�[�W���[�Ɏ��g�̃��C�g��؂藣���Ă��炤
		mOwnerInterface.ReleaseLight(*this);
	}

	const EType& GetType()const
	{
		return mType;
	}
};