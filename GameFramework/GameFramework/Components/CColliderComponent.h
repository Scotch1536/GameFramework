#pragma once
#include <vector>
#include <functional>
#include <unordered_map>

#include "../Transform/CTransform.h"
#include "../Data/CModelMeshData.h"
#include "CComponent.h"

//!
//! @file
//! @brief �R���C�_�[�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

class CTransform;

//! @brief �R���C�h�L���b�V���f�[�^�\����
struct SCollideCacheData
{
	bool IsCollide = false;					//!< �������Ă��邩
	bool IsLastFrameCollide = false;		//!< �Ō�̃t���[�����������Ă��邩
};

//! @brief �R���C�_�[�R���|�[�l���g
class CColliderComponent :public CComponent
{
public:
	//! @brief �R���C�_�[�^�C�v�񋓌^
	enum class EType
	{
		AABB ,
		SPHERE ,
	};

private:
	EType mType;										//!< �R���C�_�[�^�C�v
	std::string mObjectType = "NONE";					//!< �I�u�W�F�N�g�^�C�v

	std::vector<CColliderComponent*> mColliders;		//!< �����ȊO�̃R���C�_�[

	std::unordered_map<CColliderComponent* , SCollideCacheData> mCollidedCache;			//!< �Փˏ��̃L���b�V���f�[�^

	std::function<void(CActor&)> mEventAtBeginningCollided;			//!< �ՓˊJ�n���C�x���g
	std::function<void(CActor&)> mEventAtEndCollided;				//!< �ՓˏI�����C�x���g

	bool mShouldCompared = true;		//!< ��r���ׂ���
	bool mShouldUpdate = true;			//!< �X�V���ׂ���

	//! @brief �X�V
	void Update() override;

	//!
	//! @brief �L���b�V���f�[�^�̍X�V
	//! @param[in] target �Ώۂ̃R���C�_�[�R���|�[�l���g
	//! @param[in] isCollided �������Ă��邩
	//!
	void UpdateCollidedCache(CColliderComponent* targetCollider , bool isCollided);

protected:
	//!
	//! @brief ���b�V���̒��_�̍ő�ŏ��l���Z�o����
	//! @param[in] meshes �Ώۂ̃��b�V��
	//! @param[out] min �ŏ��l�̌���
	//! @param[out] max �ő�l�̌���
	//!
	static void CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& min , XMFLOAT3& max);

public:
	CTransform Transform;		//!< �g�����X�t�H�[��

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] type �R���C�_�[�̃^�C�v
	//! @param[in] priority �D��x
	//!
	CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority = 40);

	//! @brief �f�X�g���N�^
	virtual ~CColliderComponent();

	//! @brief �R���C�_�[�����[���h���W�n�ɕϊ�
	virtual void ConvertWorldCollider() = 0;

	const EType& GetType()const
	{
		return mType;
	}

	const std::string& GetObjectType()const
	{
		return mObjectType;
	}

	void SetObjectType(std::string objType)
	{
		mObjectType = objType;
	}

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

};
