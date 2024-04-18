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

    //�S�[�����J���鏈��
    void OpenSign(void);

    //�S�[������鏈��
    void CloseSign(void);

    //�S�[���J��Ԏ擾����ŏ���
    bool GetIsOpen(void);

    //�S�[�����Ă��邩
    bool GetIsGoal(void);

    //�S�[�����Ă��邩�����false�ɂ���
    void SetIsGoalFalse(void);

    //�S�[�������v���C���[
    Player::PLAYER_TYPE GetPlayerType(void);

    //�S�[���̕`��F��ύX����
    void SetGoalColor(float Red, float Green, float Blue, float Alpha);

private:
    //�G�t�F�N�g�̍Đ�
    void PlayOpenEffect(void);
    void PlayLeftEffect(void);
    void PlayRightEffect(void);

    // �����蔻��㏈���i�֐��j��collisionCallbacks_�ɃZ�b�g����
    virtual void InitCollisionAfter(void) override;

    //�����蔻��㏈��
    void GoalAfterCharacterCollision(const CollisionAfterData& collisionData, Object& hitObject);

    //�S�[���̊J�t���O
    bool isOpen_;

    //�S�[�����Ă��邩�@�������Ƃ悭�ł�����
    bool isGoal_;

    //�S�[�������v���C���[
    Player::PLAYER_TYPE playerType_;

    //�G�t�F�N�g
    int goalLeftEffect_;
    int goalRightEffect_;
    int goalOpenEffect_;

    //
    int img_;

    int countLeft_;
    int countRight_;



};

