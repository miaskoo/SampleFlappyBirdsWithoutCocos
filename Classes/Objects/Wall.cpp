#include "cocos2d.h"
#include "Object.h"
#include "DinamicObject.h"
#include "Wall.h"

//�������� ��� �����
cocos2d::PhysicsMaterial materiar_wall(1.0f, 0.0f, 0.8f);//���������, ���������������, �������������(����������)
extern float WORLD_SCALE;



Wall::Wall(cocos2d::Sprite *obj, cocos2d::Size proportion) : DinamicObject(obj)
{
	
	DinamicObject::createCollisionBox(proportion * WORLD_SCALE, materiar_wall);//60- ��� � �������� �������� ��� ��������
	sprite->setScale(sprite->getScale() );

	setEnableCollisionEvent(true);//�������� ������ ��������

	//������� ���������� ���������
	sprite->getPhysicsBody()->setAngularVelocityLimit(0);//�� ���������
	sprite->getPhysicsBody()->setDynamic(false);
	sprite->getPhysicsBody()->setGravityEnable(false);
	setLinearDamping(0);
	setMass(0.01f);
	
	
}

void Wall::setEnable(bool x)
{
	sprite->getPhysicsBody()->setDynamic(x);
}