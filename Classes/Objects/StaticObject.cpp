#include "cocos2d.h"
#include "Object.h"
#include "StaticObject.h"

cocos2d::PhysicsMaterial materiar(1.f, 0.1f, 100.f);//плотность, отскакиваемость, шереховатость(скольжение)

StaticObject::StaticObject(cocos2d::Sprite* obj) : LogObject::LogObject(obj)
{

}

void StaticObject::createCollisionBox(cocos2d::Vec2 prop, bool dinamic)
{
	if (LogObject::createCollisionBox(cocos2d::Size(prop.x, prop.y), materiar))
	{
		sprite->getPhysicsBody()->setDynamic(dinamic);
	}
}

void StaticObject::createCollisionCircle(size_t r, bool dinamic)
{
	if (LogObject::createCollisionCircle(r, materiar))
	{
		sprite->getPhysicsBody()->setDynamic(dinamic);
		sprite->getPhysicsBody()->setGravityEnable(false);
	}
	
}
