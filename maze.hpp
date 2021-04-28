#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "mazeError.hpp"

/**
 * @brief liest das Dokument, erschafft daraus das Labyrinth nach den festgelegten Maﬂen und
 *        gibt dieses aus
 */
class maze{
public:
    maze (){}

    /**
     * @brief liest die Datei mazeFile, speichert sie in mazeText
     * -> liest die mazeText, vorkommende Zahlen werden im Vekor mazeInformation gespeichert
     * @throws Error, wenn die Datei nicht vorhanden ist
     */
    void createMazeInformation();

    /**
     * @brief mazeFile wird gelesen
     * -> wenn am Beginn der Zeile keine Zahl steht, schreibt jedes Element des Labyrinths in einen 2-dimensionalen Vektor
     */
    void createMaze();

    /**
     * @pre maze::createMaze()
     * @brief actualMaze -> 2 dimensionaler Vektor, der das Labyrinth beinhaltet
     * -> Maze wird in der Konsole ausgegeben
     */
    void printMaze();

    /**
     * @brief liest die Datei mazeFile mit dem Labyrinth aus und erstellt daraus den 2-dimensionalen Vektor actualMaze
     */
    void buildMaze();

    /**
     * @pre Zeile temp beginnt nicht mit einer Zahl
     * @brief -> wenn die Zeilelaenge kleiner der Breite ist, wird die Zeile auf die Breite des Labyrinths mit Leereichen aufgefuellt
     *        -> wenn die Zeilenlaenge groeﬂer der Breite ist, wird die Zeile auf die Breite des Labyrinths verkleinert
     */
    std::string lineOptimization(std::string);

protected:
    std::string mazeFile; /** beinhaltet den File des Labyrinths */
    std::string mazeText; /** beinhaltet das Labyrinth als String */
    std::vector <std::vector <char> > actualMaze; /** beinhaltet das Labyrinth */
    std::vector <int> mazeInformation; /** Stellen: 0:Hoehe, 1:Breite, 2:StartY, 3:StartX, 4:ZielY, 5:ZielX, (6:turnCount -> nur bei einem gespeicherten Spiel) */
    size_t height; /** Hoehe des Labyrinths */
    size_t width; /** Breite des Labyrinths */
};
