#include "raylib.h"
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include "background.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"

float delta;
int screen_width = 1280;
int screen_height = 720;
RenderTexture2D target;
void process();

int main(void)
{
	// Setup
	InitWindow(1280, 720, "Yet Another Pong Clone");
	InitAudioDevice();
	float delta = 0;
	(void)delta;
	create_background_texture();
	setup_player();
	setup_enemy();
	setup_ball();
	target = LoadRenderTexture(1280,720);

	// Main loop
	#if defined(PLATFORM_WEB)
    	emscripten_set_main_loop(process, 0, 1);
	#else
	    SetTargetFPS(60);
	    while (!WindowShouldClose())
	    {

    		    process();
	    }
	#endif

	CloseWindow();

    return 0;
}

void process()
{
	delta = GetFrameTime();

	BeginTextureMode(target);
	ClearBackground(WHITE);
	DrawTexture(background.texture, 0, 0, WHITE);
	process_player();
	process_enemy();
	process_ball();
	EndTextureMode();

	if (IsWindowResized())
	{
		screen_width = GetScreenWidth();
		screen_height = GetScreenHeight();
	}

	BeginDrawing();
	DrawTexturePro(target.texture, (Rectangle){0, 0, 1280, -720}, (Rectangle){0, 0, screen_width, screen_height}, (Vector2){0,0}, 0.0f, WHITE);
	EndDrawing();
}
