#pragma once
#include "Button.h"
#include <iostream>

class Level : public Button {
public:
	bool is_chosen = false;
	int level_id;  //�ؿ����
	int flag_num;  //������
	int ratio;     //���ֱ���
	int interval;  //���ּ��

public:
	Level() {};

protected:
	void OnClick(bool& flag) {
		flag = true;
		is_chosen = true;
	}
	
};