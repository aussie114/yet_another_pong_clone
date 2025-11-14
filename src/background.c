#include "raylib.h"
RenderTexture2D background;

void create_background_texture(void)
{
	const Color BG_PURPLE = {125,55,220,255};
	const Color BG_BLUE   = { 40,84,164,255};
	background = LoadRenderTexture(1280, 720);
	BeginTextureMode(background);
	DrawRectangleGradientH(  0, 0, 640, 1280, BG_PURPLE, BG_BLUE);
	DrawRectangleGradientH(640, 0, 640, 1280, BG_BLUE, BG_PURPLE);
	for (int i = 0; i < 6; i++)
	{
		DrawRectangle(632, 20 + i*120, 16, 80, (Color){245,245,245,127});
	}
	EndTextureMode();
}
