#include <array>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"//чтобы использовать CSLoader 
#include "ui/CocosGUI.h"
#include "Classes/Objects/Object.h"
#include "Classes/Objects/StaticObject.h"
#include "Classes/Objects/DinamicObject.h"
#include "Classes/Objects/Birds.h"
#include "Classes/Objects/Wall.h"
#include "Classes/Objects/Pull.h"
#include "MainScene.h"


USING_NS_CC;


using namespace cocostudio::timeline;

Scene* main_scene = nullptr;//объект главной сцены
float WORLD_SCALE = 0.2f;//мировая размерность, использовал для быстрой надстройки 

Scene* MainScene::createScene()
{
	main_scene = Scene::createWithPhysics();//создали сценку с поддержкой физики
	main_scene->getPhysicsWorld()->setGravity(Vec2(0, -980));//гравитация мира

	
    auto layer = MainScene::create();

	main_scene->addChild(layer);

    return main_scene;
}

// иницилизация начальной сцены
bool MainScene::init()
{
	return initGameInstance();
}

void MainScene::returnMainMenu()
{
	resumeGame();
	GameNode->removeAllChildrenWithCleanup(true);
	main_scene->getPhysicsWorld()->removeAllBodies();
	pull_wall.clear();
	cur_Bird = nullptr;
	Pull::getPull()->clear();



	GameUINode->setVisible(false);
	GameNode->setVisible(false);

	MainUINode->setVisible(true);
	mainPlayGameButton->setEnabled(true);

#ifdef DRAW_COLLISION
	main_scene->getPhysicsWorld()->setDebugDrawMask(0x0000);//отрисовка коллайдеров
#endif
}

bool MainScene::initGameInstance()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//грузиться файл интерфейса Cocos Studio
	auto rootNode = CSLoader::createNode("GameScene.csb");
	this->addChild(rootNode);

	//Далее по аргументам которые были заданы для сцены, получаю кнопки-спрайты-слои всего интерфейса и создаю для них эвенты
	GameNode = rootNode->getChildByTag(10);
	GameUINode = rootNode->getChildByTag(9);
	PauseNode = rootNode->getChildByTag(18);
	MainUINode = rootNode->getChildByTag(16);
	GameOverUINode = rootNode->getChildByTag(27);
	

	scoreInput = static_cast<cocos2d::ui::Text*>(GameUINode->getChildByTag(8));
	scoreMaxInput = static_cast<cocos2d::ui::Text*>(GameUINode->getChildByTag(7));

	Black_Screen = static_cast<cocos2d::Sprite*>(rootNode->getChildByTag(13));


	restartButton = static_cast<cocos2d::ui::Button*>(GameUINode->getChildByTag(6));
	mainMenuButton = static_cast<cocos2d::ui::Button*>(GameUINode->getChildByTag(5));


	mainMenuYesButton = static_cast<cocos2d::ui::Button*>(PauseNode->getChildByTag(21));
	mainMenuNoButton = static_cast<cocos2d::ui::Button*>(PauseNode->getChildByTag(22));

	mainPlayGameButton = static_cast<cocos2d::ui::Button*>(MainUINode->getChildByTag(15));

	mainGameOverYesButton = static_cast<cocos2d::ui::Button*>(GameOverUINode->getChildByTag(31));
	mainGameOverNoButton = static_cast<cocos2d::ui::Button*>(GameOverUINode->getChildByTag(32));


	restartButton->setEnabled(false);
	mainMenuButton->setEnabled(false);//отключили - пока грузимся


	//создали все эвенты для всего UI игры
	restartButton->addClickEventListener([=](cocos2d::Ref*)
		{
			restartGame();
		});

	mainMenuButton->addClickEventListener([=](cocos2d::Ref*)
		{
			pauseGame();
			PauseNode->setVisible(true);
		});

	mainMenuYesButton->addClickEventListener([=](cocos2d::Ref*)
		{	
			PauseNode->setVisible(false);

			Black_Screen->runAction(cocos2d::Sequence::create(cocos2d::FadeIn::create(time_black_screen), cocos2d::CallFunc::create([=]()
				{
					returnMainMenu();
				}), cocos2d::FadeOut::create(time_black_screen), nullptr));

		});

	mainMenuNoButton->addClickEventListener([=](cocos2d::Ref*)
		{
			resumeGame();
			PauseNode->setVisible(false);
		});

	mainPlayGameButton->addClickEventListener([=](cocos2d::Ref*)
		{
#ifdef DRAW_COLLISION
			main_scene->getPhysicsWorld()->setDebugDrawMask(0xffff);//отрисовка коллайдеров
#endif
			mainPlayGameButton->setEnabled(false);
			Black_Screen->runAction(cocos2d::Sequence::create(cocos2d::FadeIn::create(time_black_screen), cocos2d::CallFunc::create([=]()
				{
					MainUINode->setVisible(false);
					initGame();
					beginGame();
				}), nullptr));
		});

	mainGameOverYesButton->addClickEventListener([=](cocos2d::Ref*)
		{
			GameOverUINode->setVisible(false);
			resumeGame();
			restartGame();
		});


	mainGameOverNoButton->addClickEventListener([=](cocos2d::Ref*)
		{
			GameOverUINode->setVisible(false);
			Black_Screen->runAction(cocos2d::Sequence::create(cocos2d::FadeIn::create(time_black_screen), cocos2d::CallFunc::create([=]()
				{
					returnMainMenu();
				}), cocos2d::FadeOut::create(time_black_screen), nullptr));
		});

	//Листнер коллизий
	ListenerPhysicsContact = cocos2d::EventListenerPhysicsContact::create();

	//описали эвенты происходящии при колизиях объектов сценки
	ListenerPhysicsContact->onContactBegin = [=](cocos2d::PhysicsContact & contact)//при возвращении эвентом true - эффекты коллизии работают по дефолту, при false - они игнорируются
	{
		//получили объекты
		auto shape1 = Pull::getPull()->find(contact.getShapeA());
		auto shape2 = Pull::getPull()->find(contact.getShapeB());


		if (shape2 != nullptr && shape1 != nullptr)
		{
			if (dynamic_cast<Bird*>(shape1) != nullptr)
			{
				if (dynamic_cast<Wall*>(shape2) != nullptr || ground_world == shape2)//если пересеклись с трубой или с полом мира
				{//евент проигрыша
					static_cast<Bird*>(shape1)->setDead(true);
					GameOverUINode->setVisible(true);
					pauseGame();
				}
				else//иначе это объекты скора
				{
					score += 10;
					updateScore();
				}
			}
			if (dynamic_cast<Wall*>(shape1) != nullptr)//если стена доехала до конца
			{
				if (dynamic_cast<Wall*>(shape2) != nullptr)
				{
					for (int n = 0; n < pull_wall.size(); n++)//и мы нашли ее в пуле то перемещаем в конец
					{
						if (shape1 == pull_wall[n])
						{
							shape1->getSprite()->runAction(cocos2d::CallFunc::create([=]()
								{
									shape1->setPosition(cocos2d::Vec2(smeh_wall * (count_wall - 1) + 50, shape1->getPosition().y));
								}));//поскольку перемещение должно произойти после эвентов коллизий, запустил action чтобы обработал перемешение
							break;
						}
						if (shape2 == pull_wall[n])
						{

							shape2->getSprite()->runAction(cocos2d::CallFunc::create([=]()
								{
									shape2->setPosition(cocos2d::Vec2(smeh_wall * (count_wall - 1) + 50, shape2->getPosition().y));
								}));
							break;
						}

					}
				}
			}

		}
		return false;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ListenerPhysicsContact, rootNode);

	loadProfile();//загрузили max score
	

	return true;
}




void MainScene::updateScore()//обновляет табло очков
{
	scoreInput->setString(std::to_string(score));
	if (max_score < score)
	{
		max_score = score;
	}
	scoreMaxInput->setString(std::to_string(max_score));
}

void MainScene::initWallGame()//задает положение стенам
{
	for (int n = 0; n < count_wall; n += 2)
	{
		int count = rand() % 400;
		int smeh_y = 800;

		pull_wall[n]->setPosition(cocos2d::Vec2(700 + smeh_wall * n, smeh_y_bot + count));
		pull_wall[n + 1]->setPosition(cocos2d::Vec2(700 + smeh_wall * n, count + smeh_y_top));
	}
}

void MainScene::beginGame()//функция запуска игры
{
	Black_Screen->runAction(cocos2d::Sequence::create(cocos2d::FadeOut::create(time_black_screen), cocos2d::CallFunc::create([=]()
		{
			for (size_t n = 0; n < count_wall; n += 2)
			{
				pull_wall[n]->addImpulse(cocos2d::Vec2(c_impulse, 0));
				pull_wall[n + 1]->addImpulse(cocos2d::Vec2(c_impulse, 0));
			}
			cur_Bird->setGravity(true);//включаем гравитацию
			restartButton->setEnabled(true);//кнопки снова доступны
			mainMenuButton->setEnabled(true);//выключаем кнопки
			cur_Bird->setDead(false);//оживляем
		}), nullptr));


}

void MainScene::restartGame()//функция повтора уровня
{
	//сбрасываем импульсы в ноль
	cur_Bird->addImpulse(cocos2d::Vec2(0, 0));

	for (int n = 0; n < count_wall; n += 2)
	{
		pull_wall[n]->addImpulse(cocos2d::Vec2(0, 0));
		pull_wall[n + 1]->addImpulse(cocos2d::Vec2(0, 0));
	}


	restartButton->setEnabled(false);//выключаем кнопки
	mainMenuButton->setEnabled(false);//выключаем кнопки
	cur_Bird->setGravity(false);//отключаем гравитацию
	cur_Bird->setDead(true);

	Black_Screen->runAction(cocos2d::Sequence::create(cocos2d::FadeIn::create(time_black_screen), cocos2d::CallFunc::create([=]()
		{

			//перемещаем в начальное положение объекты
			cur_Bird->setPosition(start_Pos_Bird);
			initWallGame();//восстанавливаем начальные положения стен

			//сбрасываем счет
			score = 0;
			updateScore();

			beginGame();
		}), nullptr));

}

void MainScene::pauseGame()
{
	main_scene->getPhysicsWorld()->setSpeed(0.0);
}

void MainScene::resumeGame()
{
	main_scene->getPhysicsWorld()->setSpeed(1.0);
}

void MainScene::initGame()
{
	GameNode->setVisible(true);
	GameUINode->setVisible(true);
	//сбросили счет
	score = 0;
	updateScore();


	//вручную создаю каждый объект сцены
	//используя реализованные классы
	LogObject* temp_obj = nullptr;

	//создали мировой пол
	cocos2d::Sprite* ground_world_sprite = cocos2d::Sprite::create();
	GameNode->addChild(ground_world_sprite);
	ground_world = new StaticObject(ground_world_sprite);
	static_cast<StaticObject*>(ground_world)->createCollisionBox(cocos2d::Vec2(2880, 300), false);
	ground_world->setEnableCollisionEvent(true);

	//сдена слева при соприкоснавении с которой будут телепортироваться трубы
	cocos2d::Sprite* wall_sprite = cocos2d::Sprite::create();
	GameNode->addChild(wall_sprite);
	wall_sprite->setPosition(-200, 0);
	temp_obj = new Wall(wall_sprite, cocos2d::Size(100, 10000));


	//птица
	cocos2d::Sprite* sprite_bird = cocos2d::Sprite::create();
	sprite_bird->setTexture("res/Birds/red_bird.png");
	sprite_bird->setLocalZOrder(99);//чтобы была поверх труб
	GameNode->addChild(sprite_bird);
	cur_Bird = new Bird(sprite_bird);
	cur_Bird->setPosition(start_Pos_Bird);
	cur_Bird->setDead(true);//мертва

	//создаем пул стен
	for (int n = 0; n < count_wall; n += 2)
	{
		int count = rand() % 400;


		cocos2d::Sprite* wall = cocos2d::Sprite::create();
		wall->setTexture("res/Walls/pipe_down.png");
		GameNode->addChild(wall);


		pull_wall.push_back(new Wall(wall, cocos2d::Size(600, 2800)));
		pull_wall[n]->setPosition(cocos2d::Vec2(smeh_x + smeh_wall * n, count + smeh_y_bot));
		pull_wall[n]->setEnable(true);


		////////////
		wall = cocos2d::Sprite::create();
		wall->setTexture("res/Walls/pipe_up.png");
		GameNode->addChild(wall);

		pull_wall.push_back(new Wall(wall, cocos2d::Size(600, 2800)));
		pull_wall[n + 1]->setPosition(cocos2d::Vec2(smeh_x + smeh_wall * n, count + smeh_y_top));
		pull_wall[n + 1]->setEnable(true);


		////////////
		auto wall_score = cocos2d::Sprite::create();
		wall_score->setPosition(100, -125);
		wall->addChild(wall_score);
		temp_obj = new StaticObject(wall_score);
		static_cast<StaticObject*>(temp_obj)->createCollisionBox(cocos2d::Vec2(25, 200), false);
		temp_obj->setEnableCollisionEvent(true);
	}
}


void MainScene::saveProfile()
{
	FILE* file = fopen("profile.dat", "wb");
	if (file != nullptr)
	{
		fwrite(&max_score, sizeof(max_score), 1, file);
		fclose(file);
	}
}

void MainScene::loadProfile()
{
	FILE* file = fopen("profile.dat", "rb");
	if (file != nullptr)
	{
		fread(&max_score, sizeof(max_score), 1, file);
		fclose(file);
	}
}

MainScene::~MainScene()
{
	saveProfile();
}