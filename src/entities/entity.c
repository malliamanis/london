#include <stdlib.h>

#include "london.h"
#include "entities/entity.h"
#include "graphics/renderer.h"

Entity *entity_create(EntityType type, float x, float y, float width, float height)
{
	Entity *e = calloc(1, sizeof(Entity));

	e->type = type;
	e->body.x = x;
	e->body.y = y;
	e->body.width = width;
	e->body.height = height;
	e->color = WHITE;

	return e;
}

void entity_tick(Entity *e)
{
	if (e->body.y + e->body.height >= HEIGHT) {
		e->vel.y = 0.0f;
		e->acc.y = 0.0f;
		e->body.y = HEIGHT - e->body.height;
	}
	else
		e->acc.y = G;

	e->vel.x += e->acc.x * DELTA_TIME;
	e->vel.y += e->acc.y * DELTA_TIME;

	e->body.x += e->vel.x * DELTA_TIME;
	e->body.y += e->vel.y * DELTA_TIME;
}

void entity_render(Entity *e)
{
	renderer_render_entity(e);
}

void entity_destroy(Entity *e)
{
	free(e);
}
