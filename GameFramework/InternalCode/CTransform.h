#pragma once
#include <vector>
#include <memory>
#include <DirectXMath.h>

#include "CRotator.h"

class CChildTransform;
class CActor;

class ITransform
{
public:
	virtual ~ITransform() {};
	virtual void AddChildTransform(CChildTransform& child) = 0;
};

class CTransform :public ITransform
{
private:
	XMFLOAT4X4 mWorldMatrix;		//���[���h�s��

	std::vector<CTransform*> mChildTransform;			//�]������̎q�g�����X�t�H�[��

	bool mShouldUpdateMatrix = true;		//�s����X�V���ׂ���

	//�q�g�����X�t�H�[���̒ǉ�
	void AddChildTransform(CChildTransform& child)override;
protected:
	XMFLOAT3 mLocation;			//���P�[�V����
	XMFLOAT3 mScale;			//�X�P�[��
	CRotator mRotation;			//���[�e�[�V����

	CTransform();
public:
	CTransform(CActor& partner);
	virtual ~CTransform() = default;

	//�X�V
	virtual void Update();

	//�s���Directx�ɃZ�b�g���Ă��炤���N�G�X�g
	void RequestSetMatrix();

	//���ʐ��`��Ԃ����N�G�X�g
	void RequestSLerp(XMFLOAT3 angle , float lerpTime)
	{
		mRotation.RequestSLerp(angle , lerpTime);
	}

	void SetLocation(XMFLOAT3 location)
	{
		mLocation = location;

		if(!mShouldUpdateMatrix)mShouldUpdateMatrix = true;
	}

	void SetScale(XMFLOAT3 scale)
	{
		mScale = scale;;

		if(!mShouldUpdateMatrix)mShouldUpdateMatrix = true;
	}

	void SetRotation(XMFLOAT3 rotation)
	{
		mRotation.SetAngle(rotation);

		if(!mShouldUpdateMatrix)mShouldUpdateMatrix = true;
	}

	const XMFLOAT3& GetLocation()const
	{
		return mLocation;
	}

	const XMFLOAT3& GetScale()const
	{
		return mScale;
	}

	const XMFLOAT3& GetRotation()const
	{
		return mRotation.GetAngle();
	}
};