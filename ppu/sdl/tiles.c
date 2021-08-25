#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../ppu.h"
#include "../../bit_manipulation.h"
#include "../../custom_types.h"

extern u8 ppu_memory[PPU_MEMORY_SIZE];
#define rec_s 5

//Screen dimension constants
const int SCREEN_WIDTH = 1700;
const int SCREEN_HEIGHT = 100;

void calculate_tile(int index, u8 tile[8][8])
{
    tile[0][0] = U8_BIT0(ppu_memory[index]) + (U8_BIT0(ppu_memory[8 + index]) << 1);
    tile[0][1] = U8_BIT1(ppu_memory[index]) + (U8_BIT1(ppu_memory[8 + index]) << 1);
    tile[0][2] = U8_BIT2(ppu_memory[index]) + (U8_BIT2(ppu_memory[8 + index]) << 1);
    tile[0][3] = U8_BIT3(ppu_memory[index]) + (U8_BIT3(ppu_memory[8 + index]) << 1);
    tile[0][4] = U8_BIT4(ppu_memory[index]) + (U8_BIT4(ppu_memory[8 + index]) << 1);
    tile[0][5] = U8_BIT5(ppu_memory[index]) + (U8_BIT5(ppu_memory[8 + index]) << 1);
    tile[0][6] = U8_BIT6(ppu_memory[index]) + (U8_BIT6(ppu_memory[8 + index]) << 1);
    tile[0][7] = U8_BIT7(ppu_memory[index]) + (U8_BIT7(ppu_memory[8 + index]) << 1);
    tile[1][0] = U8_BIT0(ppu_memory[index + 1]) + (U8_BIT0(ppu_memory[8 + index + 1]) << 1);
    tile[1][1] = U8_BIT1(ppu_memory[index + 1]) + (U8_BIT1(ppu_memory[8 + index + 1]) << 1);
    tile[1][2] = U8_BIT2(ppu_memory[index + 1]) + (U8_BIT2(ppu_memory[8 + index + 1]) << 1);
    tile[1][3] = U8_BIT3(ppu_memory[index + 1]) + (U8_BIT3(ppu_memory[8 + index + 1]) << 1);
    tile[1][4] = U8_BIT4(ppu_memory[index + 1]) + (U8_BIT4(ppu_memory[8 + index + 1]) << 1);
    tile[1][5] = U8_BIT5(ppu_memory[index + 1]) + (U8_BIT5(ppu_memory[8 + index + 1]) << 1);
    tile[1][6] = U8_BIT6(ppu_memory[index + 1]) + (U8_BIT6(ppu_memory[8 + index + 1]) << 1);
    tile[1][7] = U8_BIT7(ppu_memory[index + 1]) + (U8_BIT7(ppu_memory[8 + index + 1]) << 1);
    tile[2][0] = U8_BIT0(ppu_memory[index + 2]) + (U8_BIT0(ppu_memory[8 + index + 2]) << 1);
    tile[2][1] = U8_BIT1(ppu_memory[index + 2]) + (U8_BIT1(ppu_memory[8 + index + 2]) << 1);
    tile[2][2] = U8_BIT2(ppu_memory[index + 2]) + (U8_BIT2(ppu_memory[8 + index + 2]) << 1);
    tile[2][3] = U8_BIT3(ppu_memory[index + 2]) + (U8_BIT3(ppu_memory[8 + index + 2]) << 1);
    tile[2][4] = U8_BIT4(ppu_memory[index + 2]) + (U8_BIT4(ppu_memory[8 + index + 2]) << 1);
    tile[2][5] = U8_BIT5(ppu_memory[index + 2]) + (U8_BIT5(ppu_memory[8 + index + 2]) << 1);
    tile[2][6] = U8_BIT6(ppu_memory[index + 2]) + (U8_BIT6(ppu_memory[8 + index + 2]) << 1);
    tile[2][7] = U8_BIT7(ppu_memory[index + 2]) + (U8_BIT7(ppu_memory[8 + index + 2]) << 1);
    tile[3][0] = U8_BIT0(ppu_memory[index + 3]) + (U8_BIT0(ppu_memory[8 + index + 3]) << 1);
    tile[3][1] = U8_BIT1(ppu_memory[index + 3]) + (U8_BIT1(ppu_memory[8 + index + 3]) << 1);
    tile[3][2] = U8_BIT2(ppu_memory[index + 3]) + (U8_BIT2(ppu_memory[8 + index + 3]) << 1);
    tile[3][3] = U8_BIT3(ppu_memory[index + 3]) + (U8_BIT3(ppu_memory[8 + index + 3]) << 1);
    tile[3][4] = U8_BIT4(ppu_memory[index + 3]) + (U8_BIT4(ppu_memory[8 + index + 3]) << 1);
    tile[3][5] = U8_BIT5(ppu_memory[index + 3]) + (U8_BIT5(ppu_memory[8 + index + 3]) << 1);
    tile[3][6] = U8_BIT6(ppu_memory[index + 3]) + (U8_BIT6(ppu_memory[8 + index + 3]) << 1);
    tile[3][7] = U8_BIT7(ppu_memory[index + 3]) + (U8_BIT7(ppu_memory[8 + index + 3]) << 1);
    tile[4][0] = U8_BIT0(ppu_memory[index + 4]) + (U8_BIT0(ppu_memory[8 + index + 4]) << 1);
    tile[4][1] = U8_BIT1(ppu_memory[index + 4]) + (U8_BIT1(ppu_memory[8 + index + 4]) << 1);
    tile[4][2] = U8_BIT2(ppu_memory[index + 4]) + (U8_BIT2(ppu_memory[8 + index + 4]) << 1);
    tile[4][3] = U8_BIT3(ppu_memory[index + 4]) + (U8_BIT3(ppu_memory[8 + index + 4]) << 1);
    tile[4][4] = U8_BIT4(ppu_memory[index + 4]) + (U8_BIT4(ppu_memory[8 + index + 4]) << 1);
    tile[4][5] = U8_BIT5(ppu_memory[index + 4]) + (U8_BIT5(ppu_memory[8 + index + 4]) << 1);
    tile[4][6] = U8_BIT6(ppu_memory[index + 4]) + (U8_BIT6(ppu_memory[8 + index + 4]) << 1);
    tile[4][7] = U8_BIT7(ppu_memory[index + 4]) + (U8_BIT7(ppu_memory[8 + index + 4]) << 1);
    tile[5][0] = U8_BIT0(ppu_memory[index + 5]) + (U8_BIT0(ppu_memory[8 + index + 5]) << 1);
    tile[5][1] = U8_BIT1(ppu_memory[index + 5]) + (U8_BIT1(ppu_memory[8 + index + 5]) << 1);
    tile[5][2] = U8_BIT2(ppu_memory[index + 5]) + (U8_BIT2(ppu_memory[8 + index + 5]) << 1);
    tile[5][3] = U8_BIT3(ppu_memory[index + 5]) + (U8_BIT3(ppu_memory[8 + index + 5]) << 1);
    tile[5][4] = U8_BIT4(ppu_memory[index + 5]) + (U8_BIT4(ppu_memory[8 + index + 5]) << 1);
    tile[5][5] = U8_BIT5(ppu_memory[index + 5]) + (U8_BIT5(ppu_memory[8 + index + 5]) << 1);
    tile[5][6] = U8_BIT6(ppu_memory[index + 5]) + (U8_BIT6(ppu_memory[8 + index + 5]) << 1);
    tile[5][7] = U8_BIT7(ppu_memory[index + 5]) + (U8_BIT7(ppu_memory[8 + index + 5]) << 1);
    tile[6][0] = U8_BIT0(ppu_memory[index + 6]) + (U8_BIT0(ppu_memory[8 + index + 6]) << 1);
    tile[6][1] = U8_BIT1(ppu_memory[index + 6]) + (U8_BIT1(ppu_memory[8 + index + 6]) << 1);
    tile[6][2] = U8_BIT2(ppu_memory[index + 6]) + (U8_BIT2(ppu_memory[8 + index + 6]) << 1);
    tile[6][3] = U8_BIT3(ppu_memory[index + 6]) + (U8_BIT3(ppu_memory[8 + index + 6]) << 1);
    tile[6][4] = U8_BIT4(ppu_memory[index + 6]) + (U8_BIT4(ppu_memory[8 + index + 6]) << 1);
    tile[6][5] = U8_BIT5(ppu_memory[index + 6]) + (U8_BIT5(ppu_memory[8 + index + 6]) << 1);
    tile[6][6] = U8_BIT6(ppu_memory[index + 6]) + (U8_BIT6(ppu_memory[8 + index + 6]) << 1);
    tile[6][7] = U8_BIT7(ppu_memory[index + 6]) + (U8_BIT7(ppu_memory[8 + index + 6]) << 1);
    tile[7][0] = U8_BIT0(ppu_memory[index + 7]) + (U8_BIT0(ppu_memory[8 + index + 7]) << 1);
    tile[7][1] = U8_BIT1(ppu_memory[index + 7]) + (U8_BIT1(ppu_memory[8 + index + 7]) << 1);
    tile[7][2] = U8_BIT2(ppu_memory[index + 7]) + (U8_BIT2(ppu_memory[8 + index + 7]) << 1);
    tile[7][3] = U8_BIT3(ppu_memory[index + 7]) + (U8_BIT3(ppu_memory[8 + index + 7]) << 1);
    tile[7][4] = U8_BIT4(ppu_memory[index + 7]) + (U8_BIT4(ppu_memory[8 + index + 7]) << 1);
    tile[7][5] = U8_BIT5(ppu_memory[index + 7]) + (U8_BIT5(ppu_memory[8 + index + 7]) << 1);
    tile[7][6] = U8_BIT6(ppu_memory[index + 7]) + (U8_BIT6(ppu_memory[8 + index + 7]) << 1);
    tile[7][7] = U8_BIT7(ppu_memory[index + 7]) + (U8_BIT7(ppu_memory[8 + index + 7]) << 1);
}
int main(int argc, char *args[])
{
    char *path = "mario.nes";
    FILE *file = fopen(path, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "[ERROR]: No such file %s\n", path);
        exit(EXIT_FAILURE);
    }

    u8 buf;

    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);

    u8 PRG_SIZE;
    fread(&PRG_SIZE, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);
    fread(&buf, sizeof(u8), 1, file);

    for (int i = 0; i < 5; i++)
        fread(&buf, sizeof(u8), 1, file);

    for (int i = 0; i < PRG_SIZE * 16384; i++)
    {
        fread(&buf, sizeof(u8), 1, file);
    }
    for (int i = 0; i < 8192; i++)
    {
        fread(&buf, sizeof(u8), 1, file);
        ppu_memory[i] = buf;
    }
    fclose(file);

    //The window we'll be rendering to
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            u8 t[8][8] = {0};

            bool quite = false;
            while (!quite)
            {
                SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
                SDL_RenderClear(renderer);
                for (int tiles = 0; tiles < 30; tiles++)
                {
                    calculate_tile(tiles * 16, t);
                    for (int i = 7; i >= 0; i--)
                    {
                        for (int j = 7; j >= 0; j--)
                        {
                            switch (t[i][j])
                            {
                            case 0:
                                SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
                                break;
                            case 1:
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                break;
                            case 2:
                                SDL_SetRenderDrawColor(renderer, 200, 150, 0, 255);
                                break;
                            case 3:
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                break;
                            }
                            SDL_Rect rect = {tiles * rec_s * 8 + rec_s *(7-j), rec_s * i, rec_s, rec_s};
                            SDL_RenderFillRect(renderer, &rect);
                        }
                    }
                }
                SDL_RenderPresent(renderer);

                SDL_Event event;
                if (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        exit(0);
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
