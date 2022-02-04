//!
//! @file
//! @brief ���̓}�l�[�W���[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <dinput.h>

#include "../Object/CObject.h"

class CObject;

//! @brief �{�^���^�C�v�񋓌^
enum class EButtonType
{
	NONE ,				//!< NONE
	KEYBOARD ,			//!< �L�[�{�[�h
	MOUSE ,				//!< �}�E�X
	X_CONTROLLER ,		//!< X�R���g���[���[
};

//! @brief �{�^���I�v�V�����񋓌^
enum class EButtonOption
{
	NONE ,				//!< NONE
	PRESS ,				//!< �v���X
	TRIGGER ,			//!< �g���K�[
	RELEASE ,			//!< �����[�X
};

//! @brief �}�E�X�{�^���񋓌^
enum class EMouseButtonType
{
	NONE ,				//!< NONE
	L_BUTTON ,			//!< ���{�^��
	R_BUTTON ,			//!< �E�{�^��
	C_BUTTON ,			//!< �����{�^��
};

//! @brief �{�^�����\����
struct SButtonInfo
{
	EButtonType ButtonType = EButtonType::NONE;			//!< �{�^���^�C�v
	int ButtonNum = 0;									//!< �{�^���ԍ��i����ꍇ�j

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] type �{�^���^�C�v
	//! @param[in] buttonNum �{�^���ԍ�
	//!
	SButtonInfo(EButtonType type , int buttonNum = 0)
	{
		ButtonType = type;
		ButtonNum = buttonNum;
	}

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] mouseButtonNum �{�^���ԍ�
	//!
	SButtonInfo(EButtonType type , EMouseButtonType mouseButtonNum)
	{
		ButtonType = type;
		ButtonNum = static_cast<int>(mouseButtonNum);
	}
};

//! @brief �C���v�b�g��`�\����
struct SInputDefinition
{
	CObject* InstancePointer = nullptr;						//!< �C���X�^���X�̃|�C���^

	EButtonOption ButtonOption = EButtonOption::NONE;		//!< �{�^���̃I�v�V����

	std::vector<SButtonInfo> ButtonInfoList;				//!< �{�^���̏�񃊃X�g

	std::function<void()> EventInfo;						//!< �s�������C�x���g���
};

//! @brief ���̓}�l�[�W���[�N���X
class CInputManager
{
private:
	std::unordered_map<std::string , SInputDefinition> mInputEventList;		//!< ���̓C�x���g���X�g

	std::vector<std::function<void()>> mDeleteEvents;

	//!
	//! @brief �R���X�g���N�^
	//! @details ���O�ɓ��̓C�x���g���X�g������Ă��������ꍇ�̓R���X�g���N�^���ɏ���
	//!
	CInputManager();

	//�R�s�[�����[�u�֎~
	CInputManager(const CInputManager&) = delete;
	CInputManager& operator=(const CInputManager&) = delete;
	CInputManager(CInputManager&&) = delete;
	CInputManager& operator=(CInputManager&&) = delete;

public:
	//!
	//! @brief �C���X�^���X�擾
	//! @return CInputManager& �C���X�^���X
	//!
	static CInputManager& GetInstance();

	//!
	//! @brief �C�x���g�̃o�C���h�����N�G�X�g
	//! @details �쐬�ς݂̓��̓C�x���g���X�g�ɃC�x���g���o�C���h�i�o�^�j�������ۂɗ��p����
	//! @param[in] eventName �C�x���g���i���̓C�x���g���X�g�̃L�[�j
	//! @param[in] instancePtr �C���X�^���X�|�C���^
	//! @param[in] event �o�C���h����C�x���g
	//!
	void RequestBindEvent(std::string eventName , CObject& instancePtr , std::function<void()>& event);

	//!
	//! @brief �C�x���g�̒ǉ�
	//! @details �쐬�ς݂̓��̓C�x���g���X�g������Ώ㏑�������
	//! @param[in] eventName �C�x���g���i���̓C�x���g���X�g�̃L�[�j
	//! @param[in] buttonOption �{�^���I�v�V����
	//! @param[in] instancePtr �C���X�^���X�|�C���^
	//! @param[in] buttonInfo �R�t����{�^��
	//! @param[in] event �o�C���h����C�x���g
	//!
	void AddEvent(const std::string& eventName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& event);

	//!
	//! @brief �C�x���g�̒ǉ�
	//! @details �쐬�ς݂̓��̓C�x���g���X�g������Ώ㏑�������
	//! @param[in] eventName �C�x���g���i���̓C�x���g���X�g�̃L�[�j
	//! @param[in] buttonOption �{�^���I�v�V����
	//! @param[in] instancePtr �C���X�^���X�|�C���^
	//! @param[in] buttonInfoList �R�t����{�^���̃��X�g
	//! @param[in] event �o�C���h����C�x���g
	//!
	void AddEvent(const std::string& eventName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& event);

	//!
	//! @brief �C�x���g�̍폜
	//! @param[in] eventName �C�x���g���i���̓C�x���g���X�g�̃L�[�j
	//!
	void DeleteEvent(const std::string& eventName);

	//!
	//! @brief �o�C���h�̉��
	//! @param[in] target �o�C���h������������I�u�W�F�N�g
	//!
	void ReleaseBind(CObject& target);

	//! @brief ���͂���Ă��邩�̃`�F�b�N
	void CheckInput();

	//! @brief �}�E�X��X���W�擾
	int GetMousePosX();

	//! @brief �}�E�X��Y���W�擾
	int GetMousePosY();
};