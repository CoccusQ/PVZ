#pragma once
#include <vector>
#include "LawnMower.h"

class LawnMowerLayer {
public:
	std::vector<LawnMower*> lawn_mower_list;

public:
	void set_lawn_mower() {
		int x = MAP_LEFT_X - LAWN_MOWER_SIZE;
		for (int i = 0; i < 8; i++) {
			int y = MAP_LEFT_Y + BLOCK_SIZE - LAWN_MOWER_SIZE + i * BLOCK_SIZE;
			LawnMower* temp = new LawnMower(i, -1, x, y, LAWN_MOWER_SIZE);
			lawn_mower_list.push_back(temp);
		}
	}

	void Update() {
		for (int i = 0; i < lawn_mower_list.size(); i++) {
			LawnMower* temp = lawn_mower_list[i];
			temp->Update();
			if (temp->is_end) {
				std::swap(lawn_mower_list[i], lawn_mower_list.back());
				lawn_mower_list.pop_back();
				delete temp;
				continue;
			}
		}
	}

	void Draw() {
		for (int i = 0; i < lawn_mower_list.size(); i++) {
			lawn_mower_list[i]->Draw();
		}
	}

	void reset() {
		while (lawn_mower_list.size() > 0) {
			LawnMower* temp = lawn_mower_list[lawn_mower_list.size() - 1];
			lawn_mower_list.pop_back();
			delete temp;
		}
	}
};