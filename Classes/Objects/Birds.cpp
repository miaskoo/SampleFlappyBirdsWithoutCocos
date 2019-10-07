#include "cocos2d.h"
#include "Object.h"
#include "DinamicObject.h"
#include "Birds.h"

cocos2d::PhysicsMaterial materiar_bird(1.f, 0.1f, 100.f);
extern float WORLD_SCALE;

Bird::Bird(cocos2d::Sprite* obj) : DinamicObject(obj)
{
	//птица жива - реагируем на эвенты
	dead = false;

	size_t r = 30;//радиус коллизии
	size_t m = 100;//масса
	size_t l = 1;//скорость поглащения импульса

	//эвент птицы
	Bird_Touch_Listener = cocos2d::EventListenerMouse::create();

	Bird_Touch_Listener->onMouseDown = [=](cocos2d::EventMouse *event)
	{
		this->onMouseDown();
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Bird_Touch_Listener, sprite);

	//применяем надстройки на физическое тело
	createCollisionCircle(r, materiar_bird);
	setMass(m);
	setLinearDamping(l);
	setGravity(false);

	setEnableCollisionEvent(true);//включили эвенты коллизий
	sprite->setScale(sprite->getScale() * 4 * WORLD_SCALE);//синхранизовали размер птицы с миром
}

void Bird::onMouseDown()
{
	if (dead == false)//если не выпущена из рагатки - эвенты не срабатывают
	{
		addImpulse(cocos2d::Vec2(0, 50000));
	}
}

void Bird::setDead(bool n)
{
	dead = n;
}
