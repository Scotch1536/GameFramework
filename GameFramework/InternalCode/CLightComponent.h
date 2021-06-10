#pragma once
#include "CDirectXGraphics.h"
#include "memory.h"
#include "CComponent.h"
#include "Shader.h"

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

	LightType mLightType = LightType::DIRECTIONAL;			//ライトタイプ

	XMFLOAT3 mEyePos;			//見ている位置
	XMFLOAT4 mLightPos;			//w=0の時は方向 w=1の時は位置
	XMFLOAT4 mAmbient;			//アンビエント

	ComPtr<ID3D11Buffer> mConstantBufferLight = nullptr;		//定数バッファ

	//初期化
	bool Init()
	{
		//コンスタントバッファ作成
		bool sts = CreateConstantBuffer(CDirectXGraphics::GetInstance()->GetDXDevice() , sizeof(ConstantBufferLight) , &mConstantBufferLight);
		if(!sts)
		{
			MessageBox(NULL , "CreateBuffer(constant buffer Light) error" , "Error" , MB_OK);
			return false;
		}
		return true;
	}
public:
	CLightComponent(IActor& owner , int priority = 40):CComponent(owner , priority)
	{
		mAttribute = CComponent::EAttribute::LIGHT;

		Init();
	}

	//更新
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

		// コンスタントバッファ4をｂ3レジスタへセット（頂点シェーダー用）
		CDirectXGraphics::GetInstance()->GetImmediateContext()->VSSetConstantBuffers(4 , 1 , mConstantBufferLight.GetAddressOf());
		// コンスタントバッファ4をｂ3レジスタへセット(ピクセルシェーダー用)
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