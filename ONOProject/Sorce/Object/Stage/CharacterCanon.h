#pragma once
#include <vector>
#include "GenerateObject.h"

class Character;

class CharacterCanon :
    public GenerateObject
{
public:
    CharacterCanon(GameScene& gameScene, const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, Player::PLAYER_TYPE playerType);
    virtual ~CharacterCanon();

    virtual void Init(void)override;
    virtual void Release(void)override;
    virtual void Update(float deltaSeconds)override;
    virtual void Draw(void)override;

    //キャラクターの生成
    void CreateCharacter(void);

private:
    // 当たり判定後処理（関数）をcollisionCallbacks_にセットする
    virtual void InitCollisionAfter(void) override;

};

