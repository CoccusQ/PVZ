#pragma once

class Timer {
public:
	int timer = 0;

public:
	void IncreaseTime(int delta_time) {
		timer += delta_time;
	}

	void ResetTime() {
		timer = 0;
	}
};