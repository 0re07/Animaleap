#pragma once
#include <map>
#include <string>
#include <memory>
#include "Resource.h"

class ResourceManager
{

public:

	// リソース名
	enum class SRC
	{
		//3Dモデル
		CHARACTER_DOG_MODEL,				//犬：キャラクター
		CHARACTER_FISH_MODEL,				//魚：キャラクター
		CHARACTER_CHICKEN_MODEL,			//鶏：キャラクター
		OBSTACLE_MODEL,					//お邪魔玉
		CLOUD_MODEL,					//雲
		TRAMPOLINE_COLLSION_MODEL,		//トランポリンのコリジョン
		WALL_MODEL,						//壁
		GOAL_MODEL,						//ゴール
		CHARACTER_CANON_MODEL,			//キャラクター砲台
		OBSTACLE_CANON_MODEL,			//お邪魔砲台

		//エフェクト
		HIT_EFFECT,						//トランポリンとのヒットエフェクト
		GOAL_LEFT_EFFECT,				//ゴールした時のエフェクト(左)
		GOAL_RIGHT_EFFECT,				//ゴールした時のエフェクト(右)
		GOAL_OPEN_EFFECT,				//ゴールが開いているときのエフェクト

		//SE
		TITLE_BGM,
		GAME_BGM,
		BOUND_SE,
		GOAL_SE,
		SETTLEMENT_SE,
		FALL_SE,
		FIRE_SE,

		WIN_IMAGE_1,
		WIN_IMAGE_2

	};

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static ResourceManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);

	// リソースの完全破棄
	void Destroy(void);

	// リソースのロード
	const Resource& Load(SRC src);

	// リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	// 静的インスタンス
	static ResourceManager* instance_;

	// リソース管理の対象
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;

	// 読み込み済みリソース
	std::map<SRC, Resource&> loadedMap_;

	Resource dummy_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);
	ResourceManager(const ResourceManager& manager) = default;
	~ResourceManager(void) = default;

	// 内部ロード
	Resource& _Load(SRC src);

};
