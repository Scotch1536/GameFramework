#pragma once
#include <vector>
#include <memory>

#include "../Components/CComponent.h"
#include "../Transform/CTransform.h"
#include "../Interfaces/IRender.h"

class ILevel;
class CTransform;

//�C���^�[�t�F�[�X
class IActor
{
public:
	virtual ~IActor() {};
	virtual void AddComponent(CComponent& component) = 0;
	virtual void RegisterRenderComponent(IRender& component) = 0;
	virtual CTransform& GetTransform() = 0;
};

//�A�N�^�[�N���X
class CActor :public IActor
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//�R���|�[�l���g
	std::vector<IRender*> mRenderAttributeComponents;			//�`��̑��������R���|�[�l���g

	ILevel& mOwnerInterface;		//�C���^�[�t�F�[�X

	//�R�s�[�֎~
	CActor(const CActor&) = delete;
	CActor& operator=(const CActor&) = delete;

	/*�R���|�[�l���g�ǉ�
	�����d�v���q�N���X�͌ĂԂ��Ƃ͂ł��Ȃ�
	�R���|�[�l���g�̃R���X�g���N�^���ĂԂ��ƂŃA�N�^�[�̎Q�Ƃ���H���Ă��̃��\�b�h���Ă΂��
	*/
	void AddComponent(CComponent& component)override;

	//�����_�[�@�\�����R���|�[�l���g��o�^
	void RegisterRenderComponent(IRender& component)override;

	//�g�����X�t�H�[���擾
	CTransform& GetTransform() override
	{
		return Transform;
	}
public:
	CTransform Transform;			//�g�����X�t�H�[��

	//�����d�v���@�A�N�^�[�̃R���X�g���N�^���ĂԂ��Ƃ̓��x���ɃA�N�^�[��ǉ����邱�Ƃ��Ӗ�����
	CActor(ILevel& owner);

	virtual ~CActor();

	/*�X�V
	�����d�v�����̃��\�b�h���I�[�o�[���C�h����ꍇ�͕K���Ō�ɐe�̃��\�b�h���ĂԂ���
	*/
	void Update();

	//���t���[���s�������i�q�N���X�̂��߂̋@�\�j
	virtual void Tick() {};

	//�`��
	void Render();

	//�j��
	void Destroy();

	//�R���|�[�l���g�̑�������w��̃R���|�[�l���g���Q�b�g
	bool GetComponentFromAttribute(CComponent::EAttribute attribute , CComponent*& result)const;

};