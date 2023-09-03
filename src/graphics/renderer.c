#include <raylib.h>

#include "graphics/renderer.h"

void renderer_clear(Color color)
{
	ClearBackground(color);
}

void renderer_render_entity(Entity *entity)
{
	DrawRectangleRec(entity->body, entity->color);
}

void renderer_render_entity_rot(Entity *entity, Vector2 origin, float rotation)
{
	DrawRectanglePro(entity->body, origin, rotation, entity->color);
}
