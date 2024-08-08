#pragma once
#include <string>
#include "Object.h"
#include "Transparent.h"

class Button :public Object {
public:
	Button() {};
	Button(int x, int y, int width, int height)
		:Object(x, y, width, height) {
		
	}

	void set_image(IMAGE* idle, IMAGE* hover, IMAGE* clicked) {
		this->img_idle = idle;
		this->img_hover = hover;
		this->img_clicked = clicked;
	}

	void ProcessEvent(const ExMessage& msg, bool& flag) {
		switch (msg.message) {
		case WM_MOUSEMOVE:
			if (status == Status::IDLE && is_click(msg.x, msg.y)) {
				status = Status::HOVER;
			}
			else if (status == Status::HOVER && !is_click(msg.x, msg.y)) {
				status = Status::IDLE;
			}
			break;
		case WM_LBUTTONDOWN:
			if (is_click(msg.x, msg.y)) {
				status = Status::CLICKED;
			}
			break;
		case WM_LBUTTONUP:
			if (status == Status::CLICKED) {
				OnClick(flag);
				status = Status::HOVER;
			}
		}
	}

	void Draw() {
		switch (status) {
		case Status::IDLE:
			putimage_t(x, y, img_idle);
			break;
		case Status::HOVER:
			putimage_t(x, y, img_hover);
			break;
		case Status::CLICKED:
			putimage_t(x, y, img_clicked);
			break;
		}
	}

protected:
	enum Status { IDLE, HOVER, CLICKED };

	virtual void OnClick(bool& flag) = 0;

protected:
	IMAGE* img_idle = nullptr;
	IMAGE* img_hover = nullptr;
	IMAGE* img_clicked = nullptr;
	Status status = Status::IDLE;
};

class StartButton :public Button {
public:
	StartButton() {};
	StartButton(int x, int y, int width, int height)
		:Button(x, y, width, height) {

	}

	void OnClick(bool& flag) {
		//flag: game.is_game_start
		flag = true;
	}
};