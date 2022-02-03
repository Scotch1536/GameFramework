//!
//! @file
//! @brief ���C�g�}�l�[�W���[�̃\�[�X�t�@�C��
//!

#include "../Components/CPointLightComponent.h"
#include "../Components/CSpotLightComponent.h"
#include "../Components/CLightComponent.h"
#include "../Library/LCMath.h"

#include "CGameManager.h"

#include "CLightManager.h"


CLightManager::CLightManager()
{
	//�R���X�^���g�o�b�t�@�쐬
	bool sts = CreateConstantBuffer(CDirectXGraphics::GetInstance()->GetDXDevice() , sizeof(SConstantBufferLight) , mConstantBuffer.GetAddressOf());
	if(!sts)
	{
		MessageBox(NULL , "CreateConstantBuffer Error" , "Error" , MB_OK);
	}
}

CLightManager& CLightManager::GetInstance()
{
	static CLightManager instance;

	return instance;
}

void CLightManager::AddLight(CLightComponent& light)
{
	mLights.emplace_back(&light);

	Notice();
}

void CLightManager::ReleaseLight(CLightComponent& light)
{
	for(auto itr = mLights.begin(); itr != mLights.end(); itr++)
	{
		if((*itr) == &light)
		{
			mLights.erase(itr);
			mLights.shrink_to_fit();
			break;
		}
	}

	Notice();
}


void CLightManager::Update()
{
	XMFLOAT3 cameraLocation = CGameManager::GetInstance().GetCameraLocation();

	//��v���Ȃ����
	if(!LCMath::CompareFloat3(mEyePos , cameraLocation))
	{
		mShouldUpdate = true;
		mEyePos = cameraLocation;
	}

	if(mShouldUpdate)
	{
		int countPL = 0;
		int countSL = 0;

		mShouldUpdate = false;
		mConstantBufferLightData.EyePos = mEyePos;
		mConstantBufferLightData.DirectionLightData = mDirectionLightData;
		mConstantBufferLightData.AmbientLightData = mAmbientLightData;

		for(auto& light : mLights)
		{
			if(light->GetType() == CLightComponent::EType::POINT)
			{
				if(countPL < LIGHT_NUM)
				{
					CPointLightComponent& buf = dynamic_cast<CPointLightComponent&>(*light);
					mConstantBufferLightData.PointLights[countPL].LightPos = buf.Transform.GetWorldLocation();
					mConstantBufferLightData.PointLights[countPL].Attenuation = buf.GetAttenuation();
					countPL++;
				}
				else
				{
#ifdef _DEBUG
					MessageBox(NULL , "���C�g�}�l�[�W���[�Ɋi�[�\�ȃ|�C���g���C�g�𒴂��Ă��܂��B" , "Error" , MB_OK);
#endif
				}
			}
			else if(light->GetType() == CLightComponent::EType::SPOT)
			{
				if(countSL < LIGHT_NUM)
				{
					CSpotLightComponent& buf = dynamic_cast<CSpotLightComponent&>(*light);
					mConstantBufferLightData.SpotLights[countSL].LightPos = buf.Transform.GetWorldLocation();
					mConstantBufferLightData.SpotLights[countSL].Attenuation = buf.GetAttenuation();
					mConstantBufferLightData.SpotLights[countSL].Direction = buf.GetDirection();
					mConstantBufferLightData.SpotLights[countSL].Angle = buf.GetAngle();
					countSL++;
				}
				else
				{
#ifdef _DEBUG
					MessageBox(NULL , "���C�g�}�l�[�W���[�Ɋi�[�\�ȃX�|�b�g���C�g�𒴂��Ă��܂��B" , "Error" , MB_OK);
#endif
				}
			}
		}

		//�萔�o�b�t�@�X�V
		CDirectXGraphics::GetInstance()->GetImmediateContext()->UpdateSubresource(mConstantBuffer.Get() , 0 , nullptr , &mConstantBufferLightData , 0 , 0);
	}

	//�萔�o�b�t�@�����W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
	CDirectXGraphics::GetInstance()->GetImmediateContext()->VSSetConstantBuffers(4 , 1 , mConstantBuffer.GetAddressOf());
	//�萔�o�b�t�@�����W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
	CDirectXGraphics::GetInstance()->GetImmediateContext()->PSSetConstantBuffers(4 , 1 , mConstantBuffer.GetAddressOf());
}
