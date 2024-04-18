#pragma once
#include<DxLib.h>

class SoundController
{
public:

	SoundController(const int& soundHandle);
	~SoundController();

	void Update(void);

	/// <summary>
	/// �����Đ��i��񂫂�j
	/// </summary>
	void Play(void);

	/// <summary>
	/// �����Đ��i���[�v�j
	/// </summary>
	void PlayLoop(void);

	/// <summary>
	/// �Đ����łȂ���΁A�������Đ�����
	/// </summary>
	void PlayNonPlaying(void);

	/// <summary>
	/// �Đ����łȂ���΁A���������[�v�Đ�����
	/// </summary>
	void PlayNonPlayingLoop(void);

	/// <summary>
	/// ������~
	/// </summary>
	void Stop(void);

	/// <summary>
	/// �Đ��������f
	/// </summary>
	/// <returns>true:�Đ����@false:�Đ����ł͂Ȃ�</returns>
	bool CheckPlaySound(void);

	/// <summary>
	/// ���ʂ̐ݒ�
	/// </summary>
	/// <param name="volume">����</param>
	void SetVolume(const int& volume);

	/// <summary>
	/// �Đ����g���̐ݒ�
	/// </summary>
	/// <param name="frequencyPal">�ݒ肷��Đ����g��</param>
	void SetSoundFrequency(const int& frequencyPal);

	/// <summary>
	/// ���ʔ{���̕ύX
	/// </summary>
	/// <param name="frequencyPal">���ʔ{��</param>
	void ChangeVolumeRate(const float& rate);



private:
	const int& soundHandle_;

	//����
	int volume_;

	
};

