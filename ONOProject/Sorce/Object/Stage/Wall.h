#pragma once
#include "../Object.h"

class Wall :
    public Object
{
public:
    Wall(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot);
    virtual ~Wall();

    virtual void Init(void)override;
    virtual void Release(void)override;
    virtual void Update(float deltaSeconds)override;
    virtual void Draw(void)override;

private:
    // �����蔻��㏈���i�֐��j��collisionCallbacks_�ɃZ�b�g����
    virtual void InitCollisionAfter(void) override;

};

