#pragma once
#include <vector>
#include <string>
#include "graphics.h"

class Atlas {
public:
	std::vector<IMAGE*> frame_list;

public:
	Atlas() {};
	Atlas(std::string dir, int size, int num) {
		std::string path;

		for (int i = 0; i <= num - 1; i++) {

			path = dir + "\\" + std::to_string(i) + ".png";
			IMAGE* frame = new IMAGE();
			loadimage(frame, path.c_str(), size, size);
			frame_list.push_back(frame);

		}
	}

	void load(std::string dir, int size, int num) {
		std::string path;

		for (int i = 0; i <= num - 1; i++) {

			path = dir + "\\" + std::to_string(i) + ".png";
			IMAGE* frame = new IMAGE();
			loadimage(frame, path.c_str(), size, size);
			frame_list.push_back(frame);

		}
	}
	
	~Atlas() {
		for (int i = 0; i < frame_list.size(); i++) {
			delete frame_list[i];
		}
	}
	
};