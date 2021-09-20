#include "../Components/CLightComponent.h"

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
	CGameManager::GetInstance().

	if (mShouldUpdate)
	{
		mShouldUpdate = false;

	}

	//CDirectXGraphics::GetInstance()->GetImmediateContext()->UpdateSubresource(mConstantBufferLight.Get(), 0, nullptr, &cb, 0, 0);

	//// コンスタントバッファ4をｂ4レジスタへセット（頂点シェーダー用）
	//CDirectXGraphics::GetInstance()->GetImmediateContext()->VSSetConstantBuffers(4, 1, mConstantBufferLight.GetAddressOf());
	//// コンスタントバッファ4をｂ4レジスタへセット(ピクセルシェーダー用)
	//CDirectXGraphics::GetInstance()->GetImmediateContext()->PSSetConstantBuffers(4, 1, mConstantBufferLight.GetAddressOf());
}
