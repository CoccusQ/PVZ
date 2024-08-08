#pragma once
#include <string>
#include "Object.h"
#include "SunlightLayer.h"
#include "PlantsLayer.h"

extern SunlightLayer sunlight_layer;
extern PlantsLayer plants_layer;

//豌豆射手卡片
extern IMAGE img_card_peashooter_cooling;
extern IMAGE img_card_peashooter_prepared;
extern IMAGE img_card_peashooter_plant;

//向日葵卡片
extern IMAGE img_card_sunflower_cooling;
extern IMAGE img_card_sunflower_prepared;
extern IMAGE img_card_sunflower_plant;

class Card :public Object {
public:
	Card(const int id, int cost, int cd, int x, int y, int width = CARD_WIDTH, int height = CARD_HEIGHT)
		:id(id), cost(cost), time_cd(cd), Object(x, y, width, height) {
		//初始化图片
		switch (id) {

		//豌豆射手
		case PEASHOOTER_ID:
			img_prepared = &img_card_peashooter_prepared;
			img_cooling = &img_card_peashooter_cooling;
			img_plant = &img_card_peashooter_plant;
			break;

		//向日葵
		case SUNFLOWER_ID:
			img_prepared = &img_card_sunflower_prepared;
			img_cooling = &img_card_sunflower_cooling;
			img_plant = &img_card_sunflower_plant;
			break;

		}
		
	}

	void on_update() {
		if (!is_sunlight_enough(sunlight_layer)) {
			lack_of_sunlight = true;
			return;
		}
		else {
			lack_of_sunlight = false;
		}
	}

	//种植植物
	void on_input(const ExMessage& msg) {
		int row = 0, col = 0;
		int x = msg.x - PLANT_SIZE / 2, y = msg.y - PLANT_SIZE / 2;

		//按下鼠标左键选中卡片
		if (is_click(msg.x, msg.y) && status == Status::PREPARED) {
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (is_sunlight_enough(sunlight_layer)) {
					is_chosen = true;
				}
				break;
			}
		}

		if (is_chosen) {
			//按下鼠标左键种植
			if (msg.message == WM_LBUTTONDOWN && is_in_range(msg)) {
				
				row = (msg.y - MAP_LEFT_Y) / BLOCK_SIZE;
				col = (msg.x - MAP_LEFT_X) / BLOCK_SIZE;
				x = (col) * BLOCK_SIZE + MAP_LEFT_X + (BLOCK_SIZE - PLANT_SIZE) / 2;
				y = (row)*BLOCK_SIZE + MAP_LEFT_Y + (BLOCK_SIZE - PLANT_SIZE) / 2; //- BLOCK_SIZE / 8;

				if (plants_layer.map[row][col] == 0) {
					plants_layer.AddObject(id, row, col, x, y);
					plants_layer.map[row][col] = id;
					sunlight_layer.total_sunlight -= cost;
					is_chosen = false;
					status = Status::COOLING;
				}

			}
			//按下鼠标右键取消选择
			else if (msg.message == WM_RBUTTONDOWN) {

				is_chosen = false;
				status = Status::PREPARED;

			}

		}

	}

	//卡片冷却
	void CoolDown(int delta_time) {
		if (status == Status::COOLING) {
			timer += delta_time;
			if (timer >= time_cd) {
				status = Status::PREPARED;
				timer = 0;
			}
		}
	}

	void draw_if_chosen(int mouse_x, int mouse_y) {
		int xx = mouse_x - PLANT_SIZE / 2, yy = mouse_y - PLANT_SIZE / 2;
		if (is_chosen) {
			putimage_t(xx, yy, img_plant);
		}
	}

	void Draw() {
		if (lack_of_sunlight) {
			putimage_t(x, y, img_cooling);
			put_text();
		}
		else {
			switch (status) {
			case Status::PREPARED:
				putimage_t(x, y, img_prepared);
				put_text();
				break;
			case Status::COOLING:
				putimage_t(x, y, img_cooling);
				put_text();
				break;
			}
		}

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

	void put_text() {
		setbkmode(TRANSPARENT);
		//settextstyle(40, 0, _T("微软雅黑"));
		settextstyle(40, 0, _T("微软雅黑"), 0, 0, 700, false, false, false);
		RECT r = { x + width / 3,y + height * 9 / 19, x + width * 6 / 7,y + height };
		RECT r1 = { x + width / 3 - 2,y + height * 9 / 19 - 2, x + width * 6 / 7 - 2,y + height - 2 };
		settextcolor(LIGHTGRAY);
		drawtext(std::to_string(cost).c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextcolor(BLACK);
		drawtext(std::to_string(cost).c_str(), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

protected:
	int id;
	int time_cd;
	int cost;
	int timer = 0;
	int timer_remind = 0;
	bool is_chosen = false;
	bool lack_of_sunlight = false;
	IMAGE* img_prepared;
	IMAGE* img_cooling;
	IMAGE* img_plant;
	Status status = Status::PREPARED;
};