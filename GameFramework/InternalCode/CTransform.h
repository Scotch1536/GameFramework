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
	std::vector<CTransform*> mChildTransform;			//�]������̎q�g�����X�t�H�[��

	XMFLOAT3 mCompareLocation = { 0.f,0.f,0.f };		//��r���邽�߂̃��P�[�V����
	XMFLOAT3 mCompareScale = { 0.f,0.f,0.f };			//��r���邽�߂̃X�P�[��

	//�q�g�����X�t�H�[���̒ǉ�
	void AddChildTransform(CChildTransform& child)override;
protected:
	XMFLOAT4X4 mWorldMatrix;		//���[���h�s��

	bool mShouldUpdateMatrix = true;		//�s����X�V���ׂ���

	CTransform();

public:
	XMFLOAT3 location = { 0.f,0.f,0.f };			//���P�[�V����
	XMFLOAT3 scale = { 1.f,1.f,1.f };				//�X�P�[��

	CRotator rotation;								//���[�e�[�V����

	CTransform(CActor& partner);
	virtual ~CTransform() = default;

	//�X�V
	virtual void Update();

	//�s���Directx�ɃZ�b�g���Ă��炤���N�G�X�g
	void RequestSetMatrix();

	////���ʐ��`��Ԃ����N�G�X�g
	//void RequestSLerp(XMFLOAT3 angle , float lerpTime)
	//{
	//	mRotation.RequestSLerp(angle , lerpTime);
	//}

};