#include <DxLib.h>
#include "DeltaTimeManager.h"

DeltaTimeManager::DeltaTimeManager() :
	deltaSeconds_(0.0f),
	prevFrameTime_(0),
	deltaTotalTime_(0.0f),
	timeScale_(1.0f)

{
	prevFrameTime_ = GetNowCount();
}

DeltaTimeManager::~DeltaTimeManager()
{
}

void DeltaTimeManager::Update(void)
{
	// DeltaSeconds‚ÌŒvŽZ(•b)
	int current_frame_time = GetNowCount();
	deltaSeconds_ = (float)(current_frame_time - prevFrameTime_) / 1000.0f;
	if (deltaSeconds_ > 0.5f)
	{
		deltaSeconds_ = 0.5f;
	}
	prevFrameTime_ = current_frame_time;
	deltaTotalTime_ += deltaSeconds_;

}

float DeltaTimeManager::GetDeltaSconds(void) const
{
	return deltaSeconds_ * timeScale_;
}

void DeltaTimeManager::SetTimeScale(float timeScale)
{
	timeScale_ = timeScale;
}
