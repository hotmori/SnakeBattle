#pragma once
#define C_DELAY 10

const unsigned WINDOW_WIDTH = 1024;
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

static const char LOG_FILE_NAME[] = "log/SnakeBattle.log";

//Text messages
static const unsigned MSG_MAX_COUNT = 10;
static const char MSG_FONT[] = "FreeSans.ttf";
static const unsigned MSG_FONT_SIZE = 24;
static const unsigned MSG_GAME_START = 1;
static const unsigned MSG_GAME_OVER = 2;
static const unsigned MSG_FIRST_PLAYER_WIN = 3;
static const unsigned MSG_SECOND_PLAYER_WIN = 4;
static const unsigned MSG_GAME_DRAW = 5;

static const unsigned MSG_PLUS_SCORE_FIRST_PLAYER = 6;
static const unsigned MSG_MINUS_SCORE_FIRST_PLAYER = 7;
static const unsigned MSG_PLUS_SCORE_SECOND_PLAYER = 8;
static const unsigned MSG_MINUS_SCORE_SECOND_PLAYER = 9;

static const char MSG_GAME_START_TXT[] = "Game Started";
static const char MSG_PLUS_SCORE[] = "+1";
static const char MSG_MINUS_SCORE[] = "-1";
static const char MSG_FIRST_PLAYER_WIN_TXT[] = "First player win!";
static const char MSG_SECOND_PLAYER_WIN_TXT[] = "Second player win!";
static const char MSG_GAME_DRAW_TXT[] = "Everybody won!";
