#include "cocos2d.h"
#include "Object.h"
#include "DinamicObject.h"


DinamicObject::DinamicObject(cocos2d::Sprite* obj) : LogObject::LogObject(obj)
{

}

void DinamicObject::addImpulse(cocos2d::Vec2 impulse)
{
	if (sprite != nullptr)
	{
		if (sprite->getPhysicsBody() != nullptr)
		{
			sprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0, 0));
			sprite->getPhysicsBody()->applyImpulse(impulse);
		}
	}
}

void DinamicObject::setMass(float mass)
{
	if (sprite != nullptr)
	{
		if (sprite->getPhysicsBody() != nullptr)
		{
			sprite->getPhysicsBody()->setMass(mass);
		}
	}
}

void DinamicObject::setLinearDamping(size_t LinearDamping)
{
	if (sprite != nullptr)
	{
		if (sprite->getPhysicsBody() != nullptr)
		{
			sprite->getPhysicsBody()->setLinearDamping(LinearDamping);
		}
	}
}


void DinamicObject::setGravity(bool on)
{
	if (sprite != nullptr)
	{
		if (sprite->getPhysicsBody() != nullptr)
		{
			sprite->getPhysicsBody()->setGravityEnable(on);
		}
	}
}


