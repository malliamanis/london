#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdbool.h>

#include "util/list.h"
#include "entities/entity.h"

typedef struct {
	Entity *entity;
	bool in_air;

	uint32_t life;
	uint32_t score;
} Player;

Player *player_create(Entity *entity);

void player_tick(Player *player);
void player_render(Player *player);

void player_destroy(Player *player);

#endif
