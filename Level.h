#pragma once
#include "Button.h"
#include <iostream>

class Level : public Button {
public:
	bool is_chosen = false;
	int level_id;  //关卡编号
	int flag_num;  //旗帜数
	int ratio;     //出怪倍率
	int interval;  //出怪间隔

public:
	Level() {};

protected:
	void OnClick(bool& flag) {
		flag = true;
		is_chosen = true;
	}
	
};