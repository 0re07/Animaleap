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

	// ライフポイント画像の表示数を1つ減らす
	void SubLifeImage(void);

	// カーソル画像の座標変更
	void SetCursolImagePos(const Vector2& pos);

private:
	// ライフポイントのUI画像
	std::vector<std::unique_ptr<Image>> lifeImage_;

	// カーソルのUI画像
	std::unique_ptr<Image> cursolImage_;
};

