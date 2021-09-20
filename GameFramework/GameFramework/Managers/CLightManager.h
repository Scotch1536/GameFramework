#pragma once
#include <vector>
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

constexpr int LIGHT_NUM = 10;

class CLightComponent;

class CLightManager
{
private:
	ALIGN16 struct PointLight
	{
		XMFLOAT3 LightPos;
		XMFLOAT4 Attenuation;
	};

	ALIGN16 struct SpotLight:public PointLight
	{
		XMFLOAT3 Direction;
		float Angle;
	};

	ALIGN16 struct ConstantBufferLight
	{
		XMFLOAT3 EyePos;
		XMFLOAT3 DirectionLightData;
		XMFLOAT3 AmbientLightData;
		PointLight PointLights[LIGHT_NUM];
		SpotLight SpotLights[LIGHT_NUM];
	};

	ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;		//�萔�o�b�t�@

	ConstantBufferLight mConstantBufferLightData;

	std::vector<CLightComponent*> mLights;

	XMFLOAT3 mEyePos;			//���Ă���ʒu

	XMFLOAT3 mDirectionLightData;

	XMFLOAT3 mAmbientLightData;

	bool mShouldUpdate=false;

	CLightManager();

	//�R�s�[�����[�u�֎~
	CLightManager(const CLightManager&) = delete;
	CLightManager& operator=(const CLightManager&) = delete;
	CLightManager(CLightManager&&) = delete;
	CLightManager& operator=(CLightManager&&) = delete;

public:
	static CLightManager& GetInstance();

	//���C�g�R���|�[�l���g�̃|�C���^��ǉ�
	void AddLight(CLightComponent& light);

	void ReleaseLight(CLightComponent& light);

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