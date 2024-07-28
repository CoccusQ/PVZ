#pragma once
#include <string>
#include "Object.h"
#include "Transparent.h"

class Button :public Object {
public:
	Button(std::string dir, int x, int y, int width, int height)
		:Object(x, y, width, height) {
		std::string path_idle = dir + "\\0.png";
		std::string path_hover = dir + "\\1.png";
		std::string path_clicked = dir + "\\2.png";
		loadimage(&img_idle, path_idle.c_str(), width, height);
		loadimage(&img_hover, path_hover.c_str(), width, height);
		loadimage(&img_clicked, path_clicked.c_str(), width, height);
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
			}
		}
	}

	void Draw() {
		switch (status) {
		case Status::IDLE:
			putimage_t(x, y, &img_idle);
			break;
		case Status::HOVER:
			putimage_t(x, y, &img_hover);
			break;
		case Status::CLICKED:
			putimage_t(x, y, &img_clicked);
			break;
		}
	}

protected:
	enum Status { IDLE, HOVER, CLICKED };

	virtual void OnClick(bool& flag) = 0;

protected:
	IMAGE img_idle, img_hover, img_clicked;
	Status status = Status::IDLE;
};

class StartButton :public Button {
public:
	StartButton(std::string dir, int x, int y, int width, int height)
		:Button(dir, x, y, width, height) {

	}

	void OnClick(bool& flag) {
		//flag: game.is_game_start
		flag = true;
	}
};