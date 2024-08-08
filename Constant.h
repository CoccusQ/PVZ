#pragma once

//-----------------------------------
//Game Init
const int WINDOW_WIDTH = 800 * 1.5;
const int WINDOW_HEIGHT = 600 * 1.5;
const int FRAME_NUM = 3;
const int FPS = 144;
const int TIME_INTERVAL = 1000 / FPS;


//-----------------------------------
//Map
const int MAP_LEFT_X = 262 * 1.5;
const int MAP_LEFT_Y = 62 * 1.5;
const int MAP_RIGHT_X = 738 * 1.5;
const int MAP_RIGHT_Y = 538 * 1.5;
const int BLOCK_SIZE = 59 * 1.5;
const int PROGRESS_BAR_WIDTH = 140 * 1.5;
const int PROGRESS_BAR_HEIGHT = 35 * 1.5;
const int PROGRESS_BAR_X = (WINDOW_WIDTH - PROGRESS_BAR_WIDTH - 10 * 1.5);
const int PROGRESS_BAR_Y = (WINDOW_HEIGHT - PROGRESS_BAR_HEIGHT - 5 * 1.5);


//-----------------------------------
//Button
const int START_BUTTON_WIDTH = 172 * 1.5;
const int START_BUTTON_HEIGHT = 50 * 1.5;
const int START_BUTTON_X = (WINDOW_WIDTH - START_BUTTON_WIDTH) / 2;
const int START_BUTTON_Y = WINDOW_HEIGHT * 3 / 4;


//-----------------------------------
//Lawn Mower
const int LAWN_MOWER_SIZE = 45 * 1.5;
const int LAWN_MOWER_SPEED = 5;


//-----------------------------------
//Level
const int LEVEL_CARD_SIZE = 150;


//-----------------------------------
//Card
const int CARD_WIDTH = 83 * 1.5;
const int CARD_HEIGHT = 75 * 1.5;


//-----------------------------------
//Cardslot
const int SLOT_LEFT = 6 * 1.5;
const int SLOT_TOP = 60 * 1.5;


//-----------------------------------
//Sunlight
const int SUNLIGHT_X = 30 * 1.5;
const int SUNLIGHT_Y = 30 * 1.5;
const int SUNLIGHT_RANGE = 10 * 1.5;
const int SUNLIGHT_INIT = 200;
const int SUNLIGHT_SIZE = 35 * 1.5;
const int SUNLIGHT_SPEED = 2 * 1.5;
const int SUNLIGHT_VALUE_NORM = 25;


//-----------------------------------
//Bullet
const int BULLET_SPEED = 3 * 1.5;

//Pea
const int PEA_ID = 0;
const int PEA_SIZE = 15 * 1.5;
const int PEA_DAMAGE = 20;


//-----------------------------------
//Plants
const int PLANT_SIZE = 45 * 1.5;
const int PLANT_FRAME_INTERVAL = 144;

//Peashoter
const int PEASHOOTER_ID = 0;
const int PEASHOOTER_COST = 100;
const int PEASHOOTER_HP = 300;
const int PEASHOOTER_CD = 750;

//Sunflower
const int SUNFLOWER_ID = 1;
const int SUNFLOWER_COST = 50;
const int SUNFLOWER_HP = 300;
const int SUNFLOWER_CD = 750;


//-----------------------------------
//Zombies
const int ZOMBIE_FRAME_INTERVAL = 86;
const int ZOMBIE_EMERGE_INTERVAL = 720;
const int ZOMBIE_WAVE_INTERVAL = 5760;
const int ZOMBIE_SIZE = 60 * 1.5;
const int ZOMBIES_HP = 270;
const int ZOMBIES_DAMAGE = 1;
const int ZOMBIES_SPEED = 2;