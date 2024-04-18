#pragma once
#include <memory>

constexpr int GOAL_NUM = 3;

class GameScene;
class ObstacleCanon;
class Goal;

class Stage
{
public:
	Stage(GameScene& gameScene);
	~Stage();

	void Init(void);
	void Release(void);
	void Update(float deltaSeconds);
	void Draw(void);

private:
	//ゴールを３つ作成
	void CreateGoals(void);
	//ゴールを変更
	void ChengeGoalObjects(float changeSec);
	//各キャノンを作成
	void CreateCanonObjects(void);

	GameScene& gameScene_;

	//ゴール※
	Goal* goal_[GOAL_NUM];
	int goalOpenNow_;

	//お邪魔キャノン
	ObstacleCanon* obstacleCanon_;

	//経過秒数
	float delta_;

	//経過秒数表示用
	float deltaSec_;
};

