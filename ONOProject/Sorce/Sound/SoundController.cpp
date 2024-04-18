#include "SoundController.h"

SoundController::SoundController(const int& soundHandle):
	soundHandle_(soundHandle)
{
}

SoundController::~SoundController()
{
}

void SoundController::Play(void)
{
	//âπê∫ÇÃçƒê∂
	PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK);
}

void SoundController::PlayLoop(void)
{
	//âπê∫ÇÃçƒê∂
	PlaySoundMem(soundHandle_, DX_PLAYTYPE_LOOP);
}

void SoundController::PlayNonPlaying(void)
{
	if (!CheckPlaySound())
	{
		Play();
	}
}

void SoundController::PlayNonPlayingLoop(void)
{
	if (!CheckPlaySound())
	{
		PlayLoop();
	}
}

void SoundController::Stop(void)
{
	StopSoundMem(soundHandle_);
}

bool SoundController::CheckPlaySound(void)
{
	return CheckSoundMem(soundHandle_);
}

void SoundController::Update(void)
{
}

void SoundController::SetVolume(const int& volume)
{
	volume_ = volume;
	ChangeVolumeSoundMem(volume_, soundHandle_);
}

void SoundController::SetSoundFrequency(const int& frequencyPal)
{
	SetFrequencySoundMem(frequencyPal, soundHandle_);
}

void SoundController::ChangeVolumeRate(const float& rate)
{
	ChangeVolumeSoundMem(volume_ * rate, soundHandle_);
}

