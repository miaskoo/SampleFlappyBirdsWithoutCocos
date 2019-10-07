#include "cocos2d.h"
#include "Object.h"
#include "DinamicObject.h"
#include "Wall.h"

//материал для стены
cocos2d::PhysicsMaterial materiar_wall(1.0f, 0.0f, 0.8f);//плотность, отскакиваемость, шереховатость(скольжение)
extern float WORLD_SCALE;



Wall::Wall(cocos2d::Sprite *obj, cocos2d::Size proportion) : DinamicObject(obj)
{
	
	DinamicObject::createCollisionBox(proportion * WORLD_SCALE, materiar_wall);//60- это я подгонял коллизию под картинки
	sprite->setScale(sprite->getScale() );

	setEnableCollisionEvent(true);//включили эвенты коллизий

	//создали надстройки скоростей
	sprite->getPhysicsBody()->setAngularVelocityLimit(0);//не вращаемся
	sprite->getPhysicsBody()->setDynamic(false);
	sprite->getPhysicsBody()->setGravityEnable(false);
	setLinearDamping(0);
	setMass(0.01f);
	
	
}

void Wall::setEnable(bool x)
{
	sprite->getPhysicsBody()->setDynamic(x);
}