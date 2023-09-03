#include <raylib.h>

#include <stdlib.h>

#include "london.h"
#include "entities/bullet.h"
#include "entities/entity.h"

Bullet *bullet_create(Entity *entity)
{
	Bullet *b = malloc(sizeof(Bullet));

	b->entity = entity;
	b->delete = false;

	return b;
}

void bullet_tick(Bullet *b)
{
	if (b->entity->body.y + b->entity->body.height >= HEIGHT)
		b->entity->vel.y *= -1;

	if (b->entity->body.x + b->entity->body.width < 0 || b->entity->body.x > WIDTH || b->entity->body.y + b->entity->body.y < 0)
		b->delete = true;

	b->entity->body.x += b->entity->vel.x;
	b->entity->body.y += b->entity->vel.y;
}

void bullet_render(Bullet *b)
{
	entity_render(b->entity);
}

void bullet_destroy(Bullet *b)
{
	free(b->entity);
	free(b);
}
