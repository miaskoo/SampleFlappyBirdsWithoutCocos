#pragma once

//����� ���� ��� ��������
//������� �������� clear � ���������� pushback
//������������ ���������� �������� �� ����� 256
class Pull
{
private:
	
	size_t count;
	std::array<LogObject*, 256> pull;
	std::unordered_map<cocos2d::PhysicsShape*, LogObject*> table;
public:

	Pull();
	~Pull();
	void pushBack(LogObject *obj);
	void clear();
	size_t size();
	static Pull* getPull();
	LogObject *getIndex(int n);
	LogObject* find(cocos2d::PhysicsShape* shape);
								//void destroyObj(Object* obj);//o(n)
								//void destroyObj(int obj);//o(n);

};
