#pragma once
#include <vector>
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

class CLightComponent;

class CLightManager
{
private:

	XMFLOAT4 mEyePos;			//見ている位置
	XMFLOAT4 mLightDirection;	//w=0の時は方向 w=1の時は位置
	XMFLOAT4 mAmbient;			//アンビエント

	std::vector<CLightComponent*> mLights;

	struct SPLights
	{
		XMFLOAT4 LightPos;
		XMFLOAT4 Attenuation;
	};

	ALIGN16 struct ConstantBufferLight
	{
		XMFLOAT4 LightDirection;
		XMFLOAT4 EyePos;
		XMFLOAT4 Ambient;
		SPLights Lights[10];
	};

	ComPtr<ID3D11Buffer> mConstantBufferLight = nullptr;		//定数バッファ

	CLightManager() = default;

	//コピー＆ムーブ禁止
	CLightManager(const CLightManager&) = delete;
	CLightManager& operator=(const CLightManager&) = delete;
	CLightManager(CLightManager&&) = delete;
	CLightManager& operator=(CLightManager&&) = delete;

	bool Init();

public:
	static CLightManager& GetInstance();

	//ライトコンポーネントのポインタを追加
	void AddLight(CLightComponent& light);

	void ReleaseLight(CLightComponent& light);

	void Update();
	
	void SetEyePos(XMFLOAT4 eyepos)
	{
		mEyePos = eyepos;
	}

	void SetLightPos(XMFLOAT4 lightpos)
	{
		mLightDirection = lightpos;
	}

	void SetAmbient(XMFLOAT4 amb)
	{
		mAmbient = amb;
	}
};