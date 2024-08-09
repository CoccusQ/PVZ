#include <cstdlib>
#include <ctime>
#include "MenuScene.h"
#include "LevelScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "SunlightLayer.h"
#include "BulletLayer.h"
#include "PlantsLayer.h"
#include "ZombiesLayer.h"
#include "LawnMowerLayer.h"
#include "CardSlot.h"
#include "Button.h"
#include "Atlas.h"

int mouse_x, mouse_y;

CardSlot card_slot;
PlantsLayer plants_layer;
ZombiesLayer zombies_layer;
SunlightLayer sunlight_layer;
BulletLayer bullet_layer;
LawnMowerLayer lawn_mower_layer;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* level_scene = nullptr;

SceneManager scene_manager;

//开始界面图片
IMAGE img_opening_background;
IMAGE img_startmenu;
IMAGE img_select_level;
IMAGE img_lose;
IMAGE img_win;

//开始按钮图片
IMAGE img_startbutton_idle;
IMAGE img_startbutton_hover;
IMAGE img_startbutton_clicked;

//快捷菜单图片
IMAGE img_menu;
IMAGE img_dark;

//关卡图片
IMAGE img_level_1_1;
//IMAGE img_level_1_1_idle;
//IMAGE img_level_1_1_hover;
//IMAGE img_level_1_1_clicked;

//草坪图片
IMAGE img_game_background;

//小推车（割草机）图片
IMAGE img_lawn_mower;

//进度条图片
IMAGE img_progress_bar_1flag;

//豌豆子弹图片
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

void LoadImages() {
	//加载字体
	AddFontResourceEx("PixCon.ttf", FR_PRIVATE, NULL);
	AddFontResourceEx("IPix.ttf", FR_PRIVATE, NULL);

	//加载背景
	loadimage(&img_startmenu, "pic\\background\\start_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //开始菜单
	loadimage(&img_game_background, "pic\\background\\game_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //游戏背景图
	loadimage(&img_select_level, "pic\\background\\select_level.png", WINDOW_WIDTH, WINDOW_HEIGHT); //选择关卡背景图
	loadimage(&img_lose, "pic\\background\\lose.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //失败界面图
	loadimage(&img_win, "pic\\background\\win.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //成功背景图
	loadimage(&img_menu, "pic\\background\\menu.png", WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3);  //快捷菜单图片
	loadimage(&img_dark, "pic\\background\\dark_layer.png", WINDOW_WIDTH, WINDOW_HEIGHT);

	//加载开始按钮
	loadimage(&img_startbutton_idle, "pic\\button\\startbutton\\0.png", START_BUTTON_WIDTH, START_BUTTON_HEIGHT);
	loadimage(&img_startbutton_hover, "pic\\button\\startbutton\\1.png", START_BUTTON_WIDTH, START_BUTTON_HEIGHT);
	loadimage(&img_startbutton_clicked, "pic\\button\\startbutton\\2.png", START_BUTTON_WIDTH, START_BUTTON_HEIGHT);

	//加载关卡图片
	loadimage(&img_level_1_1, "pic\\level\\1-1.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);
	//loadimage(&img_level_1_1_idle, "pic\\level\\1-1\\0.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);
	//loadimage(&img_level_1_1_hover, "pic\\level\\1-1\\1.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);
	//loadimage(&img_level_1_1_clicked, "pic\\level\\1-1\\2.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);

	//加载小推车图片
	loadimage(&img_lawn_mower, "pic\\other\\lawn_mower.png", LAWN_MOWER_SIZE, LAWN_MOWER_SIZE);

	//加载进度条图片
	loadimage(&img_progress_bar_1flag, "pic\\progressbar\\1flag.png", PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT);

	//加载子弹图片
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
	atlas_zombies_die.load("pic\\zombies\\die", ZOMBIE_SIZE, 9);

}

int main() {
	loadimage(&img_opening_background, "pic\\background\\opening_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EX_NOCLOSE);
	putimage(0, 0, &img_opening_background);
	ExMessage msg;
	srand(time(0));
	LoadImages();
	BeginBatchDraw();
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	level_scene = new LevelScene();
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