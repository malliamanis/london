#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "entities/entity.h"
#include "london.h"
#include "entities/enemy.h"
#include "entities/bullet.h"

#define SPEED ((float)(5.0f) * METER)

Enemy *enemy_create(Entity *entity, Player *player, List *bullets)
{
	Enemy *e = malloc(sizeof(Enemy));

	e->entity = entity;
	e->entity->color = RED;
	if (GetRandomValue(0, 1) == 0)
		e->entity->vel.x = SPEED;
	else
	 	e->entity->vel.x = -SPEED;

	e->player = player;
	e->inside_player = false;

	e->bullets = bullets;

	e->in_air = true;
	e->delete = false;

	return e;
}

void enemy_tick(Enemy *e)
{
	if (e->entity->body.y + e->entity->body.height >= HEIGHT - (SPEED / METER)) {
		e->in_air = false;

		e->entity->vel.y = 0.0f;
		e->entity->acc.y = 0.0f;
		e->entity->body.y = HEIGHT - e->entity->body.height;
	}
	else
		e->entity->acc.y = G;

	if (e->entity->body.x < 0 || e->entity->body.x + e->entity->body.width > WIDTH)
		e->entity->vel.x *= -1;

	if (!e->in_air && GetRandomValue(0, 50) == 1) {
		e->in_air = true;

		e->entity->vel.y -= SPEED * 1.5f;
	}

	if (CheckCollisionRecs(e->entity->body, e->player->entity->body)) {
		if (!e->inside_player) {
			e->inside_player = true;
			if (e->player->life != 0)
				--e->player->life;
		}
	}
	else
	 	e->inside_player = false;

	for (Node *temp = e->bullets->head; temp != NULL; temp = temp->next) {
		Bullet *bullet = temp->data;
		if (CheckCollisionRecs(e->entity->body, bullet->entity->body)) {
			++e->player->score;

			e->delete = true;
			bullet->delete = true;
		}
	}

	e->entity->vel.x += e->entity->acc.x * DELTA_TIME;
	e->entity->vel.y += e->entity->acc.y * DELTA_TIME;

	e->entity->body.x += e->entity->vel.x * DELTA_TIME;
	e->entity->body.y += e->entity->vel.y * DELTA_TIME;
}

void enemy_render(Enemy *e)
{
	entity_render(e->entity);
}

void enemy_destroy(Enemy *e)
{
	free(e->entity);
	free(e);
}
