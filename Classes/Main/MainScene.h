#pragma once
#include "cocos2d.h"

//#define DRAW_COLLISION //����� �������� ��� ����������� �������� � ������ ����


class MainScene : public cocos2d::Layer
{
private:
		//////////////////////////UI VARIABLES////////////////////////
		cocos2d::Node* GameNode = nullptr;//���� ����
		cocos2d::Node* GameUINode = nullptr;//���� UI ����
		cocos2d::Node* PauseNode = nullptr;//���� ����� ����
		cocos2d::Node* MainUINode = nullptr;//���� �������� ����
		cocos2d::Node* GameOverUINode = nullptr; //���� UI ��������� ����

		cocos2d::Sprite* Black_Screen = nullptr;//������ �����


		cocos2d::ui::Text* scoreInput = nullptr;//����� �������� ����� - ������ ����������
		cocos2d::ui::Text* scoreMaxInput = nullptr;//����� ������� - ������ ����������

		cocos2d::ui::Button* restartButton = nullptr;//������ ��������
		cocos2d::ui::Button* mainMenuButton = nullptr;//������ ����

		cocos2d::ui::Button* mainMenuYesButton = nullptr;//������ �������� ����
		cocos2d::ui::Button* mainMenuNoButton = nullptr;

		cocos2d::ui::Button* mainGameOverYesButton = nullptr;//������ ����� ����
		cocos2d::ui::Button* mainGameOverNoButton = nullptr;

		cocos2d::ui::Button* mainPlayGameButton = nullptr;//������ ������ ����


		//////////////////////////VARIABLES////////////////////////
		cocos2d::EventListenerPhysicsContact* ListenerPhysicsContact = nullptr;//������ ���������� ���������
		
		const size_t count_wall = 10;//���������� ������������ ������������ ����(����� ������ ���� ������ 2!)
		const int c_impulse = -3;//���� �������� ��� �������� ����
		const int smeh_x = 700;//���� ��������� ��� ����
		const int smeh_y_bot = -100;//���������� �� y ��� ������ �����
		const int smeh_y_top = 700;//���������� �� y ��� ������� �����
		const float time_black_screen = 0.5f;//����� fade in fade out
		const cocos2d::Vec2 start_Pos_Bird = cocos2d::Vec2(400, 500);//��������� ������� �����
		
		int smeh_wall = 200;//���������� ����� �������
		size_t score = 0;//����
		size_t max_score = 0;//������ ����

		StaticObject* ground_world = nullptr;//��� ����
		Bird* cur_Bird = nullptr;//�����
		std::vector<Wall*> pull_wall;//���� ����(����)
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;



	bool initGameInstance();//������������� �������� ���� ����������� csb ��������� � Cocos Studio
	void updateScore();//��������� UI �����
	void initGame();//������������ ����(������� ������� �����(����� �� ��������� ���������), ����, ���� ���� � �� �������� � ��������� ��� ��������� ������� � ���) 
	void initWallGame();//������������� �������������� ���� ����(����) ���� pull_wall (�������������� pull_wall ������ ���� �������������� � initGame)
	void beginGame();//����� ����(�������������� ������� ����� ������ ���� �������������� � initGame � ����������� ����� � ������� initWallGame)
	void restartGame();//���������� ����(���������� ��� �������� � ���������� ��� ������� � ��������� ���������, ����� ���������� ����)
	void pauseGame();//�����
	void resumeGame();//����� �����
	void returnMainMenu();//������� � ������� ���� �� �������� ������
	void saveProfile();//��������� Max ����
	void loadProfile();//��������� Max ���� ���� ���� ������� ��� ����
	~MainScene();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);


};

