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
            std::cout << "Threat found at (" << i << ", " << y << ")" << std::endl;
            return true;
        }
            
        for (size_t j = 0; j < b->size; j++)
        {
            // vertical
            if (j != y && b->board[x][j] == true)
            {
                std::cout << "Threat found at (" << x << ", " << j << ")" << std::endl;
                return true;
            }
            
            //bottom left/top right diagonal
            if (i != x && j != y && b->board[i][j])
            {
                std::cout << "Threat found at (" << i << ", " << j << ")" << std::endl;
                return true;
            }
            
            //top left/bottom right diagonal
            if (i != x && j != y && b->board[i][b->size - j])
            {
                std::cout << "Threat found at (" << i << ", " << b->size - j << ")" << std::endl;
                return true;
            }
        }
    }

    return false;   // no threatening queens found
}

bool Solve(Board *b)
{
    b->PlaceQueen(0, 0);    // first queen always goes at (0, 0)

    for (int i = 0; i < b->size; i++)
    {
        for (int j = 0; j < b->size; j++)
        {
            std::cout << "(" << i << ", " << j << std::endl;
            if (!CheckForThreats(b, i, j))
            {
                b->PlaceQueen(i, j);
                std::cout << "Queen placed at (" << i << ", " << j << ")" << std::endl;
            }
            else {
                std::cout << "Threatening!" << std::endl;
            }
        }
    }
}

int main()
{
    Board *b = new Board(8);
    std::cout << "Board of size " << b->size << " made" << std::endl;

    Solve(b);

    delete b;

    return 0;
}