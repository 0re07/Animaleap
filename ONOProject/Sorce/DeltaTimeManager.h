#pragma once
class DeltaTimeManager
{
public:
	DeltaTimeManager();
	~DeltaTimeManager();

	// デルタタイム更新
	void Update(void);

	float GetDeltaSconds(void) const;

	// timeScaleの値でデルタタイムの速さを変える
	void SetTimeScale(float timeScale);

private:
	float deltaSeconds_;

	int prevFrameTime_;
	float deltaTotalTime_;
	float timeScale_;
};

