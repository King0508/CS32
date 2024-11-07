#include <stack> 
#include <string>
#include <iostream> 
#include <cassert>
using namespace std; 

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
int evaluate(std::string infix, std::string& postfix, bool& result);
int main()
{

    /*string pf;
    bool answer;
    assert(evaluate("!!(F|T)", pf, answer) == 0 && pf == "FT|!!" && answer);
    assert(evaluate("T&!F", pf, answer) == 0 && answer);
    assert(evaluate("T|F&F", pf, answer) == 0 && answer);
    assert(evaluate("!F|T", pf, answer) == 0 && answer);
    assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("T & !(F | T & T | F) | !!!(F & T & F) ", pf, answer) == 0 && answer);
    assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("F", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("|", pf, answer) == 1);
    assert(evaluate("&", pf, answer) == 1);
    assert(evaluate("(", pf, answer) == 1);
    assert(evaluate(")", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("A", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 0 && pf == "TF|" && answer);
    assert(evaluate(" T | F ", pf, answer) == 0 && pf == "TF|" && answer);
    assert(evaluate("T&F", pf, answer) == 0 && pf == "TF&" && !answer);
    assert(evaluate(" T & F ", pf, answer) == 0 && pf == "TF&" && !answer);
    assert(evaluate("!T", pf, answer) == 0 && pf == "T!" && !answer);
    assert(evaluate(" ! T ", pf, answer) == 0 && pf == "T!" && !answer);
    assert(evaluate("(T)", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate(" ( T ) ", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate(" ( T & ! ( F | T & T & ( ! F | F ) ) | F )", pf, answer) == 0 && pf == "TFTT&F!F|&|!&F|" && !answer);
    assert(evaluate(" T ", pf, answer) == 0);
    assert(evaluate(" T &   F    ", pf, answer) == 0 && pf == "TF&" && !answer);
    assert(evaluate("(T&(T&(T&(T&(T&(T&(T&(T&(T)))))))))", pf, answer) == 0 && pf == "TTTTTTTTT&&&&&&&&");
    assert(evaluate(" T !", pf, answer) == 1);
    assert(evaluate(" T | &", pf, answer) == 1);
    assert(evaluate(" ( ) ", pf, answer) == 1);
    assert(evaluate(" T ( F & F )", pf, answer) == 1); 
    assert(evaluate("T | (F&F|)", pf, answer) == 1);
    assert(evaluate(" T ( & F ) ", pf, answer) == 1);
    assert(evaluate("(((((F)))))", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|" && answer);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("T+F", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&|" && !answer);
    assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("!(T&F|T)", pf, answer) == 0 && pf == "TF&T|!" && !answer);
    assert(evaluate("(T|F)&(F|F)&(!F|F&T)&T", pf, answer) == 0 && pf == "TF|FF|&F!FT&|&T&" && !answer);
    assert(evaluate("!(T|F) | F | F | T&F | T & !F", pf, answer) == 0 && pf == "TF|!F|F|TF&|TF!&|" && answer);
    assert(evaluate("T&T&T&T&T&T&T&T&T&T&F", pf, answer) == 0 && pf == "TT&T&T&T&T&T&T&T&T&F&" && !answer);
    assert(evaluate("(T|F)&(F|T)&(T&T)&!(T&F)|F&F", pf, answer) == 0 && pf == "TF|FT|&TT&&TF&!&FF&|" && answer);
    assert(evaluate("!!(T|F)&F|T&!T&!F|F|T", pf, answer) == 0 && pf == "TF|!!F&TT!&F!&|F|T|" && answer);
    assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("T&(F) ", pf, answer) == 0 && pf == "TF&" && !answer);
    assert(evaluate("T & !F", pf, answer) == 0 && pf == "TF!&" && answer);
    assert(evaluate("  !(F|T)", pf, answer) == 0 && pf == "FT|!" && !answer);
    assert(evaluate("!F | T", pf, answer) == 0 && pf == "F!T|" && answer);
    assert(evaluate("T|F&F", pf, answer) == 0 && pf == "TFF&|" && answer);
    assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 && pf == "TFTT&|F|!&FT&F&!!!|" && answer);
    assert(evaluate("!(!T&(!F|T)", pf, answer) == 1);
    assert(evaluate("!(!F|T)&(!T|!F)|!!!F&!T&T&!(!F|T)", pf, answer) == 0 && pf == "F!T|!T!F!|&F!!!T!&T&F!T|!&|" && !answer);
    assert(evaluate("!!(!F|T)&(!T|!F)|!!!F&T&T&!(!F|T)", pf, answer) == 0 && pf == "F!T|!!T!F!|&F!!!T&T&F!T|!&|" && answer);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|" && answer);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("T+F", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
        && pf == "FF!TF&&|" && !answer);
    assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate(" ", pf, answer) == 1);
    assert(evaluate("  ", pf, answer) == 1);
    assert(evaluate("!     !(!F|T)&(!T|!F)|!!!F&T&T&!(!F|T)", pf, answer) == 0 && pf == "F!T|!!T!F!|&F!!!T&T&F!T|!&|" && answer);
    
    assert(evaluate(" !    !!!!!! F  ", pf, answer) == 0);

    
    assert(evaluate(" F | (T) ) ", pf, answer) == 1);
    cout << "Passed all tests" << endl;*/



    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','X','.','X' },
        { 'X','.','X','X','X','.','.','.','.','X' },
        { 'X','.','X','.','X','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','.','.','X' },
        { 'X','.','.','.','X','.','X','X','.','X' },
        { 'X','.','X','.','X','.','.','X','.','X' },
        { 'X','.','X','X','X','X','.','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 4, 3, 1, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

