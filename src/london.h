#ifndef LONDON_H
#define LONDON_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "graphics/window.h"
#include "entities/player.h"

typedef struct {
	Window *window;

	Player *player;
	List *entities;
} London;

void london_run(void);

#endif
