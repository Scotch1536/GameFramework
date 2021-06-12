#pragma once
#include <vector>
#include <memory>
#include <DirectXMath.h>

#include "CRotator.h"

class CChildTransform;
class IActor;

//�g�����X�t�H�[���N���X
class CTransform
{
private:
	XMFLOAT4X4 mWorldMatrixSelf;			//���g�̃��[���h�s��
	XMFLOAT4X4 mWorldMatrixResult;			//�ŏI�I�Ȍ��ʂ̃��[���h�s��

	CTransform* mParentTransform = nullptr;				//�e�g�����X�t�H�[��
	std::vector<CTransform*> mChildTransform;			//�q�g�����X�t�H�[��

	XMFLOAT3 mLastFrameLocation = { 0.f,0.f,0.f };		//�O�t���[���̃��P�[�V����
	XMFLOAT3 mLastFrameScale = { 0.f,0.f,0.f };			//�O�t���[���̃X�P�[��

	bool mShouldUpdateMatrix = true;		//�s����X�V���ׂ���
	bool mIsChild = false;					//�������q�g�����X�t�H�[����

public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };			//���P�[�V����
	XMFLOAT3 Scale = { 1.f,1.f,1.f };				//�X�P�[��

	CRotator Rotation;								//���[�e�[�V����

	CTransform();
	CTransform(IActor& partner);
	~CTransform();

	//�X�V
	void Update();

	//�s���Directx�ɃZ�b�g���Ă��炤���N�G�X�g
	void RequestSetMatrix();

	//�����̃g�����X�t�H�[�����A�^�b�`�i�e�q�t���j����
	void AttachTransform(CTransform& attachTarget);

	//�����̃g�����X�t�H�[�����f�^�b�`�i�e�q�t�������j����
	void DetachTransform(CTransform& detachTarget);

	const XMFLOAT4X4& GetWorldMatrixResult(const CTransform& partner)const
	{
		return mWorldMatrixResult;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}
};