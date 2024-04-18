#pragma once
class SceneUI
{
public:
	SceneUI();
	~SceneUI();

	virtual void Init(void) = 0;
	virtual void Draw(void) = 0;

private:

};

