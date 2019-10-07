
#include <vector>
#include <array>
#include "cocos2d.h"
#include "Object.h"
#include "Pull.h"


LogObject::LogObject(cocos2d::Sprite* obj)//создает на сцене с указанной коллизией
{
	sprite = obj;
}

bool LogObject::createCollisionBox(cocos2d::Size proportion, const cocos2d::PhysicsMaterial& material)//колизия бокса
{
	if (sprite != nullptr)
	{
		auto body = cocos2d::PhysicsBody::create();
		auto shape = cocos2d::PhysicsShapeBox::create(proportion, material);

		body->addShape(shape);
		sprite->setPhysicsBody(body);
		Pull::getPull()->pushBack(this);
		return true;
	}
	return false;
}
bool LogObject::createCollisionCircle(size_t radius, const cocos2d::PhysicsMaterial& material)//колизия круга
{
	if (sprite != nullptr)
	{
		auto body = cocos2d::PhysicsBody::create();
		auto shape = cocos2d::PhysicsShapeCircle::create(radius, material);
		body->addShape(shape);
		sprite->setPhysicsBody(body);
		Pull::getPull()->pushBack(this);
		return true;
	}
	return false;
}


void LogObject::setPosition(cocos2d::Vec2 pos)
{
	if (sprite != nullptr)
	{
		sprite->setPosition(pos);
	}
}

void LogObject::setRotation(size_t angle)
{
	if (sprite != nullptr)
	{
		sprite->setRotation(angle);
	}
}

cocos2d::Vec2 LogObject::getPosition()
{
	if (sprite != nullptr)
	{
		return sprite->getPosition();
	}
	return { 0,0 };
}

cocos2d::Sprite* LogObject::getSprite()
{
	return sprite;
}

void LogObject::setEnableCollisionEvent(bool on)
{
	if (sprite != nullptr)
	{
		if (sprite->getPhysicsBody() != nullptr)
		{
			auto shape = sprite->getPhysicsBody()->getShape(0);
			if (shape != nullptr)
			{
				if (on == true)
				{
					shape->setContactTestBitmask(0xFFFFFFFF);//нам нужно отслеживать коллизию объектов у объектов
				}
				else
				{
					shape->setContactTestBitmask(0x00000000);
				}
			}
		}
	}
}


LogObject::~LogObject()
{
}
