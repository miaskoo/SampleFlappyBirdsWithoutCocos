#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include "cocos2d.h"
#include "Object.h"
#include "Pull.h"

//единственный объект пула
Pull instance;


Pull::Pull()
{
	this->count = 0;
	for (size_t n = 0; n < pull.size(); n++)
	{
		pull[n] = nullptr;
	}
}

Pull::~Pull()
{
	this->clear();
}

Pull* Pull::getPull()
{
	return &instance;
}
void Pull::clear()
{
	for (size_t n = 0; n < count; n++)
	{
		if (pull[n] != nullptr)
		{
			delete pull[n];
			pull[n] = nullptr;
		}
	}
	table.clear();
	count = 0;
}

void Pull::pushBack(LogObject *obj)
{
	if (count < pull.size())
	{
		pull[count] = obj;
		count++;
		auto sprite = obj->getSprite();
		if (sprite != nullptr)
		{
			if (sprite->getPhysicsBody() != nullptr)
			{
				if (sprite->getPhysicsBody()->getShapes().size() > 0)
				{
					table[sprite->getPhysicsBody()->getShape(0)] = obj;//для быстрого доступа
				}
			}
		}
		
	}
}


LogObject* Pull::find(cocos2d::PhysicsShape* shape)
{
	if (table.find(shape) != table.cend())
	{
		return table[shape];
	}
	return nullptr;
}

size_t Pull::size()
{
	return count;
}

LogObject *Pull::getIndex(int n)
{
	if (count > n)
	{
		return pull[n];
	}
	return nullptr;
}