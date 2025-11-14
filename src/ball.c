#include "raylib.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "ball.h"
Ball ball;
Sound win_sound;
Sound loss_sound;
Sound bounce_sound;

void setup_ball(void)
{
	ball.x = 700;
	ball.y = 0;
	ball.w = 32;
	ball.h = 32;
	ball.direction.x = 1;
	ball.direction.y = -1;
	ball.speed = 500;
	ball.collision_resolved = 1;
	ball.hitbox = (Rectangle){0, 0, 32, 32};
	ball.render_texture = LoadRenderTexture(ball.w, ball.h);
	ball.state = 1;
	BeginTextureMode(ball.render_texture);
	DrawCircle(16, 16, 16, (Color){77, 166, 255, 255});
	DrawCircle(16, 16, 12, (Color){75,  91, 171, 255});
	EndTextureMode();
	ball.texture = ball.render_texture.texture;
	win_sound = LoadSound("data/win.wav");
	loss_sound = LoadSound("data/loss.wav");
	bounce_sound = LoadSound("data/bounce.wav");
}

void process_ball()
{
	if (ball.state == 1)
	{
		ball.x = player.shape.x + 32;
		ball.y = player.shape.y + 48;
		DrawTexture(ball.texture, ball.x, ball.y, WHITE);
		if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			ball.state = 0;
			if (player.shape.y <= 296)
			{
				ball.direction.y = -1;
			}
			else
			{
				ball.direction.y = 1;
			}
			ball.direction.x = 1;
		}
		return;
	}

	// Keep ball in bounds
	if (ball.y < 0 && ball.x > player.shape.x && ball.x < enemy.x + 64)
	{
		ball.direction.y = 1;
	}
	else if (ball.y > 688)
	{
		ball.direction.y = -1;
	}

	if (ball.x > 1300)
	{
		PlaySound(win_sound);
		player.score++;
		ball.state = 1;
	}
	else if (ball.x < -20)
	{
		PlaySound(loss_sound);
		enemy.score++;
		ball.state = 1;
	}

	// Ball vs player collision
	if (CheckCollisionRecs(ball.hitbox, player.shape))
	{
		PlaySound(bounce_sound);
		// Ball above paddle
		if (ball.y < player.shape.y)
		{
			// Ball also behind paddle
			if (ball.x > 48)
			{
				ball.direction.x = 1;
			}
			ball.direction.y = -1;
		}
		// Ball below paddle
		else if (ball.y > player.shape.y + 96)
		{
			if (ball.x > 48)
			{
				// Ball also behind paddle
				ball.direction.x = 1;
			}
			ball.direction.y = 1;
		}
		else
		{
			ball.direction.x = 1;
		}
	}

	// Ball vs enemy colision
	if (CheckCollisionRecs(ball.hitbox, enemy.hitbox))
	{
		PlaySound(bounce_sound);
		// Ball above paddle
		if (ball.y < enemy.y)
		{
			// Ball also behind paddle
			if (ball.x < enemy.x - 8)
			{
				ball.direction.x = -1;
			}
			ball.direction.y = -1;
		}
		// Ball below paddle
		else if (ball.y > enemy.y + 96)
		{
			if (ball.x < enemy.x - 8)
			{
				// Ball also behind paddle
				ball.direction.x = -1;
			}
			ball.direction.y = 1;
		}
		else
		{
			ball.direction.x = -1;
		}
	}

	ball.x += ball.direction.x * delta * ball.speed;
	ball.y += ball.direction.y * delta * ball.speed;

	ball.hitbox.x = ball.x;
	ball.hitbox.y = ball.y;

	DrawTexture(ball.texture, ball.x, ball.y, WHITE);
}
