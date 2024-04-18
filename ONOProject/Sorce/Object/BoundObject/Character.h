#pragma once
#include <memory>
#include "../../Player/Player.h"
#include "BoundObject.h"
class ModelMaterial;
class ModelRenderer;

class Character :
    public BoundObject
{
public:
	//当たり判定の半径
	static constexpr float HIT_SIZE_RADIOUS = 20;

	//キャラレベル
	enum class CHARACTOR_LEVEL
	{
		LEVEL_1,
		LEVEL_2,
		LEVEL_3
	};

	/// <summary>
	/// キャラクターのコンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="scl">大きさ</param>
	/// <param name="rot">角度</param>
	/// <param name="playerType">プレイヤータイプ</param>
	/// <param name="moveDir">移動方向</param>
	/// <param name="fallingPow">落下量</param>
	Character(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, const Player::PLAYER_TYPE& playerType,
		const VECTOR& moveDir, const float& fallingPow);
	virtual ~Character();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

	//キャラレベルの取得
	const CHARACTOR_LEVEL& GetCharaLevel(void)const {return level_;}
	//プレイヤータイプの取得
	const Player::PLAYER_TYPE& GetPlayerType(void)const { return playerType_; }
	//プレイヤータイプの設定
	const void SetPlayerType(const Player::PLAYER_TYPE& type){ playerType_ = type; }

	//ジャンプ処理
	void JumpProcess(const VECTOR& jumpDir, const float& jumpRate)override;

	//キャラレベルアップのチェック
	void CheckLevelUp(void);

private:
	//レベル別モデル
	int dogModelHandle_;
	int fishModelHandle_;
	int chickenModelHandle_;
	
	//バウンド回数
	int boundCount_;

	//キャラクターレベル
	CHARACTOR_LEVEL level_;

	//ローカル座標（モデルをずらす距離）
	VECTOR localPos;

	std::unique_ptr<ModelMaterial> testMaterial_;
	std::unique_ptr<ModelRenderer> testRenderer_;


};

