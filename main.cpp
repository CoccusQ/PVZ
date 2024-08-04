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

//�㶹���ֿ�Ƭ
IMAGE img_card_peashooter_cooling;
IMAGE img_card_peashooter_prepared;
IMAGE img_card_peashooter_plant;

//���տ���Ƭ
IMAGE img_card_sunflower_cooling;
IMAGE img_card_sunflower_prepared;
IMAGE img_card_sunflower_plant;

//�㶹�ӵ�ͼ��
Atlas atlas_pea;

//�㶹����ͼ��
Atlas atlas_peashooter_idle;
Atlas atlas_peashooter_shoot;

//���տ�ͼ��
Atlas atlas_sunflower_idle;
Atlas atlas_sunflower_produce;

//��ʬͼ��
Atlas atlas_zombies_walk;
Atlas atlas_zombies_attack;
Atlas atlas_zombies_die;

//��ʼ��ť���ӿ�ʼ�˵�������Ϸ����
StartButton start_btn("pic\\button\\startbutton", START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT);

void LoadImages() {
	//���ر���
	loadimage(&img_startmenu, "pic\\background\\start_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //��ʼ�˵�
	loadimage(&img_game_background, "pic\\background\\game_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //��Ϸ����ͼ

	//�����ӵ�
	loadimage(&img_bullet_pea, "pic\\bullet\\pea\\pea.png", PEA_SIZE, PEA_SIZE);  //�㶹�ӵ�

	//�����㶹���ֿ�Ƭ
	loadimage(&img_card_peashooter_prepared, "pic\\card\\peashooter1.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_peashooter_cooling, "pic\\card\\peashooter2.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_peashooter_plant, "pic\\plants\\peashooter\\idle\\0.png", PLANT_SIZE, PLANT_SIZE);

	//�������տ���Ƭ
	loadimage(&img_card_sunflower_prepared, "pic\\card\\sunflower1.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_sunflower_cooling, "pic\\card\\sunflower2.png", CARD_WIDTH, CARD_HEIGHT);
	loadimage(&img_card_sunflower_plant, "pic\\plants\\sunflower\\idle\\0.png", PLANT_SIZE, PLANT_SIZE);

	//�����㶹�ӵ�ͼ��
	atlas_pea.load("pic\\bullet\\pea", PEA_SIZE, 3);

	//�����㶹����ͼ��
	atlas_peashooter_idle.load("pic\\plants\\peashooter\\idle", PLANT_SIZE, 3);
	atlas_peashooter_shoot.load("pic\\plants\\peashooter\\shoot", PLANT_SIZE, 3);

	//�������տ�ͼ��
	atlas_sunflower_idle.load("pic\\plants\\sunflower\\idle", PLANT_SIZE, 3);
	atlas_sunflower_produce.load("pic\\plants\\sunflower\\produce", PLANT_SIZE, 3);

	//���ؽ�ʬͼ��
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