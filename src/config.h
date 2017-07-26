#pragma once
#define C_DELAY 10

static const unsigned WINDOW_WIDTH = 1024;
static const unsigned WINDOW_HEIGHT = 768;

static const unsigned GO_UP = 0;
static const unsigned GO_DOWN = 1;
static const unsigned GO_LEFT = 2;
static const unsigned GO_RIGHT = 3;

static const unsigned FIRST_PLAYER_ID = 1;
static const unsigned SECOND_PLAYER_ID = 2;

static const unsigned CELL_SIZE = 10;
static const unsigned CELL_WIDTH = WINDOW_WIDTH / CELL_SIZE;
static const unsigned CELL_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

static const unsigned START_X = CELL_WIDTH / 2;
static const unsigned START_Y = CELL_HEIGHT / 2;
static const unsigned START_LENGTH = 4;

static const unsigned RENDERING_TIMEOUT = 5;

//Text messages
static const unsigned MSG_MAX_COUNT = 10;
static const char MSG_FONT[] = "FreeSans.ttf";
static const unsigned MSG_FONT_SIZE = 24;
static const unsigned MSG_GAME_START = 0;
static const unsigned MSG_GAME_OVER = 1;
static const unsigned MSG_FIRST_PLAYER_WIN = 2;
static const unsigned MSG_SECOND_PLAYER_WIN = 3;
static const unsigned MSG_GAME_DRAW = 4;


