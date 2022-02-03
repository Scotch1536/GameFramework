//!
//! @file
//! @brief モデルデータマネージャーのヘッダーファイル
//!

#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <string>

#include "../Data/CModelData.h"

//! @brief モデルデータマネージャークラス
class CModelDataManager
{
private:
	std::unordered_map<std::string , CModelData> mModelData;				//!< モデルデータ

	std::filesystem::path mModelDataCachePath = "./ModelDataCache";			//!< モデルデータのキャッシュのディレクトリパス
	std::string mExtension = ".bin";										//!< 拡張子

	//! @brief コンストラクタ
	CModelDataManager() = default;

	//!
	//! @brief ファイル名の作成
	//! @param[in] filePath ファイルパス
	//!
	std::string MakeFileName(std::string filePath);

	//!
	//! @brief キャッシュデータの入力
	//! @param[in] target 対象のモデルデータ
	//! @param[in] filePath ファイルパス
	//! @return bool 入力が成功したか ※キャッシュデータがない場合失敗となる
	//!
	bool InputCache(CModelData& target , std::string filePath);

	//!
	//! @brief キャッシュデータの出力
	//! @param[in] target 対象のモデルデータ
	//! @param[in] filePath ファイルパス
	//!
	void OutputCache(CModelData& target , std::string filePath);

public:
	//コピー&ムーブ禁止
	CModelDataManager(const CModelDataManager&) = delete;
	CModelDataManager& operator=(const CModelDataManager&) = delete;
	CModelDataManager(CModelDataManager&&) = delete;
	CModelDataManager& operator=(CModelDataManager&&) = delete;

	//!
	//! @brief インスタンス取得
	//! @return CModelDataManager& インスタンス
	//!
	static CModelDataManager& GetInstance()
	{
		static CModelDataManager instance;
		return instance;
	}

	//!
	//! @brief モデルデータ取得
	//! @param[in] filePath ファイルパス
	//! @param[in] resourceFolderPath モデルのリソース（テクスチャなど）が置いてあるフォルダのパス
	//!
	CModelData& GetModel(std::string filePath , std::string resourceFolderPath);
};
