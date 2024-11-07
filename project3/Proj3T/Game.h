// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

class Temple;

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game(); 
    void play();
    int getDistance() const;
private:
    int m_distance; 
};

#endif // GAME_INCLUDED
