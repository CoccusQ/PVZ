#pragma once
#include <vector>
#include <string.h>
#include "Sunlight.h"

class SunlightLayer {
public:
	char map[16][16];
	std::vector<Sunlight*> sunlight_list;
	int total_sunlight = SUNLIGHT_INIT;
public:
	SunlightLayer() {
		memset(map, '-', sizeof(map));
	}

	void Update() {
		for (int i = 0; i < sunlight_list.size(); i++) {
			Sunlight* temp = sunlight_list[i];
			temp->Move();
			if (temp->is_end) {
				total_sunlight += temp->value;
				std::swap(sunlight_list[i], sunlight_list.back());
				sunlight_list.pop_back();
				delete temp;
				continue;
			}
		}
	}

	void Draw() {
		
		setbkmode(TRANSPARENT);
		setfillcolor(RGB(245, 237, 174));
		settextcolor(BLACK);
		fillroundrect(rect.left, rect.top, rect.right, rect.bottom, 10, 10);
		settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
		drawtext(std::to_string(total_sunlight).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		for (int i = 0; i < sunlight_list.size(); i++) {
			sunlight_list[i]->Draw();
		}
	}

private:
	RECT rect = { 124,20,304,100 };
};