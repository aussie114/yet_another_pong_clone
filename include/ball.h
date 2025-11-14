#ifndef BALL_H
#define BALL_H
typedef struct
{
	int x;
	int y;
	int w;
	int h;
	Vector2 direction;
	float speed;
	int collision_resolved;
	Rectangle hitbox;
	RenderTexture2D render_texture;
	Texture2D texture;
	int state;
} Ball;
extern Ball ball;
void setup_ball(void);
void process_ball(void);
#endif
