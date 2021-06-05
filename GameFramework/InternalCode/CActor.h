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
	std::vector<std::unique_ptr<CComponent>> mComponents;		//�R���|�[�l���g
	CTransform mTransform;										//�g�����X�t�H�[��
	ILevel& mOwnerInterface;									//�C���^�[�t�F�[�X
public:
	CActor(CLevel& owner);

	//�R���|�[�l���g�ǉ�
	void AddComponent(CComponent& component)override;

	//�X�V
	void Update();

	//�j��
	void Destroy();
};