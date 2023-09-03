#ifndef BULLET_H
#define BULLET_H

#include <stdbool.h>

#include "entities/entity.h"

typedef struct {
	Entity *entity;
	bool delete;
} Bullet;

Bullet *bullet_create(Entity *entity);

void bullet_tick(Bullet *bullet);
void bullet_render(Bullet *bullet);

void bullet_destroy(Bullet *bullet);

#endif
