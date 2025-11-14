#ifndef PLAYER_H
#define PLAYER_H
typedef struct
{
	Rectangle shape;
	float acceleration;
	float deceleration;
	float speed;
	float max_speed;
	int score;
	RenderTexture2D render_texture;
} Player;
extern Player player;
void setup_player(void);
void process_player(void);
#endif
