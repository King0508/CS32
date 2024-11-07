//#include <stack>
//#include <iostream>
//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
//    int r() const { return m_row; }
//    int c() const { return m_col; }
//private:
//    int m_row;
//    int m_col;
//};
//
//bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
//{
//    std::stack<Coord> coordStack;
//    coordStack.push(Coord(sr, sc));
//    maze[sr][sc] = 'A';//A indicates that square has been encountered 
//    while (!coordStack.empty())
//    {
//        int r = coordStack.top().r();//save current Coord's m_row 
//        int c = coordStack.top().c();//save current Coord's m_col  
//        std::cerr << "pop row: " << r << " pop columns: " << c << std::endl;
//        coordStack.pop();//pop current Coord off the stack  
//       
//        if (r == er && c == ec)
//        {
//            return true;
//        }
//        if (maze[r][c + 1] != 'A' && maze[r][c + 1] != 'X')
//        {
//          
//            coordStack.push(Coord(r, c+1));
//            maze[r][c+1] = 'A';
//            //std::cerr << "row: " << r << " columns: " << c+1 << std::endl;
//        }
//        if (maze[r + 1][c] != 'A' && maze[r + 1][c] != 'X')
//        {
//           
//            coordStack.push(Coord(r+1, c));
//            maze[r+1][c] = 'A';
//            //std::cerr << "row: " << r-1 << " columns: " << c << std::endl;
//           
//        }
//        if (maze[r][c - 1] != 'A' && maze[r][c - 1] != 'X')
//        {
//            
//            coordStack.push(Coord(r, c-1));
//            maze[r][c-1] = 'A';
//            //std::cerr << "row: " << r << " columns: " << c-1 << std::endl;
//        }
//       
//        if (maze[r - 1][c] != 'A' && maze[r - 1][c] != 'X')
//        {
//           
//            coordStack.push(Coord(r-1, c));
//            maze[r-1][c] = 'A';
//            //std::cerr << "row: " << r-1 << " columns: " << c << std::endl;
//        }
//        
//    }
//    return false; 
//}