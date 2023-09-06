#ifndef LONDON_H
#define LONDON_H

#include <raylib.h>

#include <stdint.h>
#include <stdbool.h>

#include "util/list.h"
#include "entities/gun.h"
#include "entities/player.h"
#include "graphics/window.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "London"

#define DELTA_TIME ((double)(1.0 / 60.0))

#define METER ((float)(100.0f)) // 100px = 1 meter
#define G ((float)(9.81f)* METER)

typedef struct {
	Window *window;

	Player *player;
	Gun *gun;
	List *enemies;
	uint32_t enemy_count;

	float spawn_timer;

	bool game_over;
} London;

void london_run(void);

#endif
