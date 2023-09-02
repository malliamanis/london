#ifndef LONDON_H
#define LONDON_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "graphics/window.h"
#include "entities/player.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "London"

typedef struct {
	Window *window;

	Player *player;
	List *entities;
} London;

void london_run(void);

#endif
