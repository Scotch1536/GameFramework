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
	};

protected:
	int mPriority = 0;		//�D��x

	EAttribute mAttribute = EAttribute::NONE;

	//�R�s�[�֎~
	CComponent(const CComponent&) = delete;
	CComponent& operator=(const CComponent&) = delete;

public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓A�N�^�[�ɃR���|�[�l���g��ǉ����邱�Ƃ��Ӗ�����
	CComponent(IActor& owner);
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