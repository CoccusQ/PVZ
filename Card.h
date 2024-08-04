#pragma once
#include <string>
#include "Object.h"
#include "SunlightLayer.h"
#include "PlantsLayer.h"

extern SunlightLayer sunlight_layer;
extern PlantsLayer plants_layer;

//�㶹���ֿ�Ƭ
extern IMAGE img_card_peashooter_cooling;
extern IMAGE img_card_peashooter_prepared;
extern IMAGE img_card_peashooter_plant;

//���տ���Ƭ
extern IMAGE img_card_sunflower_cooling;
extern IMAGE img_card_sunflower_prepared;
extern IMAGE img_card_sunflower_plant;

class Card :public Object {
public:
	Card(const int id, int cost, int cd, int x, int y, int width = CARD_WIDTH, int height = CARD_HEIGHT)
		:id(id), cost(cost), time_cd(cd), Object(x, y, width, height) {
		//��ʼ��ͼƬ
		switch (id) {

		//�㶹����
		case PEASHOOTER_ID:
			img_prepared = &img_card_peashooter_prepared;
			img_cooling = &img_card_peashooter_cooling;
			img_plant = &img_card_peashooter_plant;
			break;

		//���տ�
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

	void on_input(const ExMessage& msg) {
		int row = 0, col = 0;
		int x = msg.x - PLANT_SIZE / 2, y = msg.y - PLANT_SIZE / 2;

		//����������ѡ�п�Ƭ
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
			//������������ֲ
			if (msg.message == WM_LBUTTONDOWN && is_in_range(msg)) {
				
				row = (msg.y - MAP_LEFT_Y) / BLOCK_SIZE;
				col = (msg.x - MAP_LEFT_X) / BLOCK_SIZE;
				x = (col) * BLOCK_SIZE + MAP_LEFT_X + (BLOCK_SIZE - PLANT_SIZE) / 2;
				y = (row) * BLOCK_SIZE + MAP_LEFT_Y + (BLOCK_SIZE - PLANT_SIZE) / 2;

				plants_layer.AddObject(id, row, col, x, y);
				sunlight_layer.total_sunlight -= cost;
				is_chosen = false;
				status = Status::COOLING;

			}
			//��������Ҽ�ȡ��ѡ��
			else if (msg.message == WM_RBUTTONDOWN) {

				is_chosen = false;
				status = Status::PREPARED;

			}

		}

	}

	//��Ƭ��ȴ
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
		}
		else {
			switch (status) {
			case Status::PREPARED:
				putimage_t(x, y, img_prepared);
				break;
			case Status::COOLING:
				putimage_t(x, y, img_cooling);
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