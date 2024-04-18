#pragma once
#include "../Object.h"

class Goal :
    public Object
{
public:
    Goal(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot);
    virtual ~Goal();

    virtual void Init(void)override;
    virtual void Release(void)override;
    virtual void Update(float deltaSeconds)override;
    virtual void Draw(void)override;

    //ゴールを開ける処理
    void OpenSign(void);

    //ゴールを閉じる処理
    void CloseSign(void);

    //ゴール開閉状態取得※後で消す
    bool GetIsOpen(void);

    //ゴールしているか
    bool GetIsGoal(void);

    //ゴールしているか判定をfalseにする
    void SetIsGoalFalse(void);

    //ゴールしたプレイヤー
    Player::PLAYER_TYPE GetPlayerType(void);

    //ゴールの描画色を変更する
    void SetGoalColor(float Red, float Green, float Blue, float Alpha);

private:
    //エフェクトの再生
    void PlayOpenEffect(void);
    void PlayLeftEffect(void);
    void PlayRightEffect(void);

    // 当たり判定後処理（関数）をcollisionCallbacks_にセットする
    virtual void InitCollisionAfter(void) override;

    //当たり判定後処理
    void GoalAfterCharacterCollision(const CollisionAfterData& collisionData, Object& hitObject);

    //ゴールの開閉フラグ
    bool isOpen_;

    //ゴールしているか　※もっとよくできそう
    bool isGoal_;

    //ゴールしたプレイヤー
    Player::PLAYER_TYPE playerType_;

    //エフェクト
    int goalLeftEffect_;
    int goalRightEffect_;
    int goalOpenEffect_;

    //
    int img_;

    int countLeft_;
    int countRight_;



};

