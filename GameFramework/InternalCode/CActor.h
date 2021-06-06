#pragma once
#include <vector>
#include <memory>

#include "CComponent.h"
#include "CTransform.h"

class ILevel;
class CLevel;

//�C���^�[�t�F�[�X
class IActor
{
public:
	virtual ~IActor() {};
	virtual void AddComponent(CComponent& component) = 0;
};

class CActor :public IActor
{
private:
	//�R���|�[�l���g�ǉ��@�����d�v���q�N���X�͌ĂԂ��Ƃ͂ł��Ȃ�
	void AddComponent(CComponent& component)override;
protected:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//�R���|�[�l���g
	CTransform mTransform;										//�g�����X�t�H�[��
	ILevel& mOwnerInterface;									//�C���^�[�t�F�[�X
public:
	CActor(CLevel& owner);
	virtual ~CActor() = default;

	//�X�V
	void Update();

	//�j��
	void Destroy();
};