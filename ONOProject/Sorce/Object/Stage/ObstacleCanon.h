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

    //������܂̐���
    void Generate(Player::PLAYER_TYPE type, Character::CHARACTOR_LEVEL level);

    //
    void Fire(void);


private:
    // �����蔻��㏈���i�֐��j��collisionCallbacks_�ɃZ�b�g����
    virtual void InitCollisionAfter(void) override;

    //���ז��������g�p�ϐ�
    VECTOR obstacleScl_;
    VECTOR obstacleRot_;
    Player::PLAYER_TYPE fallPlayerType_;
    VECTOR moveDir_;
    float fallPow_;
    int max_;

    bool isFire_;
    int count_;

};

