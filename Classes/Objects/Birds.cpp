#include "cocos2d.h"
#include "Object.h"
#include "DinamicObject.h"
#include "Birds.h"

cocos2d::PhysicsMaterial materiar_bird(1.f, 0.1f, 100.f);
extern float WORLD_SCALE;

Bird::Bird(cocos2d::Sprite* obj) : DinamicObject(obj)
{
	//����� ���� - ��������� �� ������
	dead = false;

	size_t r = 30;//������ ��������
	size_t m = 100;//�����
	size_t l = 1;//�������� ���������� ��������

	//����� �����
	Bird_Touch_Listener = cocos2d::EventListenerMouse::create();

	Bird_Touch_Listener->onMouseDown = [=](cocos2d::EventMouse *event)
	{
		this->onMouseDown();
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Bird_Touch_Listener, sprite);

	//��������� ���������� �� ���������� ����
	createCollisionCircle(r, materiar_bird);
	setMass(m);
	setLinearDamping(l);
	setGravity(false);

	setEnableCollisionEvent(true);//�������� ������ ��������
	sprite->setScale(sprite->getScale() * 4 * WORLD_SCALE);//�������������� ������ ����� � �����
}

void Bird::onMouseDown()
{
	if (dead == false)//���� �� �������� �� ������� - ������ �� �����������
	{
		addImpulse(cocos2d::Vec2(0, 50000));
	}
}

void Bird::setDead(bool n)
{
	dead = n;
}
