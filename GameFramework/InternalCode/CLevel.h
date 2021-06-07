#pragma once
#include <vector>
#include <memory>

#include "CActor.h"
#include "IRender.h"

class IGame;
class CGame;
class CCameraComponent;

class ILevel
{
public:
	virtual ~ILevel() {};
	virtual void DestroyActor(CActor& target) = 0;
};

class CLevel :public ILevel , public IRender
{
private:
	friend CActor::CActor(CLevel&);

	CCameraComponent* mRenderingCamera = nullptr;		//�����_�[��S������J����
	std::vector<std::unique_ptr<CActor>> mActors;		//�A�N�^�[

protected:
	IGame& mOwnerInterface;								//�Q�[���C���^�[�t�F�[�X

private:
	//�R�s�[�֎~
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;

	/*�A�N�^�[�ǉ�
	�����d�v���q�N���X�͌ĂԂ��Ƃ͂ł��Ȃ�
	�A�N�^�[�̃R���X�g���N�^���ĂԂ��ƂŃA�N�^�[�̎Q�Ƃ���H���Ă��̃��\�b�h���Ă΂��
	*/
	void AddActor(CActor& actor);
protected:
	//�J�����̃Z�b�g�����N�G�X�g
	void RequestSetCamera(CCameraComponent& camera);

public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓��x���̑J�ڂ��Ӗ�����
	CLevel(CGame& owner);

	virtual ~CLevel() = default;

	//������
	virtual void Init() = 0;

	//�X�V
	void Update();

	//�`��
	void Render()override;

	//�A�N�^�[�̔j��
	void DestroyActor(CActor& target)override;
};