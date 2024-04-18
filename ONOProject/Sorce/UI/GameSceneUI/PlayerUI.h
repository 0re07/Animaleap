#pragma once
#include <vector>
#include <memory>
#include "../../Common/Vector2.h"

class Image;

class PlayerUI
{
public:
	PlayerUI();
	~PlayerUI();

	void Init(void);
	void Draw(void);

	void CreateLifeImage(int handle, int lifeNum, const Vector2& pos);
	void CreateCursolImage(int handle);

	// ���C�t�|�C���g�摜�̕\������1���炷
	void SubLifeImage(void);

	// �J�[�\���摜�̍��W�ύX
	void SetCursolImagePos(const Vector2& pos);

private:
	// ���C�t�|�C���g��UI�摜
	std::vector<std::unique_ptr<Image>> lifeImage_;

	// �J�[�\����UI�摜
	std::unique_ptr<Image> cursolImage_;
};

