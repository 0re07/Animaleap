#pragma once
#include "../../Player/Player.h"
#include "../Object.h"

class GameScene;

class GenerateObject :
    public Object
{
public:
    GenerateObject(GameScene& gameScene, const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, Player::PLAYER_TYPE playerType);
    virtual ~GenerateObject();

    virtual void Init(void)override;
    virtual void Release(void)override;
    virtual void Update(float deltaSeconds)override;
    virtual void Draw(void)override;

protected:
    // 当たり判定後処理（関数）をcollisionCallbacks_にセットする
    virtual void InitCollisionAfter(void) override;

    GameScene& gameScene_;

    Player::PLAYER_TYPE playerType_;

    //経過秒数
    float delta_;
};

