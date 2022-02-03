//!
//! @file
//! @brief ���C�g�}�l�[�W���[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <vector>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

constexpr int LIGHT_NUM = 10;		//< �e��ɂ����郉�C�g�̐�

class CLightComponent;

//! @brief ���C�g�R���|�[�l���g�p���C�g�}�l�[�W���[�C���^�[�t�F�[�X�N���X
class ILightManagerToLightComponent
{
public:
	//! @brief �f�X�g���N�^
	virtual ~ILightManagerToLightComponent() {};

	//!
	//! @brief ���C�g�ǉ�
	//! @param[in] lighr �ǉ����郉�C�g
	//!
	virtual void AddLight(CLightComponent& light) = 0;

	//!
	//! @brief ���C�g���
	//! @param[in] lighr ������郉�C�g
	//!
	virtual void ReleaseLight(CLightComponent& light) = 0;
};

//! @brief ���C�g�}�l�[�W���[�N���X
class CLightManager :public ILightManagerToLightComponent
{
private:
	//! @brief �|�C���g���C�g�\����
	ALIGN16 struct SPointLight
	{
		XMFLOAT3 LightPos;			//!< ���C�g�ʒu
		float Pad1;					//!< �p�f�B���O
		XMFLOAT4 Attenuation;		//!< ������
	};

	//! @brief �X�|�b�g���C�g�\����
	ALIGN16 struct SSpotLight :public SPointLight
	{
		XMFLOAT3 Direction;			//!< ���C�g�̌���
		float Pad2;					//!< �p�f�B���O
		float Angle;				//!< �p�x�i���C�g�̍L����j
	};

	//! @brief ���C�g�萔�o�b�t�@�\����
	ALIGN16 struct SConstantBufferLight
	{
		XMFLOAT3 EyePos;							//!< �ڂ̈ʒu
		float Pad1;									//!< �p�f�B���O
		XMFLOAT3 DirectionLightData;				//!< ���s�����f�[�^
		float Pad2;									//!< �p�f�B���O
		XMFLOAT3 AmbientLightData;					//!< �����f�[�^
		float Pad3;									//!< �p�f�B���O
		SPointLight PointLights[LIGHT_NUM];			//!< �|�C���g���C�g
		SSpotLight SpotLights[LIGHT_NUM];			//!< �X�|�b�g���C�g
	};

	std::vector<CLightComponent*> mLights;				//!< ���C�g�f�[�^

	ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;		//!< �萔�o�b�t�@
	SConstantBufferLight mConstantBufferLightData;		//!< ���C�g�萔�o�b�t�@�f�[�^

	XMFLOAT3 mEyePos;									//!< �ڂ̈ʒu
	XMFLOAT3 mDirectionLightData;						//!< ���s�����f�[�^
	XMFLOAT3 mAmbientLightData;							//!< �����f�[�^

	bool mShouldUpdate = false;							//!< �X�V���ׂ���

	//! @brief �R���X�g���N�^
	CLightManager();

	//�R�s�[�����[�u�֎~
	CLightManager(const CLightManager&) = delete;
	CLightManager& operator=(const CLightManager&) = delete;
	CLightManager(CLightManager&&) = delete;
	CLightManager& operator=(CLightManager&&) = delete;

	//!
	//! @brief ���C�g�ǉ�
	//! @param[in] lighr �ǉ����郉�C�g
	//!
	void AddLight(CLightComponent& light);

	//!
	//! @brief ���C�g���
	//! @param[in] lighr ������郉�C�g
	//!
	void ReleaseLight(CLightComponent& light);

public:
	//!
	//! @brief �C���X�^���X�擾
	//! @return CLightManager& �C���X�^���X
	//!
	static CLightManager& GetInstance();

	//! @brief �X�V
	void Update();

	//!
	//! @brief �ʒm
	//! @details ���C�g�̍쐬��ύX���s��ꂽ�Ƃ��Ƀ}�l�[�W���[�ɒʒm���čX�V�𑣂�
	//!
	void Notice()
	{
		mShouldUpdate = true;
	}

	//!
	//! @brief ���s�����̃Z�b�g
	//! @param[in] direction ���s�����̌���
	//!
	void SetDirectionLight(XMFLOAT3 direction)
	{
		mDirectionLightData = direction;
		Notice();
	}

	//!
	//! @brief �����̃Z�b�g
	//! @param[in] ambient ���̐F���
	//!
	void SetAmbientLight(XMFLOAT3 ambient)
	{
		mAmbientLightData = ambient;
		Notice();
	}

};