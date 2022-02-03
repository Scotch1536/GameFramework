//!
//! @file
//! @brief ライトマネージャーのヘッダーファイル
//!

#pragma once
#include <vector>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"

constexpr int LIGHT_NUM = 10;		//< 各種におけるライトの数

class CLightComponent;

//! @brief ライトコンポーネント用ライトマネージャーインターフェースクラス
class ILightManagerToLightComponent
{
public:
	//! @brief デストラクタ
	virtual ~ILightManagerToLightComponent() {};

	//!
	//! @brief ライト追加
	//! @param[in] lighr 追加するライト
	//!
	virtual void AddLight(CLightComponent& light) = 0;

	//!
	//! @brief ライト解放
	//! @param[in] lighr 解放するライト
	//!
	virtual void ReleaseLight(CLightComponent& light) = 0;
};

//! @brief ライトマネージャークラス
class CLightManager :public ILightManagerToLightComponent
{
private:
	//! @brief ポイントライト構造体
	ALIGN16 struct SPointLight
	{
		XMFLOAT3 LightPos;			//!< ライト位置
		float Pad1;					//!< パディング
		XMFLOAT4 Attenuation;		//!< 減衰率
	};

	//! @brief スポットライト構造体
	ALIGN16 struct SSpotLight :public SPointLight
	{
		XMFLOAT3 Direction;			//!< ライトの向き
		float Pad2;					//!< パディング
		float Angle;				//!< 角度（ライトの広がり）
	};

	//! @brief ライト定数バッファ構造体
	ALIGN16 struct SConstantBufferLight
	{
		XMFLOAT3 EyePos;							//!< 目の位置
		float Pad1;									//!< パディング
		XMFLOAT3 DirectionLightData;				//!< 平行光源データ
		float Pad2;									//!< パディング
		XMFLOAT3 AmbientLightData;					//!< 環境光データ
		float Pad3;									//!< パディング
		SPointLight PointLights[LIGHT_NUM];			//!< ポイントライト
		SSpotLight SpotLights[LIGHT_NUM];			//!< スポットライト
	};

	std::vector<CLightComponent*> mLights;				//!< ライトデータ

	ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;		//!< 定数バッファ
	SConstantBufferLight mConstantBufferLightData;		//!< ライト定数バッファデータ

	XMFLOAT3 mEyePos;									//!< 目の位置
	XMFLOAT3 mDirectionLightData;						//!< 平行光源データ
	XMFLOAT3 mAmbientLightData;							//!< 環境光データ

	bool mShouldUpdate = false;							//!< 更新すべきか

	//! @brief コンストラクタ
	CLightManager();

	//コピー＆ムーブ禁止
	CLightManager(const CLightManager&) = delete;
	CLightManager& operator=(const CLightManager&) = delete;
	CLightManager(CLightManager&&) = delete;
	CLightManager& operator=(CLightManager&&) = delete;

	//!
	//! @brief ライト追加
	//! @param[in] lighr 追加するライト
	//!
	void AddLight(CLightComponent& light);

	//!
	//! @brief ライト解放
	//! @param[in] lighr 解放するライト
	//!
	void ReleaseLight(CLightComponent& light);

public:
	//!
	//! @brief インスタンス取得
	//! @return CLightManager& インスタンス
	//!
	static CLightManager& GetInstance();

	//! @brief 更新
	void Update();

	//!
	//! @brief 通知
	//! @details ライトの作成や変更が行われたときにマネージャーに通知して更新を促す
	//!
	void Notice()
	{
		mShouldUpdate = true;
	}

	//!
	//! @brief 平行光源のセット
	//! @param[in] direction 平行光源の向き
	//!
	void SetDirectionLight(XMFLOAT3 direction)
	{
		mDirectionLightData = direction;
		Notice();
	}

	//!
	//! @brief 環境光のセット
	//! @param[in] ambient 環境の色情報
	//!
	void SetAmbientLight(XMFLOAT3 ambient)
	{
		mAmbientLightData = ambient;
		Notice();
	}

};