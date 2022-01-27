//!
//! @file
//! @brief スタティックメッシュコンポーネントのヘッダーファイル
//!

#pragma once
#include <string>

#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"
#include "../Data/CModelData.h"

#include "CComponent.h"

class CModelData;
class CRenderComponent;

//! @brief スタティックメッシュコンポーネントクラス
class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CModelData* mModel;							//!< モデルデータ
	CRenderComponent& mRenderComponent;			//!< レンダーコンポーネント

	//! @brief 更新
	void Update()override;

	//! @brief 描画
	void Render()override;

public:
	CTransform Transform;			//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] model モデルデータ
	//! @param[in] vertexShaderPath 頂点シェーダのパス
	//! @param[in] pixelShaderPath ピクセルシェーダのパス
	//!
	CStaticMeshComponent(CActor& owner , CTransform& parentTrans , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath);

	void SetModel(CModelData& model)
	{
		mModel = &model;
	}

	const CModelData& GetModel()
	{
		return *mModel;
	}

};