#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "entities/entity.h"
#include "london.h"
#include "graphics/renderer.h"

static London *init(void);

static void update(London *london);
static void tick(London *london);
static void render(London *london);

static void terminate(London *london);

static London *init(void)
{
	London *london = malloc(sizeof(London));

	london->window = window_init(WIDTH, HEIGHT, TITLE);

	london->player = player_create(entity_create(ENTITY_PLAYER, 0, 0, 50.0f, 50.0f));
//	london->entities = list_create();

	return london;
}

void london_run(void)
{
	London *london = init();

    const double delta_time = 1.0 / 60.0;

    double currentTime = GetTime();
	double newTime;
    double accumulator = 0.0;

    while (!window_should_close())
    {
		update(london);

        newTime = GetTime();

        accumulator += newTime - currentTime;
        currentTime = newTime;

        while (accumulator >= delta_time)
        {
            tick(london);
            accumulator -= delta_time;
        }

        render(london);
    }

	terminate(london);
}

static void update(London *london)
{
	window_update(london->window);
}

static void tick(London *london)
{
	player_tick(london->player);
}

static void render(London *london)
{
	BeginDrawing();
	ClearBackground(london->window->background);

	player_render(london->player);

	// for (Node *temp = london->entities->head; temp != NULL; temp = temp->next) {
	// 	renderer_render_entity(temp->data);
	// }

	EndDrawing();
}

static void terminate(London *london)
{
	window_destroy(london->window);

	player_destroy(london->player);
	// list_free(london->entities);

	free(london);
}
