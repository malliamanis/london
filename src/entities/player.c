#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "london.h"
#include "entities/player.h"
#include "graphics/renderer.h"

#define METER ((float)(100.0f)) // 20px = 1 meter
#define DELTA_TIME ((double)(1.0 / 60.0))

#define G ((float)(9.81f)* METER)
#define SPEED ((float)(4.0f) * METER)

Player *player_create(Entity *entity)
{
	Player *p = malloc(sizeof(Player));

	p->entity = entity;

	p->jump = false;

	return p;
}

void player_tick(Player *p)
{
	if (p->entity->body.y + p->entity->body.height >= HEIGHT) {
		p->jump = false;
		p->entity->velocity.y = 0.0f;
		p->entity->acceleration.y = 0.0f;
		p->entity->body.y = HEIGHT - p->entity->body.height;
	}
	else
		p->entity->acceleration.y = G;

	if (IsKeyDown(KEY_SPACE) && !p->jump) {
		p->jump = true;
		p->entity->velocity.y -= SPEED;
	}

	if (IsKeyDown(KEY_A))
		p->entity->body.x -= SPEED * DELTA_TIME;
	if (IsKeyDown(KEY_D))
		p->entity->body.x += SPEED * DELTA_TIME;

	p->entity->velocity.x += p->entity->acceleration.x * DELTA_TIME;
	p->entity->velocity.y += p->entity->acceleration.y * DELTA_TIME;

	p->entity->body.x += p->entity->velocity.x * DELTA_TIME;
	p->entity->body.y += p->entity->velocity.y * DELTA_TIME;
}

void player_render(Player *p)
{
	renderer_render_entity(p->entity);
}

void player_destroy(Player *p)
{
	free(p->entity);
	free(p);
}

