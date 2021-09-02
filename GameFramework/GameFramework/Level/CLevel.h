#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "../Object/CObject.h"
#include "../Actor/CActor.h"
#include "../Interfaces/IRender.h"

class IGame;
class IRender;
class CGame;
class CLevel;
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
	virtual void AddImGuiDrawFunction(std::function<void()> func) = 0;
	virtual void RequestRenderOrders(std::vector<SRenderInfo>& renderOrders) = 0;
	virtual void AddDoBeforeUpdateFunction(std::function<void()> func) = 0;
	virtual void Notice(CActor& actor) = 0;
};

//レベルクラス
class CLevel :public CObject , public ILevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;					//アクター

	std::vector<std::function<void()>> mDoBeforeUpdateFunction;		//更新後に行う関数オブジェクト
	std::vector<std::function<void()>> mImGuiDrawFunction;			//ImGuiに行わせる描画の関数オブジェクト

	//レンダーコンポーネント
	std::vector<IRender*> m3DOpacityRenderComponents;
	std::vector<std::pair<IRender* , float>> m3DTranslucentRenderComponents;
	std::vector<IRender*> m2DOpacityRenderComponents;
	std::vector<IRender*> m2DTranslucentRenderComponents;

	CCameraComponent* mRenderingCamera = nullptr;		//レンダーを担当するカメラ

protected:
	IGame& mOwnerInterface;			//ゲームインターフェース

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

	void Add3DOpacityRenderComponent(IRender& renderTarget)
	{
		m3DOpacityRenderComponents.emplace_back(&renderTarget);
	}

	void Add3DTranslucentRenderComponent(IRender& renderTarget , float distanceToCamera)
	{
		m3DTranslucentRenderComponents.emplace_back(&renderTarget , distanceToCamera);
	}

	void Add2DOpacityRenderComponent(IRender& renderTarget)
	{
		m2DOpacityRenderComponents.emplace_back(&renderTarget);
	}

	void Add2DTranslucentRenderComponent(IRender& renderTarget)
	{
		m2DTranslucentRenderComponents.emplace_back(&renderTarget);
	}

	void AddDoBeforeUpdateFunction(std::function<void()> func)override
	{
		mDoBeforeUpdateFunction.emplace_back(func);
	}

	void RequestRenderOrders(std::vector<SRenderInfo>& renderOrders)override;

	virtual void Notice(CActor& actor)override {};

protected:
	//カメラのセットをリクエスト
	void RequestSetCamera(CCameraComponent& camera)override;

	void AddImGuiDrawFunction(std::function<void()> func)override
	{
		mImGuiDrawFunction.emplace_back(func);
	}

	template<class T>
	bool GetActor(CActor*& result)
	{
		for(auto& actor : mActors)
		{
			if(typeid(T) == typeid(*actor))
			{
				result = actor.get();
				return true;
			}
		}
		return false;
	}

	template<class T>
	bool GetAllActor(std::vector<CActor*>& result)
	{
		for(auto& actor : mActors)
		{
			if(typeid(T) == typeid(*actor))
			{
				result.emplace_back(actor.get());
			}
		}
		if(result.size() != 0)return true;
		else return false;
	}

public:
	//★超重要★　コンストラクタを呼ぶことはレベルの遷移を意味する
	CLevel(IGame& owner , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f);

	virtual ~CLevel();

	/*
	★超重要★
	アクターの追加は基本ここで行う
	コンポーネント追加することができるが非推奨
	コンポーネントはアクターのコンストラクタで追加することを推奨
	*/
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

	const XMFLOAT4X4* GetRenderingCameraViewMatrix()const;

	const XMFLOAT3* GetRenderingCameraLocation()const;
};