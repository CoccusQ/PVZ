#pragma once
#include "Animation.h"
#include "Object.h"

extern Atlas atlas_zombies_walk;
extern Atlas atlas_zombies_attack;
extern Atlas atlas_zombies_die;

class Zombie :public Object {
public:
	enum Status { WALK, ATTACK };

public:
	bool is_end = false;
	int row, col;
	int damage;
	Status status = Status::WALK;

public:
	Zombie(int hp, int damage, int row, int col, int x, int y)
		:zombie_hp(hp), row(row), col(col), damage(damage),
		walk(&atlas_zombies_walk, ZOMBIE_FRAME_INTERVAL),
		attack(&atlas_zombies_attack, ZOMBIE_FRAME_INTERVAL),
		die(&atlas_zombies_die, ZOMBIE_FRAME_INTERVAL),
		Object(x, y, ZOMBIE_SIZE, ZOMBIE_SIZE, 30) {
		attack_interval = ZOMBIE_FRAME_INTERVAL * 5;
	}

	void Move() {
		if (count % 5 == 0) {
			x -= ZOMBIES_SPEED;
		}
		count++;
	}

	void Attack(int delta_time) {
		timer += delta_time;
		if (timer >= attack_interval) {
			
			timer = 0;
		}
	}

	void DecreaseHP(int damage) {
		zombie_hp -= damage;
		if (zombie_hp <= 0) {
			is_end = true;
		}
	}

	void Draw(int delta_time) {
		switch (status) {
		case Status::WALK:
			Move();
			walk.Play(x, y, delta_time);
			break;
		case Status::ATTACK:
			attack.Play(x, y, delta_time);
			Attack(delta_time);
			break;
		default:
			break;
		}
	}

protected:
	Animation walk, attack, die;
	int timer = 0;
	int attack_interval;
	int zombie_hp;
	int count = 0;
};