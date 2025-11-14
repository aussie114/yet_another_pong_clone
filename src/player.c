#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "main.h"
Player player;

void setup_player(void)
{
	player.shape = (Rectangle){32,296,32,128};
	player.acceleration = 3000.0f;
	player.deceleration = 3500.0f;
	player.speed = 0.0f;
	player.max_speed = 800.0f;
	player.score = 0;
	player.render_texture = LoadRenderTexture(player.shape.width, player.shape.height);
	BeginTextureMode(player.render_texture);
	DrawRectangleRounded((Rectangle){0,0,32,128}, 0.5, 5, (Color){143,222, 93,255});
	DrawRectangleRounded((Rectangle){4,4,24,120}, 0.5, 5, (Color){ 60,163,112,255});
	EndTextureMode();
}

void process_player(void)
{

	// Move up and down
	if (IsKeyDown(KEY_W) || (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && (float)GetMouseY() < player.shape.y) )
	{
		player.speed -= player.acceleration * delta;
	}
	// Move down
	else if (IsKeyDown(KEY_S) || (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && (float)GetMouseY() > player.shape.y + 128) )
	{
		player.speed += player.acceleration * delta;
	}
	else
	{
		// Slow down while moving down
		if (player.speed > 0)
		{
			player.speed -= player.deceleration * delta;
			// Stop speed from passing 0 on deceleration
			if (player.speed < 0)
			{
				player.speed = 0;
			}
		}
		// Slow down while moving up
		else if (player.speed < 0)
		{
			player.speed += player.deceleration * delta;
			// Stop speed from passing 0 on deceleration
			if (player.speed > 0)
			{
				player.speed = 0;
			}
		}
	}

	// Clamp speed
	if (player.speed > player.max_speed)
	{
		player.speed = player.max_speed;
	}
	else if (player.speed < -player.max_speed)
	{
		player.speed = -player.max_speed;
	}

	// Update position
	player.shape.y += player.speed * delta;

	// keep in bounds
	if (player.shape.y < 0)
	{
		player.shape.y = 0;
		player.speed = 0;
	}
	else if (player.shape.y > 592)
	{
		player.shape.y = 592;
		player.speed = 0;
	}

	DrawTexture(player.render_texture.texture, player.shape.x, player.shape.y, WHITE);
	DrawText(TextFormat("%02d", player.score), 520, 0, 80, (Color){245,245,245,127});
}
