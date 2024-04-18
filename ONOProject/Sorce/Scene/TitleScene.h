#pragma once
#include <memory>
#include "BaseScene.h"
#include "../Common/Vector2.h"
class SoundController;
class TitleBoundObject;

class TitleScene :
    public BaseScene
{
public:
	TitleScene(SceneManager& sceneManager);
	virtual ~TitleScene();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

private:

	//タイトル画像
	int titleImg_;

	//フォントハンドル
	int fontHandle_;

	//スタート座標
	Vector2 startPos_;

	//BGM
	std::unique_ptr<SoundController> bgm_;

	//デルタタイム
	float deltaTime_;

	//跳ねるオブジェクト
	std::vector<std::unique_ptr<TitleBoundObject>> boundObjcts_;
};

