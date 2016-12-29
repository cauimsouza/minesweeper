#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "MineSweeper.h"

MineSweeper::MineSweeper(int width, int height, int mines)
{
    this->width = width;
    this->height = height;
    this->mines = mines;
    endOfGame = false;
    remainingSquares = width * height - mines;
    setField();
}

MineSweeper::~MineSweeper()
{
    for(int i = 0; i < height + 2; i++)
    {
        delete[] clicked[i];
        delete[] hasMine[i];
        delete[] neighbors[i];
    }
    delete[] clicked;
    delete[] hasMine;
    delete[] neighbors;
    clicked = nullptr;
    hasMine = nullptr;
    neighbors = nullptr;
}

void MineSweeper::setField()
{
    clicked = new bool*[height+2];
    hasMine = new bool*[height+2];
    neighbors = new int*[height+2];
    for(int i = 0; i < height + 2; i++)
    {
        clicked[i] = new bool[width+2];
        hasMine[i] = new bool[width+2];
        neighbors[i] = new int[width+2];

        for(int j = 0; j < width + 2; j++)
        {
            clicked[i][j] = hasMine[i][j] = false;
            neighbors[i][j] = 0;
        }
    }

    std::srand(std::time(0));
    for(int i = 0; i < mines; )
    {
        int x = 1 + (std::rand() % width);
        int y = 1 + (std::rand() % height);
        if(hasMine[y][x]) continue;
        hasMine[y][x] = true;
        for(int k = 0; k < 8; k++)
            neighbors[y+dy[k]][x+dx[k]]++;
        i++;
    }
}

bool MineSweeper::stillPlaying()
{
    return !endOfGame;
}

/*
    Returns true if the play is valid. Returns false otherwise
*/
bool MineSweeper::play(int x, int y)
{
    if(clicked[y][x])   return false;

    if(hasMine[y][x])
    {
        endOfGame = true;
        clicked[y][x] = true;
    }
    else
    {
        floodFill(y, x);
        if(remainingSquares == 0)   endOfGame = true;
    }
    return true;
}

bool MineSweeper::victory()
{
    return !stillPlaying() && remainingSquares == 0;
}

void MineSweeper::printField(bool scan)
{
    if(stillPlaying()) scan = false;

    for(int i = height; i >= 1; i--)
    {
        for(int j = 1; j <= width; j++)
        {
            if(clicked[i][j])
            {
                if(hasMine[i][j]) printf("T");
                else printf("%d", neighbors[i][j]);
            }
            else if(scan)
            {
                if(hasMine[i][j]) printf("*");
                else    printf("-");
            }
            else    printf("-");
        }
        printf("\n");
    }
}

void MineSweeper::floodFill(int i, int j)
{
    if(i < 1 || i > height || j < 1 || j > width || clicked[i][j] || hasMine[i][j])  return;
    clicked[i][j] = true;
    remainingSquares--;
    if(neighbors[i][j]) return;
    for(int k = 0; k < 8; k++)
        floodFill(i + dy[k], j + dx[k]);
}
