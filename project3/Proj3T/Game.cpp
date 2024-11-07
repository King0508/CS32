// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "temple.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) :m_distance(goblinSmellDistance)
{

}
Game::~Game()
{}
int Game::getDistance() const
{
    return(m_distance); 
}
void Game::play()
{
    Temple t(this);//pass in game pointer so goblin can get smell distance from a getter in the game class 
    t.newTemple(); 
    t.generate();
    t.display();
    bool gameover = false; 
    char c;
    while ((c = getCharacter()) != 'q')
    {   
        t.playerRegen();//before each moves, player has 1/10 chance of regening one hp 
        switch (c)
        {
        case'h':
        case'j':
        case'k':
        case'l'://4 directions for movement 
            if (t.playerSleep()) //if player is asleep, nothing can be done 
                break;
            t.playerMove(c);
            break; 
        case'>':
            if (t.playerSleep())
                break;
            if (t.reachStair())
            {
                t.newTemple(); 
                t.generate();
            }  
            break; 
        case 'g':
            if (t.playerSleep())
                break;
            else if (t.reachIdol())
            {   
                gameover = true; 
                std::cout << "You pick up the golden idol" << std::endl;
                std::cout << "Congratulations, you won!" << std::endl;
                t.displayActionString(); 
                std::cout << "Press q to exit game." << std::endl;
                char q;
                while ((q = getCharacter()) != 'q')
                {}
                exit(0);
            }
            else
                t.pickUp();     
            break; 
        case'i':
            if (t.playerSleep())
                break;
            clearScreen(); 
            t.displayInventory(); 
            while (getCharacter() != ' ')
                break; 
            break;      
        case 'c':
            if (t.playerSleep())
                break;
            t.cheat(); 
            break; 
        case'w':
            if (t.playerSleep())
                break;
            clearScreen();
            t.displayInventory();
            char w;
            w = getCharacter();
            if (w >= 97 && w  <= 122)
                t.wield(w); 
            break; 
        case'r':
            if (t.playerSleep())
                break;
            clearScreen();
            t.displayInventory();
            char r;
            r = getCharacter(); 
            if (r >= 97 && r <= 122)
                t.read(r);
            break;
        default:
            break; 
        }
        if (!gameover) //if gameover, gold idol has been picked up and none of the below functions should be called 
        {
            t.monstersMove();
            t.displayObjects();
            clearScreen();
            t.display();
        }    
    }
}
