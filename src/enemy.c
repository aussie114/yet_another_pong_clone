#include "raylib.h"
#include "enemy.h"
#include "ball.h"
Enemy enemy;

void setup_enemy(void)
{
	enemy.x = 1216;
	enemy.y = 296;
	enemy.w = 32;
	enemy.h = 128;
	enemy.acceleration = 3000.0f;
	enemy.deceleration = 3500.0f;
	enemy.speed = 7.5f;
	enemy.max_speed = 800.0f;
	enemy.score = 0;
	enemy.hitbox = (Rectangle){0, 0, 32, 128};
	enemy.render_texture = LoadRenderTexture(enemy.w, enemy.h);
	BeginTextureMode(enemy.render_texture);
	DrawRectangleRounded((Rectangle){0,0,32,128}, 0.5, 5, (Color){222, 93, 93,255});
	DrawRectangleRounded((Rectangle){4,4,24,120}, 0.5, 5, (Color){163, 60, 60,255});
	EndTextureMode();
	enemy.texture = enemy.render_texture.texture;
}

void process_enemy(void)
{
	DrawText(TextFormat("%02d", enemy.score), 671, 0, 80, (Color){245,245,245,127});
	if (ball.x > 1280 || ball.x < 426 || ball.direction.x < 0)
	{
		DrawTexture(enemy.texture, enemy.x, enemy.y, WHITE);
		return;
	}
	// Move up
	if (ball.y < enemy.y + 64)
	{
		enemy.y -= enemy.speed;
		if (enemy.y < 0) {enemy.y = 0;}
	}
	// Move down
	else if (ball.y > enemy.y + 64)
	{
		enemy.y += enemy.speed;
		if (enemy.y > 592) {enemy.y = 592;}
	}

	enemy.hitbox.x = enemy.x;
	enemy.hitbox.y = enemy.y;

	DrawTexture(enemy.texture, enemy.x, enemy.y, WHITE);
}
