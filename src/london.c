#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#include "london.h"
#include "util/list.h"
#include "entities/enemy.h"
#include "entities/entity.h"
#include "graphics/renderer.h"

static London *init(void);

static void update(London *l);
static void tick(London *l);
static void render(London *l);

static void restart(London *l);
static void spawn_enemies(London *l);

static void terminate(London *l);

static London *init(void)
{
	London *l = malloc(sizeof(London));

	l->window = window_init(WIDTH, HEIGHT, TITLE);

	l->player = NULL;

	l->game_over = false;

	return l;
}

void london_run(void)
{
	London *l = init();
	restart(l);

	SetRandomSeed(time(NULL));

	const double delta_time = DELTA_TIME;

	double currentTime = GetTime();
	double newTime;
	double accumulator = 0.0;

	const double delta_time1 = GetMonitorRefreshRate(GetCurrentMonitor());
	printf("%lf\n", delta_time1);

	while (!window_should_close())
	{
		update(l);

		newTime = GetTime();

		accumulator += newTime - currentTime;
		currentTime = newTime;

		while (accumulator >= delta_time)
		{
			tick(l);
			accumulator -= delta_time;
		}

		render(l);
	}

	terminate(l);
}

static void update(London *l)
{
	if (l->game_over) {
		if (IsKeyPressed(KEY_SPACE)) {
			l->game_over = false;
			restart(l);
		}
	}
	else {
		window_update(l->window);

		gun_update(l->gun);
	}
}

static void tick(London *l)
{
	if (l->player->life == 0)
		l->game_over = true;

	if (l->game_over)
		return;

	player_tick(l->player);
	gun_tick(l->gun);

	if (l->enemies->head == NULL) {
		if (l->spawn_timer >= 1) {
			spawn_enemies(l);
			l->spawn_timer = 0;
		}
		else
			l->spawn_timer += DELTA_TIME;
	}
 
	for (Node *temp = l->enemies->head; temp != NULL; temp = temp->next) {
		enemy_tick(temp->data);

		if (((Enemy *)temp->data)->delete)
			list_mark_for_removal(l->enemies, temp);
	}
	list_remove_marked(l->enemies);
}

static void render(London *l)
{
	BeginDrawing();
	ClearBackground(l->window->background);

	if (l->game_over) {
		char score_str[50];
		sprintf(score_str, "SCORE: %u", l->player->score);
		DrawText(score_str, WIDTH / 2.0f - MeasureText(score_str, 50) / 2.0f, HEIGHT / 2.0f - 75.0f, 50, WHITE);

		const char *space = "PRESS SPACE TO RESTART";
		DrawText(space, WIDTH / 2.0f - MeasureText(space, 50) / 2.0f, HEIGHT / 2.0f - 25.0f, 50, WHITE);
	}
	else {
		player_render(l->player);
		gun_render(l->gun);

		for (Node *temp = l->enemies->head; temp != NULL; temp = temp->next)
			enemy_render(temp->data);

		char score_str[50];
		sprintf(score_str, "SCORE: %u", l->player->score);
		DrawText(score_str, 0, 0, 50, WHITE);

		char life_str[8];
		sprintf(life_str, "LIFE: %u", l->player->life);

		Color life_color;
		if (l->player->life == 3)
			life_color = GREEN;
		else if (l->player->life == 2)
			life_color = YELLOW;
		else if (l->player->life == 1)
			life_color = RED;

		DrawText(life_str, WIDTH - MeasureText(life_str, 50) - 5, 0, 50, life_color);
	}

	EndDrawing();
}

static void restart(London *l)
{
	if (l->player != NULL) {
		player_destroy(l->player);
		gun_destroy(l->gun);
		list_destroy(l->enemies);
	}

	l->enemies = list_create((destructor)enemy_destroy, sizeof(Enemy));
	l->player = player_create(entity_create(ENTITY_PLAYER, WIDTH / 2.0f - 25.0f, 0.0f, 50.0f, 50.0f));
	l->gun = gun_create(entity_create(ENTITY_GUN, 0, 0, 35.0f, 7.5f), l->player);

	l->enemy_count = 0;

	l->spawn_timer = 0.0f;
}

static void spawn_enemies(London *l)
{
	++l->enemy_count;

	for (int i = 0; i < l->enemy_count; ++i)
		list_add(l->enemies, enemy_create(entity_create(ENTITY_ENEMY, GetRandomValue(0, WIDTH - 50), 0, 50.0f, 50.0f), l->player, l->gun->bullets));
}

static void terminate(London *l)
{
	window_destroy(l->window);

	free(l);
}
