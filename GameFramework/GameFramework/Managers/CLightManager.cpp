#include "../Components/CLightComponent.h"

#include "CGameManager.h"

#include "CLightManager.h"


CLightManager::CLightManager()
{
	//�R���X�^���g�o�b�t�@�쐬
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

	//// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
	//CDirectXGraphics::GetInstance()->GetImmediateContext()->VSSetConstantBuffers(4, 1, mConstantBufferLight.GetAddressOf());
	//// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
	//CDirectXGraphics::GetInstance()->GetImmediateContext()->PSSetConstantBuffers(4, 1, mConstantBufferLight.GetAddressOf());
}
