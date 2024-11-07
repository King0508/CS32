#include <queue>
#include <iostream>
class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    std::queue<Coord> coordqueue;
    coordqueue.push(Coord(sr, sc));
    maze[sr][sc] = 'A';//A indicates that square has been encountered 
    while (!coordqueue.empty())
    {
        int r = coordqueue.front().r();//save current Coord's m_row 
        int c = coordqueue.front().c();//save current Coord's m_col  
        std::cerr << "pop row: " << r << " pop columns: " << c << std::endl; 
        coordqueue.pop(); 
        if (r == er && c == ec)
        {
            return true;
        }
        if (maze[r][c + 1] != 'A' && maze[r][c + 1] != 'X')
        {

            coordqueue.push(Coord(r, c + 1));
            maze[r][c + 1] = 'A';
            //std::cerr << "row: " << r << " columns: " << c+1 << std::endl;
        }
        if (maze[r + 1][c] != 'A' && maze[r + 1][c] != 'X')
        {

            coordqueue.push(Coord(r + 1, c));
            maze[r + 1][c] = 'A';
            //std::cerr << "row: " << r-1 << " columns: " << c << std::endl;

        }
        if (maze[r][c - 1] != 'A' && maze[r][c - 1] != 'X')
        {

            coordqueue.push(Coord(r, c - 1));
            maze[r][c - 1] = 'A';
            //std::cerr << "row: " << r << " columns: " << c-1 << std::endl;
        }

        if (maze[r - 1][c] != 'A' && maze[r - 1][c] != 'X')
        {

            coordqueue.push(Coord(r - 1, c));
            maze[r - 1][c] = 'A';
            //std::cerr << "row: " << r-1 << " columns: " << c << std::endl;
        }
    }
    return false;
}