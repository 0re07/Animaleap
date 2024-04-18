#pragma once
#include "../Object.h"
class Background :
    public Object
{
public:
    Background(const VECTOR& pos, const VECTOR& scl, const VECTOR& rot);
    virtual ~Background();

    virtual void Init(void) override;
    virtual void Release(void) override;
    virtual void Update(float deltaSeconds) override;
    virtual void Draw(void) override;

private:
    virtual void InitCollisionAfter(void) override;
};

