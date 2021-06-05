#pragma once

class IActor;
class CActor;

class CComponent
{
private:
	int mPriority;					//�D��x
	IActor& mOwnerInterface;		//�C���^�[�t�F�[�X
public:
	//�����d�v���@�R���X�g���N�^���ĂԂƂ������Ƃ̓A�N�^�[�ɃR���|�[�l���g��ǉ����邱�Ƃ��Ӗ�����
	CComponent(CActor& owner);

	//�X�V
	virtual void Update() = 0;

	const int& GetPriority()const
	{
		return mPriority;
	}
};