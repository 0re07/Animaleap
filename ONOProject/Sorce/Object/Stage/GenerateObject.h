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
    // �����蔻��㏈���i�֐��j��collisionCallbacks_�ɃZ�b�g����
    virtual void InitCollisionAfter(void) override;

    GameScene& gameScene_;

    Player::PLAYER_TYPE playerType_;

    //�o�ߕb��
    float delta_;
};

