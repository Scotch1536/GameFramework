//!
//!	@file
//!	@brief �R���W�������C�u�����̃w�b�_�[�t�@�C��
//!

#pragma once
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

//! @brief �R���W�������C�u�����N���X
static class LCCollision
{
public:
	//!
	//! @brief �����蔻��
	//! @details AABB��AABB�̓����蔻��̍ۂɗ��p����
	//! @param[in] min1 1�ڂ�AABB�̍ŏ��l
	//! @param[in] max1 1�ڂ�AABB�̍ő�l
	//! @param[in] min2 1�ڂ�AABB�̍ŏ��l
	//! @param[in] max2 1�ڂ�AABB�̍ő�l
	//! @return bool �������Ă��邩
	//!
	static bool IsCollide(const XMFLOAT3& min1, const XMFLOAT3& max1, const XMFLOAT3& min2, const XMFLOAT3& max2);

	//!
	//! @brief �����蔻��
	//! @details AABB�Ɠ_�̓����蔻��̍ۂɗ��p����
	//! @param[in] min AABB�̍ŏ��l
	//! @param[in] max AABB�̍ő�l
	//! @param[in] point �_�̃��P�[�V����
	//! @return bool �������Ă��邩
	//!
	static bool IsCollide(const XMFLOAT3& min, const XMFLOAT3& max, const XMFLOAT3& point);

	//!
	//! @brief �����蔻��
	//! @details �X�t�B�A�ƃX�t�B�A�̓����蔻��̍ۂɗ��p����
	//! @param[in] center1 1�ڂ̃X�t�B�A�̒��S���W
	//! @param[in] radius1 1�ڂ̃X�t�B�A�̔��a
	//! @param[in] center2 2�ڂ̃X�t�B�A�̒��S���W
	//! @param[in] radius2 2�ڂ̃X�t�B�A�̔��a
	//! @return bool �������Ă��邩
	//!
	static bool IsCollide(const XMFLOAT3& center1,const float& radius1, const XMFLOAT3& center2, const float& radius2);

	//!
	//! @brief �����蔻��
	//! @details AABB�ƃX�t�B�A�̓����蔻��̍ۂɗ��p����
	//! @param[in] min AABB�̍ŏ��l
	//! @param[in] max AABB�̍ő�l
	//! @param[in] center �X�t�B�A�̒��S���W
	//! @param[in] radius �X�t�B�A�̔��a
	//! @return bool �������Ă��邩
	//!
	static bool IsCollide(const XMFLOAT3& min, const XMFLOAT3& max, const XMFLOAT3& center, const float& radius);
};
