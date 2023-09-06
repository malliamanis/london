#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>

#include "util/list.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/bullet.h"

typedef struct {
	Entity *entity;

	Player *player;
	bool inside_player;

	List *bullets;

	bool in_air;
	bool delete;
} Enemy;

Enemy *enemy_create(Entity *entity, Player *player, List *bullets);

void enemy_tick(Enemy *enemy);
void enemy_render(Enemy *enemy);

void enemy_destroy(Enemy *enemy);

#endif
