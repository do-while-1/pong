#include "main.h"

int main(){
	srand (time(NULL));
	gameInit();
	graphicsInit();
	do{
		timerFps();
		moveBall();
		checkColl();
		aiMovePaddle();
		//graphicsRenderFpsText(fpsTimer.lastFps);
		
		graphicsDraw();
	}while(gameEvents());
	graphicsClose();
	return 0;
}

void gameInit(){
	pong.field.rect.x = 100;
	pong.field.rect.y = 100;
	pong.field.rect.w = 1400;
	pong.field.rect.h = 700;

	pong.player.rect.x = 150;
	pong.player.rect.y = 450;
	pong.player.rect.w = 10;
	pong.player.rect.h = 50;

	pong.enemy.rect.x = 1350;
	pong.enemy.rect.y = 450;
	pong.enemy.rect.w = 10;
	pong.enemy.rect.h = 50;

	pong.ball.rect.x = 800;
	pong.ball.rect.y = 450;
	pong.ball.rect.w = 10;
	pong.ball.rect.h = 10;
	
	pong.ball.x = 800;
	pong.ball.y = 450;
	pong.ball.angle = 45;
	pong.ball.speed = 5;
}

void movePaddle(struct paddle * p, int dir){
	p->rect.y += dir*2;
	if(p->rect.y > 750) p->rect.y = 750;
	if(p->rect.y < 100) p->rect.y = 100;
}

void aiMovePaddle(){
	if(pong.ball.rect.y < pong.enemy.rect.y) movePaddle(&pong.enemy, -1);
	if(pong.ball.rect.y > pong.enemy.rect.y) movePaddle(&pong.enemy, 1);
}

void moveBall(){
	pong.ball.x += sin(pong.ball.angle * PI / 180.0) * pong.ball.speed;
	pong.ball.y += cos(pong.ball.angle * PI / 180.0) * pong.ball.speed;
	
	pong.ball.rect.x = pong.ball.x;
	pong.ball.rect.y = pong.ball.y;
}

void checkColl(){
	SDL_bool collP = SDL_HasIntersection(&pong.player.rect, &pong.ball.rect);
	SDL_bool collE = SDL_HasIntersection(&pong.enemy.rect, &pong.ball.rect);

	if(collP == SDL_TRUE || collE == SDL_TRUE) pong.ball.angle += 180 + 40 - rand() % 20;
	if(pong.ball.rect.x < 100){
		resetBall(&pong.ball);
		pong.enemy.score++;
		graphicsRenderScores(pong.player.score, pong.enemy.score);
	}
	if(pong.ball.rect.x > 1500){
		resetBall(&pong.ball);
		pong.player.score++;
		graphicsRenderScores(pong.player.score, pong.enemy.score);
	}

	if(pong.ball.rect.y > 800){
		pong.ball.angle = 180 - pong.ball.angle;
	}
	if(pong.ball.rect.y < 100){
		pong.ball.angle = 180 - pong.ball.angle;
	}
}

void resetBall(){
	pong.ball.rect.x = 800;
	pong.ball.rect.y = 450;
	pong.ball.x = 800;
	pong.ball.y = 450;
	pong.ball.angle = rand() % 360;
}

int gameEvents(){
	SDL_Event event;
	while(SDL_PollEvent (&event)){
		switch(event.type){
			case SDL_QUIT:
				return 0;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
		}
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_UP]) {
    		movePaddle(&pong.player, -1);
	}
	if (state[SDL_SCANCODE_DOWN]) {
    		movePaddle(&pong.player, 1);
	}
	return 1;
}

void timerFps(){
	fpsTimer.frames++;
	if(SDL_GetTicks() < fpsTimer.frameTime + (1000.f/fpsLimit)){
		SDL_Delay(fpsTimer.frameTime + 1000.f/fpsLimit - SDL_GetTicks());
	}
	fpsTimer.frameTime = SDL_GetTicks();
	if(fpsTimer.currentTime + 1000 < SDL_GetTicks()){
		fpsTimer.lastFps = fpsTimer.frames;
		fpsTimer.frames = 0;
		fpsTimer.currentTime = SDL_GetTicks();
	}
	
}
