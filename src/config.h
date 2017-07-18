#pragma once
#define C_DELAY 10

static const unsigned WINDOW_WIDTH = 1024;
static const unsigned WINDOW_HEIGHT = 768;

static const unsigned GO_UP = 0;
static const unsigned GO_DOWN = 1;
static const unsigned GO_LEFT = 2;
static const unsigned GO_RIGHT = 3;

static const unsigned CELL_SIZE = 10;
static const unsigned CELL_WIDTH = WINDOW_WIDTH / CELL_SIZE;
static const unsigned CELL_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

static const unsigned START_X = CELL_WIDTH / 2;
static const unsigned START_Y = CELL_HEIGHT / 2;
static const unsigned START_LENGTH = 4;
