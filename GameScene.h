#pragma once
#include <iostream>
#include "Scene.h"
#include "PlantsLayer.h"
#include "ZombiesLayer.h"
#include "SunlightLayer.h"
#include "BulletLayer.h"
#include "CardSlot.h"

extern PlantsLayer plants_layer;
extern ZombiesLayer zombies_layer;
extern SunlightLayer sunlight_layer;
extern BulletLayer bullet_layer;
extern CardSlot card_slot;
extern IMAGE img_game_background;

class GameScene :public Scene {
public:
	
	void on_enter() {
		std::cout << "进入游戏局内场景\n";
	}

	void on_update(int delta_time) {
		plants_layer.Update(zombies_layer);
		zombies_layer.Update(delta_time);
		bullet_layer.Update();
		card_slot.Update(delta_time);
		sunlight_layer.Update();
	}

	void on_draw() {
		putimage(0, 0, &img_game_background);
		plants_layer.Draw(sunlight_layer, bullet_layer);
		zombies_layer.Draw();
		bullet_layer.Draw();
		card_slot.Draw();
		sunlight_layer.Draw();
		card_slot.draw_if_chosen();
	}

	void on_input(const ExMessage& msg) {
		card_slot.on_input(msg);
	}

	void on_exit() {
		std::cout << "退出游戏场景\n";
	}

private:
	
};