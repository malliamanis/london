#include <stdlib.h>

#include "entities/player.h"
#include "graphics/renderer.h"

Player *player_create(Entity *entity)
{
	Player *player = malloc(sizeof(Player));

	player->entity = entity;

	return player;
}

void player_tick(Player *player)
{

}

void player_render(Player *player)
{
	renderer_render_entity(player->entity);
}

void player_destroy(Player *player)
{
	free(player->entity);
	free(player);
}

