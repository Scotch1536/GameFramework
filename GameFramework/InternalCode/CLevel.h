#pragma once
#include <vector>
#include <memory>

#include "CActor.h"
#include "IRender.h"

class IGame;
class CGame;
class CCameraComponent;

class ILevel
{
public:
	virtual ~ILevel() {};
	virtual void DestroyActor(CActor& target) = 0;
};

class CLevel :public ILevel , public IRender
{
private:
	friend CActor::CActor(CLevel&);

	CCameraComponent* mRenderingCamera = nullptr;		//レンダーを担当するカメラ
	std::vector<std::unique_ptr<CActor>> mActors;		//アクター

protected:
	IGame& mOwnerInterface;								//ゲームインターフェース

private:
	//コピー禁止
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;

	/*アクター追加
	★超重要★子クラスは呼ぶことはできない
	アクターのコンストラクタを呼ぶことでアクターの参照から辿ってこのメソッドが呼ばれる
	*/
	void AddActor(CActor& actor);
protected:
	//カメラのセットをリクエスト
	void RequestSetCamera(CCameraComponent& camera);

public:
	//★超重要★　コンストラクタを呼ぶことはレベルの遷移を意味する
	CLevel(CGame& owner);

	virtual ~CLevel() = default;

	//初期化
	virtual void Init() = 0;

	//更新
	void Update();

	//描画
	void Render()override;

	//アクターの破壊
	void DestroyActor(CActor& target)override;
};