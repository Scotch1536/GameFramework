#pragma once

class IActor;

//�R���|�[�l���g�N���X
class CComponent
{
protected:
	int mPriority = 0;		//�D��x
public:
	//�����d�v���@�R���X�g���N�^���ĂԂƂ������Ƃ̓A�N�^�[�ɃR���|�[�l���g��ǉ����邱�Ƃ��Ӗ�����
	CComponent(IActor& owner);
	virtual ~CComponent() = default;

	//�X�V
	virtual void Update() = 0;

	const int& GetPriority()const
	{
		return mPriority;
	}
};