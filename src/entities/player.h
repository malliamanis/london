#ifndef PLAYER_H
#define PLAYER_H

#include "entities/entity.h"

typedef struct {
	Entity *entity;
} Player;

Player *player_create(Entity *entity);

void player_tick(Player *player);
void player_render(Player *player);

void player_destroy(Player *player);

#endif

