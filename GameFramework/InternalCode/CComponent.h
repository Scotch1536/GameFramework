#pragma once

class IActor;

//�R���|�[�l���g�N���X
class CComponent
{
public:
	enum class EAttribute
	{
		NONE ,
		CAMERA ,
		RENDER ,
	};

private:
	int mPriority = 0;		//�D��x 0�`100��z��

protected:
	EAttribute mAttribute = EAttribute::NONE;		//����

	IActor& mOwnerInterface;		//�C���^�[�t�F�[�X

	//�R�s�[�֎~
	CComponent(const CComponent&) = delete;
	CComponent& operator=(const CComponent&) = delete;

public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓A�N�^�[�ɃR���|�[�l���g��ǉ����邱�Ƃ��Ӗ�����
	CComponent(IActor& owner , int priority);
	virtual ~CComponent() = 0;

	//�X�V
	virtual void Update() {};

	const int& GetPriority()const
	{
		return mPriority;
	}

	const EAttribute& GetAttribute()const
	{
		return mAttribute;
	}
};