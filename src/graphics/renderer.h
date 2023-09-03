#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>

#include "entities/entity.h"

void renderer_clear(Color color);
void renderer_render_entity(Entity *entity);
void renderer_render_entity_rot(Entity *entity, Vector2 origin, float rotation);

#endif // RENDERER_H
