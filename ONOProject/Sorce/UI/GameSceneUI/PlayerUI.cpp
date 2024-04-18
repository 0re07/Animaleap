#include <assert.h>
#include "../../Resource/ResourceManager.h"
#include "../Image.h"
#include "PlayerUI.h"

// ライフポイント画像描画間隔
constexpr int LIFE_IMAGE_INTERVAL = 60;

PlayerUI::PlayerUI()
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init(void)
{
}

void PlayerUI::Draw(void)
{
	for (const auto& lifeImage : lifeImage_)
	{
		lifeImage->Draw();
	}
}

void PlayerUI::CreateLifeImage(int handle, int lifeNum, const Vector2& pos)
{
	for (int n = 0; n < lifeNum; n++)
	{
		lifeImage_.emplace_back(std::make_unique<Image>(handle, Vector2{ pos.x + n * LIFE_IMAGE_INTERVAL ,pos.y }));
	}
}

void PlayerUI::CreateCursolImage(int handle)
{
	cursolImage_ = std::make_unique<Image>(handle, Vector2{});
}

void PlayerUI::SubLifeImage(void)
{
	assert(lifeImage_.size() > 0);
	lifeImage_.pop_back();
}

void PlayerUI::SetCursolImagePos(const Vector2& pos)
{
	cursolImage_->SetPos(pos);
}
