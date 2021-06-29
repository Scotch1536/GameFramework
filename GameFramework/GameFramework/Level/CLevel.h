#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "../Object/CObject.h"
#include "../Actor/CActor.h"
#include "../Interfaces/IRender.h"

class IGame;
class CGame;
class CGameManager;
class IGameManagerToLevel;
class CCameraComponent;

class ILevel
{
public:
	virtual ~ILevel() {};
	virtual void DestroyActor(CActor& target) = 0;
	virtual void AddActor(CActor& actor) = 0;
	virtual void RequestSetCamera(CCameraComponent& camera) = 0;
};

//レベルクラス
class CLevel :public CObject , public ILevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;					//アクター
	std::vector<std::function<void()>> mDoAfterUpdateFunction;		//更新後に行う関数オブジェクト

	CCameraComponent* mRenderingCamera = nullptr;		//レンダーを担当するカメラ

protected:
	IGame* mOwnerInterface;			//ゲームインターフェース

private:
	//コピー禁止
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;

	/*アクター追加
	★超重要★
	子クラスは呼ぶことはできない
	アクターのコンストラクタを呼ぶことでアクターの参照から辿ってこのメソッドが呼ばれる
	*/
	void AddActor(CActor& actor)override;

	//アクターの破壊
	void DestroyActor(CActor& target)override;

protected:
	//カメラのセットをリクエスト
	void RequestSetCamera(CCameraComponent& camera)override;

public:
	//★超重要★　コンストラクタを呼ぶことはレベルの遷移を意味する
	CLevel(CGame& owner);

	/*
	★超重要★
	ゲームマネージャーにレベルを送る場合のみゲームの参照なしでコンストラクタを呼び出し可能
	開始レベルの設定のためなので一度のみ可能二度目からはエラーで終了する
	*/
	CLevel(IGameManagerToLevel& receiver);

	virtual ~CLevel() {};

	//初期化
	virtual void Init() = 0;

	//更新
	void Update()override;

	/*
	毎フレーム行う処理（子クラスのための機能）
	プロトタイプなどの簡単に試したい時のために用意したので
	本制作での利用は非推奨
	ポーズなどの制御がされていないのでバグの温床になる
	*/
	virtual void Tick() {};

	//描画
	void Render()override;

	//インターフェースのセット　ゲームマネージャーからしか呼び出す想定をしていない
	void SetOwnerInterface(CGame& owner);
};