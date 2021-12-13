#pragma once
#include <vector>
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

constexpr int LIGHT_NUM = 10;

class CLightComponent;

class ILightManagerToLightComponent
{
public:
	virtual void AddLight(CLightComponent& light) = 0;
	virtual void ReleaseLight(CLightComponent& light) = 0;
};

class CLightManager :public ILightManagerToLightComponent
{
private:
	ALIGN16 struct SPointLight
	{
		XMFLOAT3 LightPos;
		float Pad1;
		XMFLOAT4 Attenuation;
	};

	ALIGN16 struct SSpotLight :public SPointLight
	{
		XMFLOAT3 Direction;
		float Pad1;
		float Angle;
	};

	ALIGN16 struct SConstantBufferLight
	{
		XMFLOAT3 EyePos;
		float Pad1;
		XMFLOAT3 DirectionLightData;
		float Pad2;
		XMFLOAT3 AmbientLightData;
		float Pad3;
		SPointLight PointLights[LIGHT_NUM];
		SSpotLight SpotLights[LIGHT_NUM];
	};

	ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;		//�萔�o�b�t�@

	SConstantBufferLight mConstantBufferLightData;

	std::vector<CLightComponent*> mLights;

	XMFLOAT3 mEyePos;			//���Ă���ʒu

	XMFLOAT3 mDirectionLightData;

	XMFLOAT3 mAmbientLightData;

	bool mShouldUpdate = false;

	CLightManager();

	//�R�s�[�����[�u�֎~
	CLightManager(const CLightManager&) = delete;
	CLightManager& operator=(const CLightManager&) = delete;
	CLightManager(CLightManager&&) = delete;
	CLightManager& operator=(CLightManager&&) = delete;

	//���C�g�R���|�[�l���g�̃|�C���^��ǉ�
	void AddLight(CLightComponent& light);

	//���C�g�R���|�[�l���g�̃|�C���^�����
	void ReleaseLight(CLightComponent& light);

public:
	static CLightManager& GetInstance();

	void Update();

	void Notice()
	{
		mShouldUpdate = true;
	}

	void SetDirectionLight(XMFLOAT3 direction)
	{
		mDirectionLightData = direction;
		Notice();
	}

	void SetAmbientLight(XMFLOAT3 ambient)
	{
		mAmbientLightData = ambient;
		Notice();
	}

};