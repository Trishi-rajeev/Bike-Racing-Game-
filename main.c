#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BIKE_WIDTH 60
#define BIKE_HEIGHT 30
#define GRAVITY 0.5f
#define MAX_SPEED 10.0f

typedef struct {
    float x, y;
    float velocity_x, velocity_y;
    float rotation;
    bool is_jumping;
    int score;
} Bike;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* bike_texture;
    SDL_Texture* background_texture;
    TTF_Font* font;
    bool running;
    Bike player1;
    Bike player2;
} GameState;

void init_game(GameState* game) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("SDL_image initialization failed: %s\n", IMG_GetError());
        return;
    }

    if (TTF_Init() < 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        return;
    }

    game->window = SDL_CreateWindow("Bike Racing Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!game->window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!game->renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return;
    }

    // Initialize players
    game->player1 = (Bike){100, WINDOW_HEIGHT - 100, 0, 0, 0, false, 0};
    game->player2 = (Bike){100, WINDOW_HEIGHT - 200, 0, 0, 0, false, 0};
    game->running = true;
}

void handle_input(GameState* game) {
    SDL_Event event;
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = false;
        }
    }

    // Player 1 controls
    if (keyboard_state[SDL_SCANCODE_W]) {
        game->player1.velocity_y = -MAX_SPEED;
    }
    if (keyboard_state[SDL_SCANCODE_S]) {
        game->player1.velocity_y = MAX_SPEED;
    }
    if (keyboard_state[SDL_SCANCODE_A]) {
        game->player1.velocity_x = -MAX_SPEED;
    }
    if (keyboard_state[SDL_SCANCODE_D]) {
        game->player1.velocity_x = MAX_SPEED;
    }

    // Player 2 controls
    if (keyboard_state[SDL_SCANCODE_UP]) {
        game->player2.velocity_y = -MAX_SPEED;
    }
    if (keyboard_state[SDL_SCANCODE_DOWN]) {
        game->player2.velocity_y = MAX_SPEED;
    }
    if (keyboard_state[SDL_SCANCODE_LEFT]) {
        game->player2.velocity_x = -MAX_SPEED;
    }
    if (keyboard_state[SDL_SCANCODE_RIGHT]) {
        game->player2.velocity_x = MAX_SPEED;
    }
}

void update_game(GameState* game) {
    // Update player 1
    game->player1.x += game->player1.velocity_x;
    game->player1.y += game->player1.velocity_y;
    game->player1.velocity_y += GRAVITY;

    // Update player 2
    game->player2.x += game->player2.velocity_x;
    game->player2.y += game->player2.velocity_y;
    game->player2.velocity_y += GRAVITY;

    // Basic collision with ground
    if (game->player1.y > WINDOW_HEIGHT - BIKE_HEIGHT) {
        game->player1.y = WINDOW_HEIGHT - BIKE_HEIGHT;
        game->player1.velocity_y = 0;
        game->player1.is_jumping = false;
    }

    if (game->player2.y > WINDOW_HEIGHT - BIKE_HEIGHT) {
        game->player2.y = WINDOW_HEIGHT - BIKE_HEIGHT;
        game->player2.velocity_y = 0;
        game->player2.is_jumping = false;
    }
}

void render_game(GameState* game) {
    SDL_SetRenderDrawColor(game->renderer, 135, 206, 235, 255);
    SDL_RenderClear(game->renderer);

    // Draw ground
    SDL_SetRenderDrawColor(game->renderer, 34, 139, 34, 255);
    SDL_Rect ground = {0, WINDOW_HEIGHT - 50, WINDOW_WIDTH, 50};
    SDL_RenderFillRect(game->renderer, &ground);

    // Draw player 1 bike
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_Rect player1_rect = {
        (int)game->player1.x,
        (int)game->player1.y,
        BIKE_WIDTH,
        BIKE_HEIGHT
    };
    SDL_RenderFillRect(game->renderer, &player1_rect);

    // Draw player 2 bike
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_Rect player2_rect = {
        (int)game->player2.x,
        (int)game->player2.y,
        BIKE_WIDTH,
        BIKE_HEIGHT
    };
    SDL_RenderFillRect(game->renderer, &player2_rect);

    SDL_RenderPresent(game->renderer);
}

void cleanup(GameState* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    GameState game = {0};
    init_game(&game);

    while (game.running) {
        handle_input(&game);
        update_game(&game);
        render_game(&game);
        SDL_Delay(16); // Cap at ~60 FPS
    }

    cleanup(&game);
    return 0;
}
