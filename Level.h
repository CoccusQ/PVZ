#pragma once
#include "Button.h"
#include "Object.h"
#include <string>

class Level : public Button {
public:
	bool is_chosen = false;
	std::string name;
	int level_id;  //¹Ø¿¨±àºÅ
	int flag_num;  //ÆìÖÄÊý
	int ratio;     //³ö¹Ö±¶ÂÊ
	int interval;  //³ö¹Ö¼ä¸ô

public:
	Level() {};
	Level(std::string name) :name(name) {};

	void Draw() {
		switch (status) {
		case Status::IDLE:
			putimage_t(x, y, img_idle);
			draw_text(BLACK);
			break;
		case Status::HOVER:
			putimage_t(x, y, img_idle);
			draw_text(RED);
			break;
		case Status::CLICKED:
			putimage_t(x, y, img_idle);
			draw_text(WHITE);
			break;
		}
	}

protected:
	void OnClick(bool& flag) {
		flag = true;
		is_chosen = true;
	}

	void draw_text(COLORREF color) {
		setbkmode(TRANSPARENT);
		settextstyle(40, 0, _T("Î¢ÈíÑÅºÚ"), 0, 0, 700, false, false, false);
		RECT r = { x + width / 8 + 2,y + height / 6 * 3,x + width / 8 * 7 + 2,y + height };
		RECT r1 = { x + width / 8 + 2 + 2,y + height / 6 * 3 + 2 + 2,x + width / 8 * 7 + 2,y + height + 2 };
		settextcolor(LIGHTGRAY);
		drawtext(name.c_str(), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextcolor(color);
		drawtext(name.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
};