#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "london.h"
#include "entities/player.h"
#include "graphics/renderer.h"

#define SPEED ((float)(4.0f) * METER)

Player *player_create(Entity *entity)
{
	Player *p = malloc(sizeof(Player));

	p->entity = entity;
	p->in_air = true;

	return p;
}

void player_tick(Player *p)
{
	if (p->entity->body.y + p->entity->body.height >= HEIGHT) {
		p->in_air = false;

		p->entity->vel.y = 0.0f;
		p->entity->acc.y = 0.0f;
		p->entity->body.y = HEIGHT - p->entity->body.height;
	}
	else
		p->entity->acc.y = G;

	if (IsKeyDown(KEY_SPACE) && !p->in_air) {
		p->in_air = true;
		p->entity->vel.y -= SPEED * 1.25f;
	}

	if (IsKeyDown(KEY_A))
		p->entity->body.x -= SPEED * DELTA_TIME;
	if (IsKeyDown(KEY_D))
		p->entity->body.x += SPEED * DELTA_TIME;

	p->entity->vel.x += p->entity->acc.x * DELTA_TIME;
	p->entity->vel.y += p->entity->acc.y * DELTA_TIME;

	p->entity->body.x += p->entity->vel.x * DELTA_TIME;
	p->entity->body.y += p->entity->vel.y * DELTA_TIME;
}

void player_render(Player *p)
{
	entity_render(p->entity);
}

void player_destroy(Player *p)
{
	entity_destroy(p->entity);
	free(p);
}
