#pragma once
class DeltaTimeManager
{
public:
	DeltaTimeManager();
	~DeltaTimeManager();

	// �f���^�^�C���X�V
	void Update(void);

	float GetDeltaSconds(void) const;

	// timeScale�̒l�Ńf���^�^�C���̑�����ς���
	void SetTimeScale(float timeScale);

private:
	float deltaSeconds_;

	int prevFrameTime_;
	float deltaTotalTime_;
	float timeScale_;
};

