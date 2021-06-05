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
protected:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//�R���|�[�l���g
	CTransform mTransform;										//�g�����X�t�H�[��
	ILevel& mOwnerInterface;									//�C���^�[�t�F�[�X

	//�R���|�[�l���g�ǉ�
	void AddComponent(CComponent& component)override;
public:
	CActor(CLevel& owner);

	//�X�V
	void Update();

	//�j��
	void Destroy();
};