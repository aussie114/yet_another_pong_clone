#ifndef ENEMY_H
#define ENEMY_H
typedef struct
{
	int x;
	int y;
	int w;
	int h;
	float acceleration;
	float deceleration;
	float speed;
	float max_speed;
	int score;
	Rectangle hitbox;
	RenderTexture2D render_texture;
	Texture2D texture;
} Enemy;
extern Enemy enemy;
void setup_enemy(void);
void process_enemy(void);
#endif
