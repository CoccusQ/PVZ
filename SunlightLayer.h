#pragma once
#include <vector>
#include <string.h>
#include "Sunlight.h"

class SunlightLayer {
public:
	std::vector<Sunlight*> sunlight_list;
	int total_sunlight = SUNLIGHT_INIT;
public:
	SunlightLayer() {};

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
		fillroundrect(rect.left, rect.top, rect.right, rect.bottom, 5, 5);
		settextstyle(45, 0, _T("Î¢ÈíÑÅºÚ"));
		drawtext(std::to_string(total_sunlight).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		for (int i = 0; i < sunlight_list.size(); i++) {
			sunlight_list[i]->Draw();
		}
	}

	void reset() {
		total_sunlight = SUNLIGHT_INIT;
		while (sunlight_list.size() > 0) {
			Sunlight* temp = sunlight_list[sunlight_list.size() - 1];
			sunlight_list.pop_back();
			delete temp;
		}
	}

private:
	RECT rect = { 93,15,228,75 };
};