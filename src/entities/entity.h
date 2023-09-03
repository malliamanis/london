#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include <stdint.h>
#include <stddef.h>

typedef enum {
	ENTITY_PLAYER,
	ENTITY_GUN,
	ENTITY_BULLET
} EntityType;

typedef struct {
	EntityType type;

	Rectangle body;
	Vector2 vel;
	Vector2 acc;
	Color color;
} Entity;

Entity *entity_create(EntityType type, float x, float y, float width, float height);

void entity_tick(Entity *entity);
void entity_render(Entity *entity);

void entity_destroy(Entity *entity);

#endif // ENTITY_H
