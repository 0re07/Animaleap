#pragma once
#include<DxLib.h>

class SoundController
{
public:

	SoundController(const int& soundHandle);
	~SoundController();

	void Update(void);

	/// <summary>
	/// 音声再生（一回きり）
	/// </summary>
	void Play(void);

	/// <summary>
	/// 音声再生（ループ）
	/// </summary>
	void PlayLoop(void);

	/// <summary>
	/// 再生中でなければ、音声を再生する
	/// </summary>
	void PlayNonPlaying(void);

	/// <summary>
	/// 再生中でなければ、音声をループ再生する
	/// </summary>
	void PlayNonPlayingLoop(void);

	/// <summary>
	/// 音声停止
	/// </summary>
	void Stop(void);

	/// <summary>
	/// 再生中か判断
	/// </summary>
	/// <returns>true:再生中　false:再生中ではない</returns>
	bool CheckPlaySound(void);

	/// <summary>
	/// 音量の設定
	/// </summary>
	/// <param name="volume">音量</param>
	void SetVolume(const int& volume);

	/// <summary>
	/// 再生周波数の設定
	/// </summary>
	/// <param name="frequencyPal">設定する再生周波数</param>
	void SetSoundFrequency(const int& frequencyPal);

	/// <summary>
	/// 音量倍率の変更
	/// </summary>
	/// <param name="frequencyPal">音量倍率</param>
	void ChangeVolumeRate(const float& rate);



private:
	const int& soundHandle_;

	//音量
	int volume_;

	
};

