#pragma once
#include <vector>
#include <memory>

#include "CComponent.h"
#include "CTransform.h"
#include "IRender.h"

class CLevel;
class ILevel;

//�C���^�[�t�F�[�X
class IActor
{
public:
	virtual ~IActor() {};
	virtual void AddComponent(CComponent& component) = 0;
	virtual void RegisterRenderComponent(IRender& component) = 0;
};

//�A�N�^�[�N���X
class CActor :public IActor , public IRender
{
private:
	//�t�����h�w��
	friend CComponent::CComponent(IActor&);

	std::vector<std::unique_ptr<CComponent>> mComponents;		//�R���|�[�l���g
	ILevel& mOwnerInterface;									//�C���^�[�t�F�[�X
	std::vector<IRender*> mRenderAttributeComponents;			//�`��̑��������R���|�[�l���g

	//�R�s�[�֎~
	CActor(const CActor&) = delete;
	CActor& operator=(const CActor&) = delete;

	/*�R���|�[�l���g�ǉ�
	�����d�v���q�N���X�͌ĂԂ��Ƃ͂ł��Ȃ�
	�R���|�[�l���g�̃R���X�g���N�^���ĂԂ��ƂŃA�N�^�[�̎Q�Ƃ���H���Ă��̃��\�b�h���Ă΂��
	*/
	void AddComponent(CComponent& component)override;
	void RegisterRenderComponent(IRender& component)override;
protected:
	CTransform mTransform;										//�g�����X�t�H�[��

public:
	//�����d�v���@�A�N�^�[�̃R���X�g���N�^���ĂԂ��Ƃ̓��x���ɃA�N�^�[��ǉ����邱�Ƃ��Ӗ�����
	CActor(CLevel& owner);

	virtual ~CActor() {};

	/*�X�V
	�����d�v�����̃��\�b�h���I�[�o�[���C�h����ꍇ�͕K���Ō�ɐe�̃��\�b�h���ĂԂ���
	*/
	virtual void Update();

	//�`��
	void Render()override;

	//�j��
	void Destroy();

	//�R���|�[�l���g�̑�������w��̃R���|�[�l���g���Q�b�g
	bool GetComponentFromAttribute(CComponent::EAttribute attribute , CComponent*& inOut)const;
};