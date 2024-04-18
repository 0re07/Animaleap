#pragma once

class SceneManager;

class BaseScene
{
public:
	BaseScene(SceneManager& sceneManager);
	virtual ~BaseScene();

	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(float deltaSeconds) = 0;
	virtual void Draw(void) = 0;

protected:

	SceneManager& sceneManager_;

};

