#ifndef GUN_H
#define GUN_H

#include "util/list.h"
#include "entities/entity.h"
#include "entities/player.h"

typedef struct {
	Entity *entity;
	List *bullets;

	Player *player;
} Gun;

Gun *gun_create(Entity *entity, Player *player);

void gun_update(Gun *gun);
void gun_tick(Gun *gun);
void gun_render(Gun *gun);

void gun_destroy(Gun *gun);

#endif
