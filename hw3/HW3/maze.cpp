//bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
//{
//    //std::cerr << "row: " << sr << " columns: " << sc << std::endl;
//    if (sr == er && sc == ec)
//        return true; 
//    maze[sr][sc] = 'M';
//    
//    if (maze[sr + 1][sc] != 'X' && maze[sr + 1][sc] != 'M')
//    {   
//        if(pathExists(maze, sr + 1, sc, er, ec))
//            return true;      
//    }
//    if (maze[sr][sc+1] != 'X' && maze[sr][sc+1] != 'M')
//    {
//        if(pathExists(maze, sr, sc + 1, er, ec))
//            return true;
//    }
//    if (maze[sr-1][sc] != 'X' && maze[sr-1][sc] != 'M')
//    {
//        if(pathExists(maze, sr - 1, sc, er, ec))
//            return true;
//    }
//    if (maze[sr][sc-1] != 'X' && maze[sr][sc-1] != 'M')
//    {
//        if(pathExists(maze, sr, sc - 1, er, ec))
//            return true;
//    }
//    return false; 
//}