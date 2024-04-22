#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
bool game_is_running = false;
bool in_main_menu = true;
bool in_game_play = false;

typedef struct
{
    float x;
    float y;
    float width;
    float height;
} Ball;

Ball ball;
bool moveUp = false;
bool moveLeft = false;
bool moveRight = false;
bool moveDown = false;
int fontSize = 50;

Uint32 startTime = 0;
Uint32 currentTime = 0;
Uint32 elapsedTime = 0;
Uint32 remainingTime = 0;
const Uint32 GAME_DURATION = 300000; // 5 minutes in milliseconds

void init_resources()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Game with Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Couldn't create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Couldn't create renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() != 0)
    {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Load font with desired size (e.g., 36)
    font = TTF_OpenFont("assets/font/Ubuntu-Bold.ttf", fontSize); // Replace "arial.ttf" with your font file
    if (!font)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialize game timer
    startTime = SDL_GetTicks();
}

void setup()
{
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            game_is_running = false;
            break;
        case SDL_KEYDOWN:
            if (in_main_menu)
            {
                // Process menu selection
                switch (event.key.keysym.sym)
                {
                case SDLK_1:
                    printf("Starting Game!\n");
                    in_main_menu = false;
                    in_game_play = true;
                    break;
                case SDLK_2:
                case SDLK_ESCAPE:
                    printf("Exiting Game!\n");
                    game_is_running = false;
                    break;
                default:
                    break;
                }
            }
            else
            {
                // Process game input
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    in_game_play = false;
                    in_main_menu = true;
                    break;
                case SDLK_w:
                case SDLK_UP:
                    moveUp = true;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    moveLeft = true;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    moveRight = true;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    moveDown = true;
                    break;
                default:
                    break;
                }
            }
            break;
        case SDL_KEYUP:
            // Process game input
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
            case SDLK_UP:
                moveUp = false;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                moveLeft = false;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                moveRight = false;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                moveDown = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void update()
{
    float moveSpeed = 5.0f;

    if ((moveUp || moveDown) && (moveLeft || moveRight))
    {
        moveSpeed = 3.0f; // Reduce speed if moving diagonally
    }

    if (in_game_play)
    {
        if (moveUp && ball.y > 0)
        {
            ball.y -= moveSpeed;
        }
        if (moveLeft && ball.x > 0)
        {
            ball.x -= moveSpeed;
        }
        if (moveRight && ball.x < WINDOW_WIDTH - ball.width)
        {
            ball.x += moveSpeed;
        }
        if (moveDown && ball.y < WINDOW_HEIGHT - ball.height)
        {
            ball.y += moveSpeed;
        }

        // Update game timer
        currentTime = SDL_GetTicks();
        elapsedTime = currentTime - startTime;
        remainingTime = (GAME_DURATION > elapsedTime) ? (GAME_DURATION - elapsedTime) : 0;

        if (remainingTime <= 0)
        {
            printf("Game Over! Time's up.\n");
            in_game_play = false;
            in_main_menu = true;
        }
    }
}

void render_main_menu()
{
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    SDL_Color textColor = {0, 0, 0, 255};

    // Render menu options
    render_text("PRESS '1' TO START GAME", font, textColor, 100, 600);
    render_text("PRESS '2' TO ESCAPE GAME", font, textColor, 100, 700);

    SDL_RenderPresent(renderer);
}

void render_game()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render ball
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect ballRect = {(int)ball.x, (int)ball.y, (int)ball.width, (int)ball.height};
    SDL_RenderFillRect(renderer, &ballRect);

    // Render remaining time at the top of the screen
    SDL_Color textColor = {255, 0, 0, 255};
    char timeText[50];
    snprintf(timeText, sizeof(timeText), " %d ", remainingTime / 1000);
    render_text(timeText, font, textColor, (WINDOW_WIDTH / 2) - fontSize, 20);

    SDL_RenderPresent(renderer);
}

void render_text(const char *text, TTF_Font *font, SDL_Color color, int x, int y)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (surface)
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture)
        {
            SDL_Rect rect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

void cleanup()
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    init_resources();
    setup();

    game_is_running = true;
    while (game_is_running)
    {
        process_input();
        if (in_main_menu)
        {
            render_main_menu();
        }
        else if (in_game_play)
        {
            update();
            render_game();
        }
        SDL_Delay(FRAME_TARGET_TIME);
    }

    cleanup();
    return EXIT_SUCCESS;
}
