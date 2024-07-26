#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "SunlightLayer.h"
#include "BulletLayer.h"
#include "ZombiesLayer.h"
#include "CardSlot.h"

Game game;
CardSlot card_slot;
SunlightLayer sunlight_layer;
BulletLayer bullet_layer;
ZombiesLayer zombies_layer;

int main() {
	srand(time(0));
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	ExMessage msg;
	int temp_x = 0, temp_y = 0;
	card_slot.ChooseCard();
	BeginBatchDraw();
	while (1) {
		DWORD start_time = GetTickCount();
		cleardevice();

		game.Update(zombies_layer);
		game.Draw(sunlight_layer, bullet_layer, zombies_layer);
		if (!game.running) break;

		zombies_layer.AddZombie(TIME_INTERVAL);
		zombies_layer.Update();
		zombies_layer.Draw();

		bullet_layer.Update(zombies_layer);
		bullet_layer.Draw();

		card_slot.CoolDown(TIME_INTERVAL);
		card_slot.Draw();
		
		sunlight_layer.Update();
		sunlight_layer.Draw();

		if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
			temp_x = msg.x;
			temp_y = msg.y;
			card_slot.ProcessEvent(msg, game, sunlight_layer);
		}
		else {
			card_slot.ProcessEvent(temp_x, temp_y, sunlight_layer);
		}

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