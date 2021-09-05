#include "CLightManager.h"
#include "../Components/CLightComponent.h"

CLightManager& CLightManager::GetInstance()
{
	static CLightManager instance;

	return instance;
}

void CLightManager::AddLight(CLightComponent& light)
{
	mLights.emplace_back(&light);
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
}

bool CLightManager::Init()
{
	//コンスタントバッファ作成
	bool sts = CreateConstantBuffer(CDirectXGraphics::GetInstance()->GetDXDevice(), sizeof(ConstantBufferLight), mConstantBufferLight.GetAddressOf());
	if (!sts)
	{
		MessageBox(NULL, "CreateBuffer(constant buffer Light) error", "Error", MB_OK);
		return false;
	}
	return true;
}

void CLightManager::Update()
{
	int count=0;

	ConstantBufferLight cb;

	CLightComponent* null = nullptr;
	mLights.emplace_back(null);

	cb.EyePos.w = 1.0;
	cb.EyePos.x = mEyePos.x;
	cb.EyePos.y = mEyePos.y;
	cb.EyePos.z = mEyePos.z;

	cb.LightDirection.x = mLightDirection.x;
	cb.LightDirection.y = mLightDirection.y;
	cb.LightDirection.z = mLightDirection.z;
	cb.LightDirection.w = mLightDirection.w;

	cb.Ambient = mAmbient;

	for (auto itr = mLights.begin(); itr==mLights.end(); itr++)
	{
		
	}

	mLights.pop_back();
	mLights.shrink_to_fit();

	CDirectXGraphics::GetInstance()->GetImmediateContext()->UpdateSubresource(mConstantBufferLight.Get(), 0, nullptr, &cb, 0, 0);

	// コンスタントバッファ4をｂ4レジスタへセット（頂点シェーダー用）
	CDirectXGraphics::GetInstance()->GetImmediateContext()->VSSetConstantBuffers(4, 1, mConstantBufferLight.GetAddressOf());
	// コンスタントバッファ4をｂ4レジスタへセット(ピクセルシェーダー用)
	CDirectXGraphics::GetInstance()->GetImmediateContext()->PSSetConstantBuffers(4, 1, mConstantBufferLight.GetAddressOf());
}
