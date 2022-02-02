//!
//!	@file
//!	@brief �I�u�W�F�N�g�V�X�e���̃w�b�_�[�t�@�C��
//!

#pragma once
#include <string>

//! @brief �I�u�W�F�N�g�N���X
class CObject
{
private:
	std::string mID;		//!< �I�u�W�F�N�gID

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] id �I�u�W�F�N�gID
	//!
	CObject(std::string id):mID(id) {};

	//! @brief �f�X�g���N�^
	virtual ~CObject() = default;

	//! @brief �X�V
	virtual void Update() = 0;

	//! @brief �`��
	virtual void Render() = 0;

	const std::string& GetID()
	{
		return mID;
	}

};