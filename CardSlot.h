#pragma once
#include "Card.h"

extern int mouse_x;
extern int mouse_y;

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
		Card* new_card1 = new Card(SUNFLOWER_ID, SUNFLOWER_COST, SUNFLOWER_CD, cur_x, cur_y);
		card_list.push_back(new_card1);
		cur_y += CARD_HEIGHT + 1;
		Card* new_card = new Card(PEASHOOTER_ID, PEASHOOTER_COST, PEASHOOTER_CD, cur_x, cur_y);
		card_list.push_back(new_card);
		
	}

	void draw_if_chosen() {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->draw_if_chosen(mouse_x, mouse_y);
		}
	}

	void Draw() {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->Draw();
		}
	}

	void Update(int delta_time) {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->on_update();
			card_list[i]->CoolDown(delta_time);
		}
	}

	void on_input(const ExMessage& msg) {
		for (int i = 0; i < card_list.size(); i++) {
			card_list[i]->on_input(msg);
		}
	}

};