#include <iostream>

struct Board
{
    bool **board;

    size_t size;

    Board(const int n)
    {
        size = n;
        board = new bool*[n];
        for (int i = 0; i < n; i++)
        {
            board[i] = new bool[n];
        }
    }

    ~Board()
    {
        for (size_t i = 0; i < size; i++)
        {
            delete board[i];
        }
        delete board;
    }

    void PlaceQueen(const int x, const int y)
    {
        board[x][y] = true;
    }
};



bool CheckForThreats(Board *b, const int x, const int y)
{
    if(b->board[x][y] == true)
        return true;
    
    for (size_t i = 0; i < b->size; i++)
    {
        // horizontal
        if (i != x && b->board[i][y] == true)
        {
            std::cout << "Threat found on the horizontal at (" << i << ", " << y << ")" << std::endl;
            return true;
        }
            
        for (size_t j = 0; j < b->size; j++)
        {
            // vertical
            if (j != y && b->board[x][j] == true)
            {
                std::cout << "Threat found on the vertical at (" << x << ", " << j << ")" << std::endl;
                return true;
            }
            
            // top left/bottom right diagonal
            int _diagX1 = x + i;
            int _diagY1 = y + j;
            if (_diagX1 != x && _diagY1 != y && _diagX1 < b->size && _diagY1 < b->size)
            {
                if (b->board[_diagX1][_diagY1])
                {
                    std::cout << "Threat found on the 1st diagonal at (" << _diagX1 << ", " << _diagY1 << ")" << std::endl;
                    return true;
                }
            }
            
            // bottom left/top right diagonal
            int _diagX2 = x + i;
            int _diagY2 = b->size - (y + j);
            if (_diagX2 != x && _diagY2 != y && _diagX2 < b->size && _diagY2 > 0)
            {
                if (b->board[_diagX2][_diagY2])
                {
                    std::cout << "Threat found on the 2nd diagonal at (" << _diagX2 << ", " << _diagY2 << ")" << std::endl;
                    return true;
                }
            }
        }
    }

    return false;   // no threatening queens found
}

bool Solve(Board *b)
{
    b->PlaceQueen(0, 0);    // first queen always goes at (0, 0)

    int numQueens = b->size - 1;
    
    while (numQueens > 0)
    {
        for (int i = 0; i < b->size; i++)
        {
            for (int j = 0; j < b->size; j++)
            {
                std::cout << "(" << i << ", " << j << ")" << std::endl;
                if (!CheckForThreats(b, i, j))
                {
                    b->PlaceQueen(i, j);
                    numQueens--;
                    std::cout << "Queen placed at (" << i << ", " << j << ")" << std::endl;
                    
                }
            }
        }
        std::cout << "Queens remaining: " << numQueens << std::endl;
    }
}

int UserInputHell()
{
    int _n;
    while (true)
    {
        std::cout << "Pick a number 4 or greater: ";
        std::cin >> _n;
        if (_n > 3)
        {
            return _n;
        }
    }
}

int main()
{
    Board *b = new Board(UserInputHell());
    std::cout << "Board of size " << b->size << " made" << std::endl;

    Solve(b);

    delete b;

    return 0;
}