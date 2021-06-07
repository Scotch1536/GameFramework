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

	//enum class ComponentType
	//{
	//	NONE = 0b00 ,
	//	SMESH = 0b01 ,
	//};

protected:
	int mPriority = 0;		//�D��x

	EAttribute mAttribute = EAttribute::NONE;
	//ComponentType mType = ComponentType::NONE;

	//�R�s�[�֎~
	CComponent(const CComponent&) = delete;
	CComponent& operator=(const CComponent&) = delete;

public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓A�N�^�[�ɃR���|�[�l���g��ǉ����邱�Ƃ��Ӗ�����
	CComponent(IActor& owner);
	virtual ~CComponent() = default;

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

	//const int& GetType()const
	//{
	//	return static_cast<int>(mType);
	//}
};