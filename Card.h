#pragma once
#include <string>
#include "Object.h"
#include "SunlightLayer.h"

class Card :public Object {
public:
	Card(const int id, int cost, int cd, int x, int y, int width = CARD_WIDTH, int height = CARD_HEIGHT)
		:id(id), cost(cost), time_cd(cd), Object(x, y, width, height) {
		std::string name;
		switch (id) {
		case SUNFLOWER:
			name = "sunflower";
			break;
		case PEASHOOTER:
			name = "peashooter";
			break;
		}
		std::string path_1 = "pic\\card\\" + name + "1.png";
		std::string path_2 = "pic\\card\\" + name + "2.png";
		std::string path_plant = "pic\\plants\\" + name + "\\idle\\0.png";
		loadimage(&img_prepared, path_1.c_str(), width, height);
		loadimage(&img_cooling, path_2.c_str(), width, height);
		loadimage(&img_plant, path_plant.c_str(), PLANT_SIZE, PLANT_SIZE);
		rect = { x + 20, y + 20, x + width - 20, y + width - 20 };
	}

	void ProcessEvent(const ExMessage &msg, Game &game, SunlightLayer &sunlight_layer) {
		int row = 0, col = 0;
		int x = msg.x - PLANT_SIZE / 2, y = msg.y - PLANT_SIZE / 2;

		if (!is_sunlight_enough(sunlight_layer)) {
			lack_of_sunlight = true;
			return;
		}
		else {
			lack_of_sunlight = false;
		}

		if (is_chosen) {
			putimage_t(x, y, &img_plant);
			//Add Plant
			if (msg.message == WM_LBUTTONDOWN && is_in_range(msg)) {
				
				row = (msg.y - MAP_LEFT_Y) / BLOCK_SIZE;
				col = (msg.x - MAP_LEFT_X) / BLOCK_SIZE;
				x = (col) * BLOCK_SIZE + MAP_LEFT_X + (BLOCK_SIZE - PLANT_SIZE) / 2;
				y = (row) * BLOCK_SIZE + MAP_LEFT_Y + (BLOCK_SIZE - PLANT_SIZE) / 2;
				game.AddObject(id, row, col, x, y);
				sunlight_layer.total_sunlight -= cost;
				is_chosen = false;
				status = Status::COOLING;
			}
			else if (msg.message == WM_RBUTTONDOWN) {

				is_chosen = false;
				status = Status::PREPARED;

			}

		}

		if (is_click(msg.x, msg.y) && status == Status::PREPARED) {\
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (is_sunlight_enough(sunlight_layer)) {
					is_chosen = true;
				}
				break;
			default:
				break;
			}
		}
	}

	void ProcessEvent(int temp_x, int temp_y, SunlightLayer& sunlight_layer) {
		if (!is_sunlight_enough(sunlight_layer)) {
			lack_of_sunlight = true;
			return;
		}
		else {
			lack_of_sunlight = false;
		}

		int x = temp_x - PLANT_SIZE / 2, y = temp_y - PLANT_SIZE / 2;
		if (is_chosen) {
			putimage_t(x, y, &img_plant);
		}
	}

	void CoolDown(int delta_time) {
		if (status == Status::COOLING) {
			timer += delta_time;
			if (timer >= time_cd) {
				status = Status::PREPARED;
				timer = 0;
			}
		}
	}

	/*
	void Reminder() {
		setbkmode(TRANSPARENT);
		setfillcolor(RGB(245, 237, 174));
		settextcolor(BLACK);
		fillroundrect(rect.left, rect.top, rect.right, rect.bottom, 10, 10);
		settextstyle(20, 0, _T("Î¢ÈíÑÅºÚ"));
		drawtext("Ñô¹â²»×ã£¡", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	*/

	void Draw() {
		if (lack_of_sunlight) {
			putimage_t(x, y, &img_cooling);
		}
		else {
			switch (status) {
			case Status::PREPARED:
				putimage_t(x, y, &img_prepared);
				break;
			case Status::COOLING:
				putimage_t(x, y, &img_cooling);
				break;
			}
		}

		/*
		if (is_remind) {
			Reminder();
			timer_remind += TIME_INTERVAL;
			if (timer_remind >= 100) {
				is_remind = false;
			}
		}
		*/
	}

protected:
	enum Status { PREPARED, COOLING };

	bool is_in_range(const ExMessage& msg) {
		return msg.x > MAP_LEFT_X
			&& msg.x < MAP_RIGHT_X
			&& msg.y > MAP_LEFT_Y
			&& msg.y < MAP_RIGHT_Y;
	}

	bool is_sunlight_enough(SunlightLayer& sunlight_layer) {
		return sunlight_layer.total_sunlight >= cost;
	}

protected:
	int id;
	int time_cd;
	int cost;
	int timer = 0;
	int timer_remind = 0;
	bool is_chosen = false;
	bool lack_of_sunlight = false;
	IMAGE img_prepared, img_cooling, img_plant;
	Status status = Status::PREPARED;
	RECT rect;
};