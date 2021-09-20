#pragma once
#include <vector>
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

class CLightComponent;

class CLightManager
{
private:

	struct PointLight
	{
		XMFLOAT4 LightPos;
		XMFLOAT4 Attenuation;
	};

	struct SpotLight:public PointLight
	{
		XMFLOAT3 Direction;
		float Angle;
	};

	ALIGN16 struct ConstantBufferLight
	{
		XMFLOAT4 DirectionOfLightDirection;
		XMFLOAT4 EyePos;
		XMFLOAT4 Ambient;
		PointLight PointLights[10];
		SpotLight SpotLights[10];
	};

	ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;		//�萔�o�b�t�@

	ConstantBufferLight mConstantBufferLightData;

	std::vector<CLightComponent*> mLights;

	XMFLOAT4 mEyePos;			//���Ă���ʒu

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