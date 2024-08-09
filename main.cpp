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

//��ʼ����ͼƬ
IMAGE img_opening_background;
IMAGE img_startmenu;
IMAGE img_select_level;
IMAGE img_lose;
IMAGE img_win;

//��ʼ��ťͼƬ
IMAGE img_startbutton_idle;
IMAGE img_startbutton_hover;
IMAGE img_startbutton_clicked;

//��ݲ˵�ͼƬ
IMAGE img_menu;
IMAGE img_dark;

//�ؿ�ͼƬ
IMAGE img_level_1_1;
//IMAGE img_level_1_1_idle;
//IMAGE img_level_1_1_hover;
//IMAGE img_level_1_1_clicked;

//��ƺͼƬ
IMAGE img_game_background;

//С�Ƴ�����ݻ���ͼƬ
IMAGE img_lawn_mower;

//������ͼƬ
IMAGE img_progress_bar_1flag;

//�㶹�ӵ�ͼƬ
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

void LoadImages() {
	//��������
	AddFontResourceEx("PixCon.ttf", FR_PRIVATE, NULL);
	AddFontResourceEx("IPix.ttf", FR_PRIVATE, NULL);

	//���ر���
	loadimage(&img_startmenu, "pic\\background\\start_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //��ʼ�˵�
	loadimage(&img_game_background, "pic\\background\\game_background.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //��Ϸ����ͼ
	loadimage(&img_select_level, "pic\\background\\select_level.png", WINDOW_WIDTH, WINDOW_HEIGHT); //ѡ��ؿ�����ͼ
	loadimage(&img_lose, "pic\\background\\lose.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //ʧ�ܽ���ͼ
	loadimage(&img_win, "pic\\background\\win.png", WINDOW_WIDTH, WINDOW_HEIGHT);  //�ɹ�����ͼ
	loadimage(&img_menu, "pic\\background\\menu.png", WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3);  //��ݲ˵�ͼƬ
	loadimage(&img_dark, "pic\\background\\dark_layer.png", WINDOW_WIDTH, WINDOW_HEIGHT);

	//���ؿ�ʼ��ť
	loadimage(&img_startbutton_idle, "pic\\button\\startbutton\\0.png", START_BUTTON_WIDTH, START_BUTTON_HEIGHT);
	loadimage(&img_startbutton_hover, "pic\\button\\startbutton\\1.png", START_BUTTON_WIDTH, START_BUTTON_HEIGHT);
	loadimage(&img_startbutton_clicked, "pic\\button\\startbutton\\2.png", START_BUTTON_WIDTH, START_BUTTON_HEIGHT);

	//���عؿ�ͼƬ
	loadimage(&img_level_1_1, "pic\\level\\1-1.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);
	//loadimage(&img_level_1_1_idle, "pic\\level\\1-1\\0.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);
	//loadimage(&img_level_1_1_hover, "pic\\level\\1-1\\1.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);
	//loadimage(&img_level_1_1_clicked, "pic\\level\\1-1\\2.png", LEVEL_CARD_SIZE, LEVEL_CARD_SIZE);

	//����С�Ƴ�ͼƬ
	loadimage(&img_lawn_mower, "pic\\other\\lawn_mower.png", LAWN_MOWER_SIZE, LAWN_MOWER_SIZE);

	//���ؽ�����ͼƬ
	loadimage(&img_progress_bar_1flag, "pic\\progressbar\\1flag.png", PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT);

	//�����ӵ�ͼƬ
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