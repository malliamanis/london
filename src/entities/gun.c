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

// macros for the coordinates of the middle of the player cause they are used a lot
#define PLAYER_CENTER_X (g->player->entity->body.x + g->player->entity->body.width / 2.0f)
#define PLAYER_CENTER_Y (g->player->entity->body.y + g->player->entity->body.height / 2.0f)

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
		// places the bullet at the middle of the player with the origin being the middle of the bullet rectangle
		Entity *bullet_entity = entity_create(ENTITY_BULLET, PLAYER_CENTER_X - BULLET_SIZE / 2.0f, PLAYER_CENTER_Y - BULLET_SIZE / 2.0f, BULLET_SIZE, BULLET_SIZE);

		Vector2 mouse_pos = GetMousePosition();

		// sets the velocity of the bullet as the normalised vector ranging from the center of the player and the mouse and then scales it to the desired speed
		bullet_entity->vel = math_vec2_norm((Vector2){mouse_pos.x - PLAYER_CENTER_X, mouse_pos.y - PLAYER_CENTER_Y});
		math_ptr_vec2_scale(&bullet_entity->vel, BULLET_SPEED);

		list_add(g->bullets, bullet_create(bullet_entity));
	}
}

void gun_tick(Gun *g)
{
	g->entity->body.x = PLAYER_CENTER_X;
	g->entity->body.y = PLAYER_CENTER_Y;

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
	float angle = fmod(atan2f(mouse_pos.y - PLAYER_CENTER_Y, mouse_pos.x - PLAYER_CENTER_X), 2.0f * PI); // I don't remember how I figured this out
	angle *= (180.0f / PI); // turns it from radians to degrees

	renderer_render_entity_rot(g->entity, (Vector2){0.0f, g->entity->body.height / 2.0f}, angle);
}

void gun_destroy(Gun *g)
{
	list_destroy(g->bullets);
	entity_destroy(g->entity);
	free(g);
}
