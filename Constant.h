#pragma once

//-----------------------------------
//Game Init
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1200;
const int FRAME_NUM = 3;
const int FPS = 144;
const int TIME_INTERVAL = 1000 / FPS;


//-----------------------------------
//Map
const int MAP_LEFT_X = 524;
const int MAP_LEFT_Y = 124;
const int MAP_RIGHT_X = 1476;
const int MAP_RIGHT_Y = 1076;
const int BLOCK_SIZE = 119;
const int PROGRESS_BAR_WIDTH = 300;
const int PROGRESS_BAR_HEIGHT = 75;
const int PROGRESS_BAR_X = WINDOW_WIDTH - PROGRESS_BAR_WIDTH - 20;
const int PROGRESS_BAR_Y = WINDOW_HEIGHT - PROGRESS_BAR_HEIGHT - 10;


//-----------------------------------
//Button
const int START_BUTTON_WIDTH = 344;
const int START_BUTTON_HEIGHT = 100;
const int START_BUTTON_X = (WINDOW_WIDTH - START_BUTTON_WIDTH) / 2;
const int START_BUTTON_Y = WINDOW_HEIGHT * 3 / 4;


//-----------------------------------
//Card
const int CARD_WIDTH = 300;
const int CARD_HEIGHT = 150;


//-----------------------------------
//Cardslot
const int SLOT_LEFT = 13;
const int SLOT_TOP = 120;


//-----------------------------------
//Sunlight
const int SUNLIGHT_X = 60;
const int SUNLIGHT_Y = 60;
const int SUNLIGHT_RANGE = 20;
const int SUNLIGHT_INIT = 200;
const int SUNLIGHT_SIZE = 70;
const int SUNLIGHT_SPEED = 4;
const int SUNLIGHT_VALUE_NORM = 25;


//-----------------------------------
//Bullet
const int BULLET_SPEED = 5;

//Pea
const int PEA_SIZE = 30;
const int PEA_DAMAGE = 20;


//-----------------------------------
//Plants
const int PLANT_SIZE = 90;
const int PLANT_FRAME_INTERVAL = 144;

//Sunflower
const int SUNFLOWER = 0;
const int SUNFLOWER_COST = 50;
const int SUNFLOWER_HP = 300;
const int SUNFLOWER_CD = 750;

//Peashoter
const int PEASHOOTER = 1;
const int PEASHOOTER_COST = 100;
const int PEASHOOTER_HP = 300;
const int PEASHOOTER_CD = 750;


//-----------------------------------
//Zombies
const int ZOMBIE_FRAME_INTERVAL = 86;
const int ZOMBIE_EMERGE_INTERVAL = 720;
const int ZOMBIE_WAVE_INTERVAL = 5760;
const int ZOMBIE_SIZE = 120;
const int ZOMBIES_HP = 270;
const int ZOMBIES_DAMAGE = 1;
const int ZOMBIES_SPEED = 1;