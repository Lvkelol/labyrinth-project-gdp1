#pragma once
#include "maze.hpp"


/**
 * @brief beinhaltet alle wichtigen Attribute und Funktionen des Labyrinthspiels
 * -> es kann ein neues oder geladenes Spiel geladen werden
 * -> der Spieler sich muss durch das Labyrinth zum Ziel bewegen um zu gewinnen
 */
class game : public maze{
    public:
        /**
         * @brief ruft das Spiel auf
         */
        game(){
            mazeGame();
        }

        /**
         * @pre maze::createMaze()
         * @brief Entnimmt der mazeInformation Start- und Endpunkt des Labyrinths und markiert diese mit 'A' und 'B'
         * -> wenn es sich um ein neues Spiel handelt, werden dem Spieler die Werte des Startpunktes zugewiesen und dieser mit 'P' ueberschrieben
         * -> wenn ein Spiel geladen wird, wird die Zuweisung der Position der Spieler ueber die Suchschleife, die das P im Labyrinth sucht und die Werte uebergibt
         * -> wenn das Spiel gestartet ist (gameStarted = true) wird nur noch nach der neuen Zuweisung des Spielers, dieser neu "gezeichnet"
         */
        void createWaypoints();

        /**
         * @brief setzt die Postion des Spielers
         * -> findet die Spielerposition heraus, wenn das Spiel geladen wurde
         * @param startX x-Koordinate des Startpunktes
         * @param startY y-Koordinate des Startpunktes
         */
        void setPlayer(int startX, int startY);

        /**
         * @brief Hauptfunktion des Spiels
         * -> wird in dem Konstruktor aufgerufen und ruft alle fuer das Spiel notwendigen Funktionen auf
         * -> Abfrage an Spieler, ob Spiel neu gestartet oder geladen werden soll
         * -> Auswertung des Inputs durch chooseGameOption()
         */
        void mazeGame();

        /**
         * @brief Wertet den Input des Spielers beim Waehlen der Spieloption aus
         * 'L' -> Laden: Datei zum Einlesen wird auf "mazeSave.txt" gesetzt, Spiel wird ausgefuehrt
         * 'N' -> Neu: Datei zum Einlesen wird auf "maze.txt" gesetzt, Spiel wird ausgefuehrt
         */
        void chooseGameOption();

        /**
         * @pre Eingabe eines Buchstabens
         * @brief ueberprueft die Gueltigkeit der Eingabe und fuehrt die dazugehuerige Funktion (den Zug/die Bewegung im Labyrinth) aus
         * -> bei Ungueltigkeit ist eine neue Eingabe erforderlich
         */
        void playerAction();

        /**
         * @pre Bewegung ist gueltig -> wird durch inputTest() ueberprueft
         * @brief fuehrt die Bewegung des Spielers in die bestimmte Richtung im Labyrinth aus
         * @param x Veraenderung der Spielerposition in x Richtung
         * @param y Veraenderung der Spielerposition in y Richtung
         */
        void playerMove(int x, int y);

        /**
         * @brief testet, ob die Eingabe des Spielers die Groeße 1 hat
         * -> wenn falsch, neue Eingabe erforderlich
         * -> wenn wahr wird ein Kleinbuchtstabe der Eingabe zu einem Grossbuchstaben umgewandelt, Grossbuchstaben und Zahlen bleiben
         * -> speichert den Buchstaben dann in Input
         */
        void inputTest();

        /**
         * @param x Veraenderung der Spielerposition in x Richtung
         * @param y Veraenderung der Spielerposition in y Richtung
         * @returns true , wenn der Zug/die Bewegung korrekt bzw. nicht in eine Wand und nicht ausserhalb des Labyrinths geht
         */
        bool testMove(int x, int y);

        /**
         * @returns true, wenn die Position des Spieler gleich der Endposition ist, sonst false
         */
        bool gameWin();

        /**
         * @brief gibt die Anleitung des Spiels aus und stellt den turnCount ein (laden oder neu zaehlen)
         * -> fuehrt mit der while(!gameWin() && !endGame) Schleife das Spiel aus
         * -> gibt, wenn das Spiel nicht durch ein vorzeitiges Beenden ('X') beendet wurde, den letzten Stand des Labyrinths (Spieler steht auf Endfeld) aus
         *    und beendet Programm
         */
        void newGame();

        /**
         * @brief fuegt an die mazeInformation den turnCount an
         * -> fuegt die mazeInformation und das actualMaze zusammen in den mazeSaveText
         * -> speichert den mazeSaveText in der Datei "mazeSave.txt"
         */
        void saveGame();

    private:
        char input; /** Input des Spielers */
        char *startP; /** Startpunkt */
        char *endP; /** Endpunkt */
        char *player; /** Punkt des Spielers */
        int *turnCount; /** Zugzahl */
        int playerX; /** x-Koordinate des Spielers */
        int playerY; /** y-Koordinate des Spielers */
        bool gameStarted; /** gibt an, ob das Spiel gestartet wurde */
        bool movedPlayer; /** gibt an, ob der Spieler bewegt wurde */
        bool gameLoaded; /** gibt an, ob das Spiel geladen wurde */
        bool endGame; /** gibt an, ob das Spiel beendet werden soll */
};
