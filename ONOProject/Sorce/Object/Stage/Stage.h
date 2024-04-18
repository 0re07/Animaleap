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
	//�S�[�����R�쐬
	void CreateGoals(void);
	//�S�[����ύX
	void ChengeGoalObjects(float changeSec);
	//�e�L���m�����쐬
	void CreateCanonObjects(void);

	GameScene& gameScene_;

	//�S�[����
	Goal* goal_[GOAL_NUM];
	int goalOpenNow_;

	//���ז��L���m��
	ObstacleCanon* obstacleCanon_;

	//�o�ߕb��
	float delta_;

	//�o�ߕb���\���p
	float deltaSec_;
};

