#pragma once
#include <list>
#include "../BoundObject/Character.h"
#include "GenerateObject.h"


class Obstacle;

class ObstacleCanon :
    public GenerateObject
{
public:
    ObstacleCanon(GameScene& gameScene, const VECTOR& pos, const VECTOR& scl, const VECTOR& rot);
    virtual ~ObstacleCanon();

    virtual void Init(void)override;
    virtual void Release(void)override;
    virtual void Update(float deltaSeconds)override;
    virtual void Draw(void)override;

    //おじゃまの生成
    void Generate(Player::PLAYER_TYPE type, Character::CHARACTOR_LEVEL level);

    //
    void Fire(void);


private:
    // 当たり判定後処理（関数）をcollisionCallbacks_にセットする
    virtual void InitCollisionAfter(void) override;

    //お邪魔生成時使用変数
    VECTOR obstacleScl_;
    VECTOR obstacleRot_;
    Player::PLAYER_TYPE fallPlayerType_;
    VECTOR moveDir_;
    float fallPow_;
    int max_;

    bool isFire_;
    int count_;

};

