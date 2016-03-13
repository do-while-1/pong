#include "main.h"

void graphicsDraw(){
	SDL_RenderClear(gfx.renderer);
	int w, h;
	SDL_QueryTexture(gfx.fps, NULL, NULL, &w, &h);
	SDL_Rect rect = {0,0,w,h};
	SDL_RenderCopy(gfx.renderer, gfx.fps, NULL, &rect);
	SDL_SetRenderDrawColor(gfx.renderer, 0, 60, 0, 255);
	SDL_RenderDrawRect(gfx.renderer, &pong.field.rect);

	rect.x = 600; rect.y = 10;	
	SDL_QueryTexture(gfx.playerScore, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(gfx.renderer, gfx.playerScore, NULL, &rect);

	rect.x = 1000; rect.y = 10;	
	SDL_QueryTexture(gfx.enemyScore, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(gfx.renderer, gfx.enemyScore, NULL, &rect);


	SDL_RenderFillRect(gfx.renderer, &pong.player.rect);
	SDL_RenderFillRect(gfx.renderer, &pong.enemy.rect);
	SDL_RenderFillRect(gfx.renderer, &pong.ball.rect);

	SDL_SetRenderDrawColor(gfx.renderer, 0, 0, 0, 255);
	SDL_RenderPresent(gfx.renderer);
}

void graphicsRenderScores(int player, int enemy){
	char buf[10];
	sprintf(buf, "%i", player);
	SDL_Color color = {0, 60, 0, 255};	
	SDL_Surface * s = TTF_RenderText_Blended(gfx.font, buf, color);
	SDL_DestroyTexture(gfx.playerScore);
	gfx.playerScore = SDL_CreateTextureFromSurface(gfx.renderer, s);
	SDL_FreeSurface(s);

	char buf2[10];
	sprintf(buf2, "%i", enemy);	
	s = TTF_RenderText_Blended(gfx.font, buf2, color);
	SDL_DestroyTexture(gfx.enemyScore);
	gfx.enemyScore = SDL_CreateTextureFromSurface(gfx.renderer, s);
	SDL_FreeSurface(s);
}

void graphicsRenderFpsText(int fps){
	char buf[10];
	sprintf(buf, "%i", fps);
	SDL_Color color = {255, 255, 255, 255};	
	SDL_Surface * s = TTF_RenderText_Blended(gfx.font, buf, color);
	SDL_DestroyTexture(gfx.fps);
	gfx.fps = SDL_CreateTextureFromSurface(gfx.renderer, s);
	SDL_FreeSurface(s);
}
void graphicsInit(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("sdl init failed\n");
		graphicsClose();
	}
	gfx.window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,           
        screensizex, screensizey, SDL_WINDOW_RESIZABLE);
	if(gfx.window == NULL){
		printf("window creation failed\n");
		graphicsClose();
	}
	gfx.renderer = SDL_CreateRenderer(gfx.window, -1, SDL_RENDERER_ACCELERATED);

	if(TTF_Init() != 0){
		printf("ttf init failed\n");
		graphicsClose();
	}
	gfx.font = TTF_OpenFont("Purisa.ttf", 74);
	if(gfx.font == NULL){
		printf("font not found\n");
		graphicsClose();
	}
	graphicsRenderScores(0, 0);
}

void graphicsClose(){
	TTF_CloseFont(gfx.font);
	TTF_Quit();
	SDL_DestroyTexture(gfx.fps);
	SDL_DestroyTexture(gfx.playerScore);
	SDL_DestroyTexture(gfx.enemyScore);
	SDL_DestroyWindow(gfx.window);
	SDL_DestroyRenderer(gfx.renderer);
	SDL_Quit();
	exit(1);
}
