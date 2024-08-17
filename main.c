#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define WIN_HEIGHT 500
#define WIN_WIDTH 500
#define W_H_SQ 166

SDL_Texture *x_tex = NULL;
SDL_Texture *o_tex = NULL;

bool isPointIn(int x, int y, SDL_Rect rect)
{
    if ((x >= rect.x && rect.x + rect.w >= x) && (y >= rect.y && rect.y + rect.h >= y))
        return true;

    return false;
}

SDL_Texture *loadImage(SDL_Renderer *ren, const char *path)
{
    SDL_Surface *img = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);

    if (img == NULL || tex == NULL)
        printf("Error");
    return tex;
}

int main(int ac, char *av[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Error: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event ev;
    int x = 0, y = 0, click = 0;

    char board[9] = {0};
    char currTurn = 'X';

    o_tex = loadImage(ren, "./opng.png");
    x_tex = loadImage(ren, "./xpng.png");

    const int sqs_len = 9;
    SDL_Rect sqs[sqs_len];
    SDL_Texture *tex[9] = {NULL};

    for (int i = 0; i < sqs_len; i++)
    {
        sqs[i].x = i % 3 * (W_H_SQ);
        sqs[i].y = i / 3 * (W_H_SQ);
        sqs[i].w = W_H_SQ;
        sqs[i].h = W_H_SQ;
    }

    while (running)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(ren, 75, 75, 75, 255);
        SDL_RenderClear(ren);

        click = SDL_GetMouseState(&x, &y);

        if (click)
        {
            for (int i = 0; i < sqs_len; i++)
            {
                if (isPointIn(x, y, sqs[i]) && board[i] != 'X' && board[i] != 'O')
                {
                    printf("LOG:%c %d\n", board[i],i);
                    board[i] = currTurn;
                    if (currTurn == 'X')
                    {
                        tex[i] = x_tex;
                        currTurn = 'O';
                    }
                    else
                    {
                        tex[i] = o_tex;
                        currTurn = 'X';
                    }
                }
            }
        }

        for (int i = 0; i < sqs_len; i++)
        {
            if (tex[i] != NULL)
                SDL_RenderCopy(ren, tex[i], NULL, &(sqs[i]));
        }
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderDrawLine(ren, 0, W_H_SQ, WIN_WIDTH, W_H_SQ);
        SDL_RenderDrawLine(ren, 0, W_H_SQ * 2, WIN_WIDTH, W_H_SQ * 2);
        SDL_RenderDrawLine(ren, W_H_SQ, 0, W_H_SQ, WIN_HEIGHT);
        SDL_RenderDrawLine(ren, W_H_SQ * 2, 0, W_H_SQ * 2, WIN_HEIGHT);

        SDL_RenderPresent(ren);
        SDL_Delay(17);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}