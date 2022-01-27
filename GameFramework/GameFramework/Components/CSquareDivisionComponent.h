//!
//! @file
//! @brief �l�p�����R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <DirectXMath.h>
#include <vector>
#include <array>
#include <unordered_map>
#include <string>

#include "CComponent.h"

using namespace DirectX;

//! @brief �l�p�����R���|�[�l���g�N���X
class  CSquareDivisionComponent :public CComponent
{
protected:
	std::unordered_map<std::string , std::pair<int , int>> mAlias;		//!< �ʖ�
	std::vector<std::array<XMFLOAT2 , 4>> mUVData;						//!< UV�f�[�^

	//!
	//! @brief �ʖ��̒ǉ�
	//! @details �͈͎w��ŕʖ���ǉ�����ۂɗ��p����
	//! �q�N���X��2D�A�j���[�V�����Ŏg�p���郁�\�b�h
	//! @param[in] start �J�n��UV�f�[�^�z��̃C���f�b�N�X
	//! @param[in] finish �I����UV�f�[�^�z��̃C���f�b�N�X
	//! @param[in] alias �ǉ��������ʖ�
	//!
	void AddAlias(int start , int finish , std::string alias)
	{
		mAlias[alias].first = start;
		mAlias[alias].second = finish;
	};

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] divWidth �����̕�����
	//! @param[in] divHeight �c���̕�����
	//!
	CSquareDivisionComponent(CActor& owner , int divWidth , int divHeight);

	//!
	//! @brief UV�f�[�^�̎擾
	//! @details UV�f�[�^�z��̃C���f�b�N�X����UV�f�[�^���擾����ۂɗ��p����
	//! @param[in] index �擾������UV�f�[�^�z��̃C���f�b�N�X
	//! @param[out] result ���ʂ�UV�f�[�^
	//!
	void GetUV(int index , std::array<XMFLOAT2 , 4>& result);

	//!
	//! @brief UV�f�[�^�̎擾
	//! @details �ʖ�����UV�f�[�^���擾����ۂɗ��p����
	//! @param[in] alias �擾������UV�f�[�^�̕ʖ�
	//! @param[out] result ���ʂ�UV�f�[�^
	//!
	void GetUV(std::string alias , std::array<XMFLOAT2 , 4>& result);

	//!
	//! @brief �ʖ��̒ǉ�
	//! @details 1�̃C���f�b�N�X�ɕʖ���ǉ�����ۂɗ��p����
	//! @param[in] index �J�n��UV�f�[�^�z��̃C���f�b�N�X
	//! @param[in] alias �ǉ��������ʖ�
	//!
	void AddAlias(int index , std::string alias)
	{
		mAlias[alias].first = index;
		mAlias[alias].second = index;
	};

	//!
	//! @brief �ʖ��̍폜
	//! @param[in] alias �폜�������ʖ�
	//!
	void DeleteAlias(std::string alias)
	{
		//�����̕ʖ������݂���Ȃ�폜����
		if(mAlias.count(alias) != 0)mAlias.erase(alias);
	}

};