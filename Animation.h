#pragma once
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>
#include "Transparent.h"
#include "Constant.h"
#include "Atlas.h"

class Animation {
public:
	bool is_finished = false;

public:
	Animation() {};
	Animation(Atlas* anim_atlas, int frame_interval) {
		interval = frame_interval;
		this->atlas = anim_atlas;
	}
	~Animation() {}

	void reset() {
		timer = 0;
		idx_frame = 0;
		is_finished = false;
	}

	void set_loop(bool flag) {
		is_loop = flag;
	}

	void set_atlas(Atlas* atlas) {
		this->atlas = atlas;
	}

	void set_interval(int frame_interval) {
		interval = frame_interval;
	}

	int get_frame_index() {
		return idx_frame;
	}

	void Play(int x, int y, int delta_time) {
		timer += delta_time;

		if (timer >= interval) {
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->frame_list.size()) {
				if (is_loop) {
					idx_frame = 0;
				}
				else {
					idx_frame = atlas->frame_list.size() - 1;
					is_finished = true;
				}
			}
		}
		//putimage_t(x, y, atlas->frame_list[idx_frame]);
	}

	void Draw(int x, int y) {
		putimage_t(x, y, atlas->frame_list[idx_frame]);
	}

private:
	int timer = 0;
	int idx_frame = 0;
	int interval;
	bool is_loop = true;
	Atlas* atlas;
};