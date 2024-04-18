#pragma once
#include <list>
#include <memory>

#include "../Object/Object.h"
#include "BaseScene.h"

class Object;
class Player;
class Stage;
class SoundController;

class GameScene :
    public BaseScene
{
public:
	GameScene(SceneManager& sceneManager);
	virtual ~GameScene();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(float deltaSeconds) override;
	virtual void Draw(void) override;

	void GameOver(void);

	// �I�u�W�F�N�g�����֐�(objectList�ɓ����)
	template <typename T, typename... Args>
	void CreateObject(Args&&... args)
	{
		//static_assert(std::is_base_of<Object, T>::value, "T does not succeed to Object class");

		T* newInstance = new T(std::forward<Args>(args)...);

		Object* object = dynamic_cast<Object*>(newInstance);
		object->Init();

		objectList_.emplace_back(std::move(newInstance));
	}

	template <typename T, typename... Args>
	T* CreateObjectTest(Args&&... args)
	{
		return std::move(new T(std::forward<Args>(args)...));
	}

	void AddObjectList(Object* object);

	// �I�u�W�F�N�g���X�g�̒����犈�����̃g�����|�����̐���Ԃ�
	const std::list<std::unique_ptr<Object>>& GetObjectList(void) const;

private:

	void ObjectUpdate(float deltaSeconds);
	void ObjectDraw(void);
	void ObjectCollisionDraw(void);
	void ObjectCollision(void);
	void DeleteObject(void);
	
	// �I�u�W�F�N�g�ƃI�u�W�F�N�g�̓����蔻��
	void CheckCollision(Object& obj1, Object& obj2);

	std::list<std::unique_ptr<Object>> objectList_;

	std::unique_ptr<Player> leftPlayer_;
	std::unique_ptr<Player> rightPlayer_;

	std::unique_ptr<Stage> stage_;

	//BGM
	std::unique_ptr<SoundController> bgm_;
	//����SE
	std::unique_ptr<SoundController> settlementSE_;

};

