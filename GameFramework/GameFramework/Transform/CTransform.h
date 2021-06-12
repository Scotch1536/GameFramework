#pragma once
#include <vector>
#include <memory>
#include <DirectXMath.h>

#include "CRotator.h"

class CChildTransform;
class IActor;

class ITransform
{
public:
	virtual ~ITransform() {};
	virtual void AttachTransform(CTransform& attachTarget) = 0;
	virtual void DetachTransform(CTransform& detachTarget) = 0;
};

//�g�����X�t�H�[���N���X
class CTransform :public ITransform
{
private:
	XMFLOAT4X4 mWorldMatrixSelf;			//���g�̃��[���h�s��
	XMFLOAT4X4 mWorldMatrixResult;			//�ŏI�I�Ȍ��ʂ̃��[���h�s��

	CTransform* mParentTransform = nullptr;				//�e�g�����X�t�H�[��
	std::vector<CTransform*> mChildTransform;			//�q�g�����X�t�H�[��

	XMFLOAT3 mCompareLocation = { 0.f,0.f,0.f };		//��r���邽�߂̃��P�[�V����
	XMFLOAT3 mCompareScale = { 0.f,0.f,0.f };			//��r���邽�߂̃X�P�[��

	bool mShouldUpdateMatrix = true;		//�s����X�V���ׂ���
	bool mIsChild = false;					//�������q�g�����X�t�H�[����

	//�����̃g�����X�t�H�[�����A�^�b�`�i�e�q�t���j����
	void AttachTransform(CTransform& attachTarget)override;

	//�����̃g�����X�t�H�[�����f�^�b�`�i�e�q�t�������j����
	void DetachTransform(CTransform& detachTarget)override;

public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };			//���P�[�V����
	XMFLOAT3 Scale = { 1.f,1.f,1.f };				//�X�P�[��

	CRotator Rotation;								//���[�e�[�V����

	CTransform();
	CTransform(IActor& partner);
	~CTransform();

	//�X�V
	virtual void Update();

	//�s���Directx�ɃZ�b�g���Ă��炤���N�G�X�g
	virtual void RequestSetMatrix();

	const XMFLOAT4X4& GetWorldMatrixSelf(const CTransform& partner)const
	{
		return mWorldMatrixSelf;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}
};