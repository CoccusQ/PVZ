#include <cstdlib>
#include <ctime>
#include "MenuScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "SunlightLayer.h"
#include "BulletLayer.h"
#include "PlantsLayer.h"
#include "ZombiesLayer.h"
#include "CardSlot.h"
#include "Button.h"
#include "Atlas.h"

int mouse_x, mouse_y;

CardSlot card_slot;
PlantsLayer plants_layer;
ZombiesLayer zombies_layer;
SunlightLayer sunlight_layer;
BulletLayer bullet_layer;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;

SceneManager scene_manager;

IMAGE img_startmenu;
IMAGE img_game_background;
IMAGE img_bullet_pea;

//豌豆射手卡片
IMAGE img_card_peashooter_cooling;
IMAGE img_card_peashooter_prepared;
IMAGE img_card_peashooter_plant;

//向日葵卡片
IMAGE img_card_sunflower_cooling;
IMAGE img_card_sunflower_prepared;
IMAGE img_card_sunflower_plant;

//豌豆子弹图集
Atlas atlas_pea;

//豌豆射手图集
Atlas atlas_peashooter_idle;
Atlas atlas_peashooter_shoot;

//向日葵图集
Atlas atlas_sunflower_idle;
Atlas atlas_sunflower_produce;

//僵尸图集
Atlas atlas_zombies_walk;
Atlas atlas_zombies_attack;
Atlas atlas_zombies_die;

//开始按钮：从开始菜单进入游戏界面
StartButton start_btn("pic\\button\\startbutton", START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT);

void LoadImages() {
	//加载背景
	loadimage(&img_startmenu, "pic\\background\\start_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //开始菜单
	loadimage(&img_game_background, "pic\\background\\game_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //游戏背景图

	//加载子弹
	loadimage(&img_bullet_pea, "pic\\bullet\\pea\\pea.png", PEA_SIZE, PEA_SIZE);  //豌豆子弹

	//加载豌豆射手卡片
	loadimage(&img_card_peashooter_prepared, "pic\\card\\peashooter1.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_peashooter_cooling, "pic\\card\\peashooter2.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_peashooter_plant, "pic\\plants\\peashooter\\idle\\0.png", PLANT_SIZE, PLANT_SIZE);

	//加载向日葵卡片
	loadimage(&img_card_sunflower_prepared, "pic\\card\\sunflower1.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_sunflower_cooling, "pic\\card\\sunflower2.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_sunflower_plant, "pic\\plants\\sunflower\\idle\\0.png", PLANT_SIZE, PLANT_SIZE);

	//加载豌豆子弹图集
	atlas_pea.load("pic\\bullet\\pea", PEA_SIZE, 3);

	//加载豌豆射手图集
	atlas_peashooter_idle.load("pic\\plants\\peashooter\\idle", PLANT_SIZE, 3);
	atlas_peashooter_shoot.load("pic\\plants\\peashooter\\shoot", PLANT_SIZE, 3);

	//加载向日葵图集
	atlas_sunflower_idle.load("pic\\plants\\sunflower\\idle", PLANT_SIZE, 3);
	atlas_sunflower_produce.load("pic\\plants\\sunflower\\produce", PLANT_SIZE, 3);

	//加载僵尸图集
	atlas_zombies_walk.load("pic\\zombies\\walk", ZOMBIE_SIZE, 5);
	atlas_zombies_attack.load("pic\\zombies\\attack", ZOMBIE_SIZE, 5);
	atlas_zombies_die.load("pic\\zombies\\die", ZOMBIE_SIZE, 5);

}

int main() {
	ExMessage msg;
	srand(time(0));
	LoadImages();
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	BeginBatchDraw();
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	scene_manager.set_current_scene(menu_scene);
	card_slot.ChooseCard();
	while (1) {
		DWORD start_time = GetTickCount();

		if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
			mouse_x = msg.x;
			mouse_y = msg.y;

			scene_manager.on_input(msg);

		}
		scene_manager.on_update(TIME_INTERVAL);
		cleardevice();

		scene_manager.on_draw();

		FlushBatchDraw();
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < TIME_INTERVAL) {
			Sleep(TIME_INTERVAL - delta_time);
		}
	}
	EndBatchDraw();
	closegraph();
	return 0;
}