#pragma once
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>
#include "Transparent.h"
#include "Constant.h"

class Animation {
public:
	Animation(std::string dir, int size, int num, int frame_interval) {
		interval = frame_interval;
		std::string path;
		for (int i = 0; i < num; i++) {
			path = dir + "\\" + std::to_string(i) + ".png";
			IMAGE* frame = new IMAGE();
			loadimage(frame, path.c_str(), size, size);
			frame_list.push_back(frame);
		}
	}
	~Animation() {
		for (int i = 0; i < frame_list.size(); i++) {
			delete frame_list[i];
		}
	}

	void Play(int x, int y, int delta_time) {
		timer += delta_time;
		if (timer >= interval) {
			idx_frame++;
			idx_frame %= frame_list.size();
			timer = 0;
		}
		putimage_t(x, y, frame_list[idx_frame]);
	}
private:
	int timer = 0;
	int idx_frame = 0;
	int interval;
	std::vector<IMAGE*> frame_list;
};