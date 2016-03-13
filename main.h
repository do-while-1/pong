#ifndef _main_
#define _main_

#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "/usr/include/SDL2/SDL.h"
#include "/usr/include/SDL2/SDL_ttf.h"

#define screensizex 1600
#define screensizey 900
#define fpsLimit 100
#define PI 3.14159265


struct graphics{
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * fps;
	SDL_Texture * playerScore;
	SDL_Texture * enemyScore;
	TTF_Font * font;
}gfx;

struct timer{
	unsigned int currentTime, frames, frameTime, lastFps;
}fpsTimer;

struct map{
	SDL_Rect rect;
};

struct paddle{
	SDL_Rect rect;
	int score;
};

struct pongBall{
	SDL_Rect rect;
	float x, y;
	double angle;
	int speed;
};

	

struct game{
	struct map field;
	struct paddle player;
	struct paddle enemy;
	struct pongBall ball;
}pong;

void gameInit();
void timerFps();
int gameEvents();

void graphicsInit();
void graphicsRenderFpsText(int fps);
void graphicsRenderScores(int player, int enemy);
void graphicsDraw();
void graphicsClose();

void movePaddle(struct paddle * p, int dir);
void aiMovePaddle();
void moveBall();
void checkColl();
void resetBall();

#endif
