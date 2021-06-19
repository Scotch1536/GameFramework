#pragma once
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

#include "CComponent.h"

class CLightComponent :public CComponent
{
private:
	ALIGN16 struct ConstantBufferLight
	{
		XMFLOAT4 LightDirection;
		XMFLOAT4 EyePos;
		XMFLOAT4 Ambient;
	};

	enum class LightType
	{
		DIRECTIONAL ,
		POINT ,
		SPOT
	};

	LightType mLightType = LightType::DIRECTIONAL;			//���C�g�^�C�v

	XMFLOAT3 mEyePos;			//���Ă���ʒu
	XMFLOAT4 mLightPos;			//w=0�̎��͕��� w=1�̎��͈ʒu
	XMFLOAT4 mAmbient;			//�A���r�G���g

	ComPtr<ID3D11Buffer> mConstantBufferLight = nullptr;		//�萔�o�b�t�@

	//������
	bool Init()
	{
		//�R���X�^���g�o�b�t�@�쐬
		bool sts = CreateConstantBuffer(CDirectXGraphics::GetInstance()->GetDXDevice() , sizeof(ConstantBufferLight) , &mConstantBufferLight);
		if(!sts)
		{
			MessageBox(NULL , "CreateBuffer(constant buffer Light) error" , "Error" , MB_OK);
			return false;
		}
		return true;
	}
public:
	CLightComponent(CActor& owner , int priority = 40):CComponent(owner , priority)
	{
		Init();
	}

	//�X�V
	void Update()override
	{
		ConstantBufferLight	cb;

		cb.EyePos.w = 1.0;
		cb.EyePos.x = mEyePos.x;
		cb.EyePos.y = mEyePos.y;
		cb.EyePos.z = mEyePos.z;

		cb.LightDirection.x = mLightPos.x;
		cb.LightDirection.y = mLightPos.y;
		cb.LightDirection.z = mLightPos.z;
		cb.LightDirection.w = mLightPos.w;

		cb.Ambient = mAmbient;

		CDirectXGraphics::GetInstance()->GetImmediateContext()->UpdateSubresource(mConstantBufferLight.Get() , 0 , nullptr , &cb , 0 , 0);

		// �R���X�^���g�o�b�t�@4����3���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
		CDirectXGraphics::GetInstance()->GetImmediateContext()->VSSetConstantBuffers(4 , 1 , mConstantBufferLight.GetAddressOf());
		// �R���X�^���g�o�b�t�@4����3���W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
		CDirectXGraphics::GetInstance()->GetImmediateContext()->PSSetConstantBuffers(4 , 1 , mConstantBufferLight.GetAddressOf());
	}

	void SetEyePos(XMFLOAT3 eyepos)
	{
		mEyePos = eyepos;
	}

	void SetLightPos(XMFLOAT4 lightpos)
	{
		mLightPos = lightpos;
	}

	void SetAmbient(XMFLOAT4 amb)
	{
		mAmbient = amb;
	}
};