//!
//!	@file
//!	@brief �g�����X�t�H�[���V�X�e���̃w�b�_�[�t�@�C��
//!

#pragma once
#include <vector>
#include <memory>
#include <array>
#include <functional>
#include <DirectXMath.h>

#include "CRotator.h"

using namespace DirectX;

class CChildTransform;
class IActor;

//! @brief �g�����X�t�H�[���N���X
class CTransform final
{
public:
	//! @brief �A�^�b�`�I�v�V�����񋓌^
	enum class EAttachOption
	{
		DEFAULT = 0b00 ,			//!< �f�t�H���g
		LOCATION_ONLY = 0b01 ,		//!< ���P�[�V�����̂�
	};

private:
	EAttachOption mAttachOption = EAttachOption::DEFAULT;			//!< �A�^�b�`�I�v�V����

	XMFLOAT4X4 mWorldMatrix;										//!< ���[���h�ϊ��s��
	XMFLOAT4X4 mLocalMatrix;										//!< ���[�J���ϊ��s��

	CTransform* mParentTransform = nullptr;							//!< �e�g�����X�t�H�[��
	std::vector<CTransform*> mChildTransform;						//!< �q�g�����X�t�H�[��

	XMFLOAT3 mLastFrameLocation = { 0.f,0.f,0.f };					//!< �O�t���[���̃��P�[�V����
	XMFLOAT3 mLastFrameScale = { 0.f,0.f,0.f };						//!< �O�t���[���̃X�P�[��

	IActor& mOwnerInterface;										//!< ���g�����L����A�N�^�[�̃C���^�[�t�F�[�X

	std::vector<std::function<void()>> mEventWhenMatrixUpdate;		//!< �s��X�V�����s�C�x���g

	bool mShouldUpdateMatrix = true;								//!< �s����X�V���ׂ���
	bool mIgnoreUpdateMatrixOnce = false;							//!< ��x�s��̍X�V�𖳎����邩
	bool mIsChild = false;											//!< �������q�g�����X�t�H�[����
	bool mIsBillboard = false;										//!< �r���{�[�h��
	bool mDoDrawDebugLine = false;									//!< �f�o�b�O���C����`�悷�邩

	//!
	//! @brief ���[�J���ϊ��s����Z�b�g
	//! @param[in] matrix �Z�b�g���郏�[���h�ϊ��s��
	//!
	void SetLocalMatrix(const XMFLOAT4X4& matrix);
	
public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };		//!< ���P�[�V����
	XMFLOAT3 Scale = { 1.f,1.f,1.f };			//!< �X�P�[��

	CRotator Rotation;							//!< ���[�e�[�^�[

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃g�����X�t�H�[�������L����A�N�^�[
	//!
	CTransform(IActor& partner);

	//!
	//! @brief �R���X�g���N�^
	//! @details ���Ƃ�����]������g�����X�t�H�[�������܂��Ă���ۂɗ��p����
	//! @param[in] partner ���̃g�����X�t�H�[�������L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//!
	CTransform(IActor& partner , CTransform& parentTrans);

	//! @brief �f�X�g���N�^
	~CTransform();

	//! @brief �X�V
	void Update();

	//! @brief GPU�ɍs����Z�b�g���郊�N�G�X�g
	void RequestSetMatrix();

	//!
	//! @brief �g�����X�t�H�[�����A�^�b�`
	//! @details �����̃g�����X�t�H�[�����q�g�����X�t�H�[���Ƃ��ăA�^�b�`�����
	//! @param[in] attachTarget ���g�ɃA�^�b�`����g�����X�t�H�[��
	//!
	void AttachTransform(CTransform& attachTarget);

	//!
	//! @brief �g�����X�t�H�[�����f�^�b�`
	//! @details �����̃g�����X�t�H�[�����f�^�b�`�����
	//! @param[in] detachTarget ���g�Ƀf�^�b�`����g�����X�t�H�[��
	//!
	void DetachTransform(CTransform& detachTarget);

	//! @brief �f�o�b�O���C���@�\�����N�G�X�g
	void RequestDebugLine();

	//!
	//! @brief ���[���h�̉E�����x�N�g���擾
	//! @return XMFLOAT3 ���[���h�̉E�����x�N�g��
	//!
	XMFLOAT3 GetWorldRightVector()const;

	//!
	//! @brief ���[���h�̏�����x�N�g���擾
	//! @return XMFLOAT3 ���[���h�̏�����x�N�g��
	//!
	XMFLOAT3 GetWorldUpwardVector()const;

	//!
	//! @brief ���[���h�̑O�����x�N�g���擾
	//! @return XMFLOAT3 ���[���h�̑O�����x�N�g��
	//!
	XMFLOAT3 GetWorldForwardVector()const;
	
	//!
	//! @brief ���[�J���̉E�����x�N�g���擾
	//! @return XMFLOAT3 ���[�J���̉E�����x�N�g��
	//!
	XMFLOAT3 GetLocalRightVector()const;

	//!
	//! @brief ���[�J���̏�����x�N�g���擾
	//! @return XMFLOAT3 ���[�J���̏�����x�N�g��
	//!
	XMFLOAT3 GetLocalUpwardVector()const;

	//!
	//! @brief ���[�J���̑O�����x�N�g���擾
	//! @return XMFLOAT3 ���[�J���̑O�����x�N�g��
	//!
	XMFLOAT3 GetLocalForwardVector()const;

	//! @brief ���[���h�̃��P�[�V�����擾
	XMFLOAT3 GetWorldLocation()const;

	//! @brief ���[���h�̃X�P�[���擾
	XMFLOAT3 GetWorldScale()const;

	//!
	//! @brief �s��X�V�����s�C�x���g��ǉ�
	//! @param[in] event �ǉ�����C�x���g
	//!
	void AddEventWhenMatrixUpdate(const std::function<void()>& event)
	{
		mEventWhenMatrixUpdate.emplace_back(event);
	};

	const XMFLOAT4X4& GetWorldMatrix()const
	{
		return mWorldMatrix;
	}

	const XMFLOAT4X4& GetLocalMatrix()const
	{
		return mLocalMatrix;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}

	void SetIsBillboard(bool flg)
	{
		mIsBillboard = flg;
	}

	void SetOption(EAttachOption option)
	{
		mAttachOption = option;
	}

};