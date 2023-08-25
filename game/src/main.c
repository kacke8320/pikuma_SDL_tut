#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int game_is_running = FALSE;

struct ball {
				float x;
				float y;
				float width;
				float height;
} ball;

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
				}																//-1 means default, 0 does too
				renderer = SDL_CreateRenderer(window, -1, 0);
				if(!renderer) {
								fprintf(stderr, "Error creating SDL Renderer.\n");
								return FALSE;
				}
				
				return TRUE;
}

void process_input() {
				SDL_Event event;
				SDL_PollEvent(&event);

				switch(event.type) {
								case SDL_QUIT:
												game_is_running = FALSE;
												break;
								case SDL_KEYDOWN:
												if(event.key.keysym.sym == SDLK_ESCAPE)
																game_is_running = FALSE;
												break;
				}
}

void setup() {
				ball.x = 20;
				ball.y = 20;
				ball.width = 15;
				ball.height = 15;
}

void update() {
				ball.x += 1;
				ball.y += 1;
}

void render() {									//   			r, g, b, alpha	
				SDL_SetRenderDrawColor(renderer, 0, 20, 100, 255);
				SDL_RenderClear(renderer);

				//Draw rectangle
				SDL_Rect ball_rect = {
								(int)ball.x,
								(int)ball.y,
								(int)ball.width,
								(int)ball.height
				};
			
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &ball_rect);
								
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

