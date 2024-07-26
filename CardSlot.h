#pragma once
#include "Card.h"
#include "Game.h"

class CardSlot {
public:
	std::vector<Card*> card_list;
	int left = SLOT_LEFT, top = SLOT_TOP;
	int cur_x = SLOT_LEFT, cur_y = SLOT_TOP;

public:
	~CardSlot() {
		for (int i = 0; i < card_list.size(); i++) {
			delete card_list[i];
		}
	}

	void ChooseCard() {
		Card* new_card = new Card(PEASHOOTER, PEASHOOTER_COST, PEASHOOTER_CD, cur_x, cur_y);
		card_list.push_back(new_card);
		cur_y += CARD_HEIGHT + 1;
		Card *new_card1 = new Card(SUNFLOWER, SUNFLOWER_COST, SUNFLOWER_CD, cur_x, cur_y);
		card_list.push_back(new_card1);
	}

	void Draw() {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->Draw();
		}
	}

	void CoolDown(int delta_time) {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->CoolDown(delta_time);
		}
	}

	void ProcessEvent(const ExMessage& msg, Game& game, SunlightLayer& sunlight_layer) {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->ProcessEvent(msg, game, sunlight_layer);
		}
	}

	void ProcessEvent(int temp_x, int temp_y, SunlightLayer& sunlight_layer) {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->ProcessEvent(temp_x, temp_y, sunlight_layer);
		}
	}
};