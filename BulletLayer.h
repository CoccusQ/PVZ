#pragma once
#include <vector>
#include <string.h>
#include "Bullet.h"

class BulletLayer {
public:
	std::vector<Bullet*> bullet_list;
public:
	void Update() {
		for (int i = 0; i < bullet_list.size(); i++) {
			Bullet* temp = bullet_list[i];
			temp->Update();
			if (temp->is_end) {
				std::swap(bullet_list[i], bullet_list.back());
				bullet_list.pop_back();
				delete temp;
				continue;
			}
		}
	}

	void Draw() {
		for (int i = 0; i < bullet_list.size(); i++) {
			bullet_list[i]->Draw();
		}
	}
};