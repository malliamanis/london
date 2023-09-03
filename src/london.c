#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "entities/entity.h"
#include "london.h"
#include "graphics/renderer.h"

static London *init(void);

static void update(London *l);
static void tick(London *l);
static void render(London *l);

static void terminate(London *l);

static London *init(void)
{
	London *l = malloc(sizeof(London));

	l->window = window_init(WIDTH, HEIGHT, TITLE);

	l->player = player_create(entity_create(ENTITY_PLAYER, 0, 0, 50.0f, 50.0f));
	l->gun = gun_create(entity_create(ENTITY_GUN, 0, 0, 35.0f, 7.5f), l->player);

	return l;
}

void london_run(void)
{
	London *l = init();

    const double delta_time = DELTA_TIME;

    double currentTime = GetTime();
	double newTime;
    double accumulator = 0.0;

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
	window_update(l->window);

	gun_update(l->gun);
}

static void tick(London *l)
{
	player_tick(l->player);
	gun_tick(l->gun);
}

static void render(London *l)
{
	BeginDrawing();
	ClearBackground(l->window->background);

	player_render(l->player);
	gun_render(l->gun);

	EndDrawing();
}

static void terminate(London *l)
{
	window_destroy(l->window);

	player_destroy(l->player);
	gun_destroy(l->gun);

	free(l);
}
