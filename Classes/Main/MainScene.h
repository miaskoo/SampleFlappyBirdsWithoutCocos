#pragma once
#include "cocos2d.h"

//#define DRAW_COLLISION //Можно включить для отображения коллизий в режиме игры


class MainScene : public cocos2d::Layer
{
private:
		//////////////////////////UI VARIABLES////////////////////////
		cocos2d::Node* GameNode = nullptr;//слой игры
		cocos2d::Node* GameUINode = nullptr;//слой UI игры
		cocos2d::Node* PauseNode = nullptr;//слой паузы игры
		cocos2d::Node* MainUINode = nullptr;//слой главного меню
		cocos2d::Node* GameOverUINode = nullptr; //слой UI проигрыша игры

		cocos2d::Sprite* Black_Screen = nullptr;//Черный экран


		cocos2d::ui::Text* scoreInput = nullptr;//цифры текущего счета - объект интерфейса
		cocos2d::ui::Text* scoreMaxInput = nullptr;//цифры рекорда - объект интерфейса

		cocos2d::ui::Button* restartButton = nullptr;//кнопка рестарта
		cocos2d::ui::Button* mainMenuButton = nullptr;//кнопка меню

		cocos2d::ui::Button* mainMenuYesButton = nullptr;//кнопки игрового меню
		cocos2d::ui::Button* mainMenuNoButton = nullptr;

		cocos2d::ui::Button* mainGameOverYesButton = nullptr;//кнопки конца игры
		cocos2d::ui::Button* mainGameOverNoButton = nullptr;

		cocos2d::ui::Button* mainPlayGameButton = nullptr;//кнопка начать игру


		//////////////////////////VARIABLES////////////////////////
		cocos2d::EventListenerPhysicsContact* ListenerPhysicsContact = nullptr;//листер физических контактов
		
		const size_t count_wall = 10;//количество одновременно существующих труб(число должно быть кратно 2!)
		const int c_impulse = -3;//сила импульса для движения труб
		const int smeh_x = 700;//пред растояние для труб
		const int smeh_y_bot = -100;//расстояние по y для нижней трубы
		const int smeh_y_top = 700;//расстояние по y для верхней трубы
		const float time_black_screen = 0.5f;//время fade in fade out
		const cocos2d::Vec2 start_Pos_Bird = cocos2d::Vec2(400, 500);//стартовая позиция птицы
		
		int smeh_wall = 200;//расстояние между трубами
		size_t score = 0;//счет
		size_t max_score = 0;//лучший счет

		StaticObject* ground_world = nullptr;//пол мира
		Bird* cur_Bird = nullptr;//птица
		std::vector<Wall*> pull_wall;//пулл стен(труб)
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;



	bool initGameInstance();//иницилизирует бинарный файл интерфейсов csb сделанный в Cocos Studio
	void updateScore();//обновляет UI очков
	void initGame();//иницилизация игры(создает объекты птицы(также ее начальное положение), труб, стен мира и из коллизии и добавляет все созданные объекты в пул) 
	void initWallGame();//иницилизирует местоположение всех стен(труб) пула pull_wall (предворительно pull_wall должен быть иницилизирован в initGame)
	void beginGame();//старт игры(предворительно игровой режим должен быть иницилизирован в initGame и расставлены трубы с помощью initWallGame)
	void restartGame();//перезапуск игры(сбрасывает все скорости и возвращает все объекты в начальное положение, также сбрасывает очки)
	void pauseGame();//пауза
	void resumeGame();//конец паузы
	void returnMainMenu();//возврат в главное меню из игрового режима
	void saveProfile();//сохраняет Max скор
	void loadProfile();//загружает Max скор если файл профиля уже есть
	~MainScene();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);


};

