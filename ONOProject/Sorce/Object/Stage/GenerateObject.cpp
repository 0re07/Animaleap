#include "../../Scene/GameScene.h"
#include "ObstacleCanon.h"
#include "CharacterCanon.h"
#include "GenerateObject.h"

GenerateObject::GenerateObject(GameScene& gameScene, const VECTOR& pos, const VECTOR& scl, const VECTOR& rot, Player::PLAYER_TYPE playerType):
	Object(pos, scl, rot), 
	gameScene_(gameScene),
	playerType_(playerType)
{

}

GenerateObject::~GenerateObject()
{
}

void GenerateObject::Init(void)
{
	//gameScene_.CreateObject<CharacterCanon>(gameScene_, VECTOR{}, VECTOR{}, VECTOR{});
	//gameScene_.CreateObject<ObstacleCanon>(gameScene_, VECTOR{}, VECTOR{}, VECTOR{});
}

void GenerateObject::Release(void)
{
}

void GenerateObject::Update(float deltaSeconds)
{
}

void GenerateObject::Draw(void)
{
}

void GenerateObject::InitCollisionAfter(void)
{
}
