#ifndef MINESWEEPER_H
#define MINESWEEPER_H


class MineSweeper
{
    public:
        MineSweeper(int width, int height, int bombs);
        ~MineSweeper();
        bool stillPlaying();
        bool play(int x, int y);
        bool victory();
        void printField(bool scan=false);

    protected:

    private:
        bool **clicked;
        bool **hasMine;
        int **neighbors; // neighbors[i][j] = number of mines surrounding position (i,j)
        bool endOfGame;
        int remainingSquares;
        int width;
        int height;
        int mines;
        const int dx[8] = {1,1,1,-1,-1,-1,0,0};
        const int dy[8] = {0,1,-1,0,1,-1,1,-1};
        void setField();
        void floodFill(int i, int j);
};

#endif // MINESWEEPER_H
