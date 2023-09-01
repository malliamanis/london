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

void renderer_render_textured_entity(Entity *entity, Texture2D *texture)
{
	DrawTexturePro(*texture, (Rectangle) {0, 0, texture->width, texture->height}, entity->body, (Vector2) {0}, 0.0f, WHITE);
}
