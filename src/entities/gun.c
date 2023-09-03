#include <raylib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "london.h"
#include "util/list.h"
#include "entities/gun.h"
#include "util/mathutil.h"
#include "entities/entity.h"
#include "entities/bullet.h"
#include "graphics/renderer.h"

#define BULLET_SPEED ((float)(1.0f) * METER)
#define BULLET_SIZE ((float)(5.0f))

#define PLAYER_OFFSET_X (g->player->entity->body.x + g->player->entity->body.width / 2.0f)
#define PLAYER_OFFSET_Y (g->player->entity->body.y + g->player->entity->body.width / 2.0f)

Gun *gun_create(Entity *entity, Player *player)
{
	Gun *g = malloc(sizeof(Gun));
	
	g->entity = entity;
	g->entity->color = BLACK;

	g->bullets = list_create((destructor)bullet_destroy, sizeof(Bullet));

	g->player = player;

	return g;
}

void gun_update(Gun *g)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Entity *bullet_entity = entity_create(ENTITY_BULLET, PLAYER_OFFSET_X - BULLET_SIZE, PLAYER_OFFSET_Y - BULLET_SIZE, BULLET_SIZE, BULLET_SIZE);

		Vector2 mouse_pos = GetMousePosition();
		bullet_entity->vel = math_vec2_scale(math_vec2_norm((Vector2){mouse_pos.x - PLAYER_OFFSET_X, mouse_pos.y - PLAYER_OFFSET_Y}), BULLET_SPEED);

		list_add(g->bullets, bullet_create(bullet_entity));
	}
}

void gun_tick(Gun *g)
{
	g->entity->body.x = g->player->entity->body.x + g->player->entity->body.width / 2.0f;
	g->entity->body.y = g->player->entity->body.y + g->player->entity->body.height / 2.0f;

	for (Node *temp = g->bullets->head; temp != NULL; temp = temp->next) {
		bullet_tick(temp->data);
		if (((Bullet *)temp->data)->delete)
			list_mark_for_removal(g->bullets, temp);
	}
	list_remove_marked(g->bullets);
}

void gun_render(Gun *g)
{
	for (Node *temp = g->bullets->head; temp != NULL; temp = temp->next)
		bullet_render(temp->data);

	Vector2 mouse_pos = GetMousePosition();
	float deg = fmod(atan2f(mouse_pos.y - PLAYER_OFFSET_Y, mouse_pos.x - PLAYER_OFFSET_X) - 2.0f * PI / 4.0f, 2.0f * PI) * (180.0f / PI) + 90.0f;

	renderer_render_entity_rot(g->entity, (Vector2){0.0f, g->entity->body.height / 2.0f}, deg);
}

void gun_destroy(Gun *g)
{
	list_destroy(g->bullets);
	entity_destroy(g->entity);
	free(g);
}
