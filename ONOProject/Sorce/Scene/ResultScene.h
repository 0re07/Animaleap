#pragma once
#include "BaseScene.h"

class ResultScene :
    public BaseScene
{
public:
	ResultScene(SceneManager& sceneManager);
	virtual ~ResultScene();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

private:
	int winImage1_;
	int winImage2_;

};

