#include "../Components/CPointLightComponent.h"
#include "../Components/CSpotLightComponent.h"
#include "../Components/CLightComponent.h"
#include "../Library/LCMath.h"

#include "CGameManager.h"

#include "CLightManager.h"


CLightManager::CLightManager()
{
	//コンスタントバッファ作成
	bool sts = CreateConstantBuffer(CDirectXGraphics::GetInstance()->GetDXDevice(), sizeof(ConstantBufferLight), mConstantBuffer.GetAddressOf());
	if (!sts)
	{
		MessageBox(NULL, "CreateBuffer(constant buffer Light) error", "Error", MB_OK);
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
	for (auto itr = mLights.begin(); itr != mLights.end(); itr++)
	{
		if ((*itr) == &light)
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
	const XMFLOAT3* cameraLocation = nullptr;
	cameraLocation = CGameManager::GetInstance().GetCameraLocation();

	if (cameraLocation != nullptr)
	{
		if (!LCMath::CompareFloat3(mEyePos, *cameraLocation))
		{
			mShouldUpdate = true;
			mEyePos = *cameraLocation;
		}
	}

	if (mShouldUpdate)
	{
		int countPL = 0;
		int countSL = 0;

		mShouldUpdate = false;
		mConstantBufferLightData.EyePos = mEyePos;
		mConstantBufferLightData.DirectionLightData = mDirectionLightData;
		mConstantBufferLightData.AmbientLightData = mAmbientLightData;

		for (auto& light : mLights)
		{
			if (light->GetType() == CLightComponent::EType::POINT)
			{
				if (countPL < LIGHT_NUM)
				{
					CPointLightComponent& buf = dynamic_cast<CPointLightComponent&>(*light);
					mConstantBufferLightData.PointLights[countPL].LightPos = buf.Transform.GetWorldLocation();
					mConstantBufferLightData.PointLights[countPL].Attenuation = buf.GetAttenuation();
					countPL++;
				}
				else
				{
#ifdef _DEBUG
					MessageBox(NULL, "ライトマネージャーに格納可能なポイントライトを超えています。", "Error", MB_OK);
#endif
				}
			}
			else if (light->GetType() == CLightComponent::EType::SPOT)
			{
				if (countSL < LIGHT_NUM)
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
					MessageBox(NULL, "ライトマネージャーに格納可能なスポットライトを超えています。", "Error", MB_OK);
#endif
				}
			}
		}

		CDirectXGraphics::GetInstance()->GetImmediateContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr, &mConstantBufferLightData, 0, 0);
	}

	// コンスタントバッファ4をｂ4レジスタへセット（頂点シェーダー用）
	CDirectXGraphics::GetInstance()->GetImmediateContext()->VSSetConstantBuffers(4, 1, mConstantBuffer.GetAddressOf());
	// コンスタントバッファ4をｂ4レジスタへセット(ピクセルシェーダー用)
	CDirectXGraphics::GetInstance()->GetImmediateContext()->PSSetConstantBuffers(4, 1, mConstantBuffer.GetAddressOf());
}
