/**
 * @author Lukas Marche
 * INB-1
 * @date 16.02.2020
 */
#include "maze.hpp"
#include "game.hpp"


/**
 * @brief Startet das Labyrinth Spiel
 * -> faengt einen Fehler, falls eine Labyrinthdatei nicht vorhanden ist
 */
void startMazeProgram();


/**
 * Fuehrt das Labyrinthspiel aus.
 * Der Spieler P muss durch das Labyrinth zum Ziel B gelangen.
 * Das Spiel endet, sobald der Spieler gewonnen oder das Spiel manuell beendet hat.
 */
int main()
{
    startMazeProgram();
    return 0;
}


void startMazeProgram(){
    try{
        game A;
    }
    catch (mazeError &e){
        std::cout << e.getErrorMessage() << std::endl;
    }
}
