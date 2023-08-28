#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int game_is_running = FALSE;

//millisec of last frame
int last_frame_time = 0;

struct ball {
	float x;
	float y;
	float width;
	float height;
} ball;

struct player {
	float x;
	float y;
	float width;
	float height;
} player;

unsigned int initialize_window(void) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}
	//parameter(title, x, y, height, width, );
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	if(!window) {
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}		//-1 means default, 0 does too
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer) {
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return FALSE;
	}	
	return TRUE;
}

void process_input() {
	/*
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_QUIT:
			game_is_running = FALSE;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
					game_is_running = FALSE;
					break;
				case SDLK_s:
					ball.y += 10;
					break;
				case SDLK_w:
					ball.y -= 10;
					break;
				case SDLK_d:
					ball.x += 10;
					break;
				case SDLK_a:
					ball.x -= 10;
					break;
			}
			printf("1");
	} */

	/*
	SDL_Event event;
	if(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {game_is_running = FALSE;}
		else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {game_is_running = FALSE;}
		else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w) {
			SDL_Event event2;
			if(SDL_PollEvent(&event2)) {
				if(event2.type == SDL_KEYDOWN && event2.key.keysym.sym == SDLK_a) {
					ball.y -= 5;
					ball.x -= 5;
				}
			} else {
				ball.y -= 10;
			}
		}
		else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a) {ball.x -= 10;}
		else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) {ball.y += 10;}
		else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {ball.x += 10;}
	
	}
	*/





	/*	
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_QUIT:
			game_is_running = FALSE;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_a) {
				if(event.key.keysym.sym == SDLK_w) {
					printf("works");
				}
			} else {
				printf("doesnt work");
			}
	}
	*/


	/*	
	//https://stackoverflow.com/questions/1252976/how-to-handle-multiple-keypresses-at-once-with-sdl
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

	SDL_Event event;
	SDL_PollEvent(&event);

	if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		if(keyboard_state_array[SDLK_a] && !(keyboard_state_array[SDL_SCANCODE_DOWN])) {

		}
	}
	*/

}

void setup() {
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;
}

void update() {
	/*WHACKSHIT!! CPU LASTIG
	//TODO: sleep until reach the frame target time
	while(!SDL_TICKS_PASSED(
		SDL_GetTicks(),
		last_frame_time +
		FRAME_TARGET_TIME));
	*/
	//besser so
	/* muss aber auch nicht sein, da frame cap an sich bissi lost is baller doch einfach?
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
	if(time to wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}*/

	//Get a delta time factor converted to seconds to be used to upgrade objects
	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	
	last_frame_time = SDL_GetTicks();
	/*
	ball.x += 70 * delta_time;
	ball.y += 50 * delta_time;
	/*
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_a) {
				ball.x++;
			}
			else if(event.key.keysym.sym == SDLK_d) {
				ball.y++;
			}
	}*/


	//get user input
	// SDL_Event event;
	// SDL_PollEvent(&event);
	// switch(event.type) {
	// 	case SDL_QUIT:
	// 		game_is_running = FALSE;
	// 		break;
	// 	case SDL_KEYDOWN:
	// 		if(event.key.keysym.sym == SDLK_a) {
	// 			ball.y -= 1000 * delta_time;
	// 			break;
	// 		}
	// }

}

void render() {
	//====================INITIALIZE BALL=====================//
						//r, g, b, alpha	
	SDL_SetRenderDrawColor(renderer, 0, 20, 100, 255);
	SDL_RenderClear(renderer);
	//Draw rectangle
	SDL_Rect ball_rect = {
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};
			
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	//======================INITIALIZE PLAYER=================//
	SDL_Texture* player_texture = IMG_LoadTexture(renderer, "FILE");
	SDL_Texture player_obj = {
		(int)player.x,
		(int)player.y,
		(int)player.width,
		(int)player.height
	};

	SDL_RenderTexture()
	}
								
	//back/front buffer
	SDL_RenderPresent(renderer);
}

void destroy_window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {
	game_is_running = initialize_window();
	setup();

	while(game_is_running) {
		process_input();
		update();
		render(); //(or draw)
	}

	destroy_window();

	return 0;
}

