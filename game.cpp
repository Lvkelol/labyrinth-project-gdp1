#include "game.hpp"


void game::createWaypoints(){
    if (!gameStarted){ /** setzt die fuer das Spiel wichtigen Parameter */
        int startY = mazeInformation.at(2);
        int startX = mazeInformation.at(3);
        int endY = mazeInformation.at(4);
        int endX = mazeInformation.at(5);
        if (startY < 0 || startY > static_cast<int>(height) || startX < 0 || startX > static_cast<int>(width)){
            throw mazeError("Der Startpunkt ist nicht innerhalb des Labyrinths.");
        }
        if (endY < 0 || endY > static_cast<int>(height) || endX < 0 || endX > static_cast<int>(width)){
                throw mazeError("Der Endpunkt ist nicht innerhalb des Labyrinths.");
        }
        endP = &actualMaze.at(static_cast<size_t>(endX)).at(static_cast<size_t>(endY)); /** setzt Endpunkt */
        *endP = 'B';
        startP = &actualMaze.at(static_cast<size_t>(startX)).at(static_cast<size_t>(startY)); /** setzt Startpunkt */
        setPlayer(startX, startY);
    }
    *startP = 'A'; /** wenn die Postion des Spielers veraendert wurde, muessen dem neuen Punkt die Zeichen zugewiesen werden */
    *player = 'P';
}


void game::setPlayer(int startX, int startY){
    if (!gameLoaded){ /** wenn das Spiel nicht geladen wurde muss der Spieler auf den Startpunkt/die Startparameter gesetzt werden */
        player = startP;
        playerX = startX;
        playerY = startY;
    }
    else /** wenn das Spiel geladen wurde, wird in dem geladenen Labyrinth der Spieler lokalisiert und die Parameter (Koordinaten) des Spielers werden auf diesen Punkt gesetzt */
    {
        for (size_t i = 0; i < height; ++i){
            for (size_t j = 0; j < width; ++j){
                if (actualMaze.at(j).at(i) == 'P'){
                playerX = static_cast<int>(j);
                playerY = static_cast<int>(i);
                player = &actualMaze.at(j).at(i);
                }
            }
        }
    }
}


void game::mazeGame(){
    std::cout << "Moechtest du ein neues Spiel starten (N) oder das gespeicherte Spiel laden (L)?" << std::endl;
    gameStarted = false;
    endGame = false;
    chooseGameOption();
}


void game::chooseGameOption(){
    inputTest();
    switch (input){
        case 'N':
            mazeFile = "maze.txt";
            newGame(); /** neues Spiel wird gestartet */
            break;
        case 'L':
            gameLoaded = true;
            mazeFile = "mazeSave.txt";
            newGame(); /** Spiel wird geladen */
            break;
        default:
            std::cout << "Eingabe inkorrekt. Bitte erneut eingeben." << std::endl;
            chooseGameOption();
            break;
    }
}


void game::playerAction(){
    movedPlayer = false;
    inputTest();
    switch(input){
    case 'O':
    case '8':
        if (testMove(0,-1)){ /** testet, ob das Feld ueber dem Spieler ein legales Feld ist fuer die Bewegung nach oben */
            playerMove(0,-1);
        }
        break;
    case 'R':
    case '6':
        if (testMove(1,0)){ /** wie oben, Test fuer Bewegung nach rechts */
            playerMove(1,0);
        }
        break;
    case 'U':
    case '2':
        if (testMove(0,1)){ /** wie oben, Test fuer Bewegung nach unten */
            playerMove(0,1);
        }
        break;
    case 'L':
    case '4':
        if (testMove(-1,0)){ /** wie oben, Test fuer Bewegung nach links */
                playerMove(-1,0);
        }
        break;
    case 'S':
        saveGame();
        std::cout << "Das Spiel wurde gespeichert." << std::endl;
        std::cout << "Bitte gib deine neue Eingabe ein." << std::endl;
        playerAction(); /** gibt dem Spieler die Moeglichkeit das Spiel nach dem Speichern weiter zu spielen */
        break;
    case 'X':
        endGame = true; /** sorgt dafuer, dass das Spiel abgebrochen wird */
        break;
    default:
        break;
    }
    if (!movedPlayer && !endGame){ /** wenn der Spieler keinen gueltigen Zug gemacht hat und das Spiel nicht beendet werden soll wird eine neue Aktion vom Spieler gefordert */
        std::cout << "Eingabe inkorrekt, bitte erneut eingeben." << std::endl;
        playerAction();
    }
    if(!endGame)createWaypoints(); /** setzt das Zeichen fuer den Startpunkt ('A') und das fuer den Spieler ('B') neu, wenn das Spiel nicht beendet werden soll */
}


void game::playerMove(int x, int y){
    *player = '.';
    playerX = playerX + x;
    playerY = playerY + y;
    player = &actualMaze.at(static_cast<size_t>(playerX)).at(static_cast<size_t>(playerY));
    movedPlayer = true;
}


void game::inputTest(){
    std::string tempString;
    char tempChar;
    std::cin >> tempString;
    while (tempString.size()!= 1){ /** testet, ob nur 1 Zeichen eingeben wurde, sonst neue Eingabe erforderlich */
        std::cout << "Bitte nur einen Buchstaben oder eine Zahl eingeben." << std::endl;
        std::cin >> tempString;
    }
    tempChar = tempString.at(0);
    input = static_cast<char>(toupper(static_cast<int>(tempChar))); /** wandelt Kleinbuchstaben in Grossbuchstaben um -> Eingabe muss nicht zwingend durch den Grossbuchstaben erfolgen */
}


bool game::testMove(int x, int y){
    int xDest = playerX + x; /** x-Koordinate des neuen Punktes der Bewegung */
    int yDest = playerY + y; /** y-Koordinate des neuen Punktes der Bewegung */
    if (xDest >= 0 && yDest >= 0){ /** testet ob der neue Punkt legal erreichbar ist */
        if (static_cast<size_t>(xDest) < width && static_cast<size_t>(yDest) < height){
            if(actualMaze.at(static_cast<size_t>(xDest)).at(static_cast<size_t>(yDest))!='*'){
                return true;
            }
        }
    }
    return false;
}


bool game::gameWin(){
    if (player == endP){
        return true;
    }
    else return false;
}


void game::newGame(){
    buildMaze();
    createWaypoints(); /** setzt die Wegpunkte und die Spielerposition */
    if (!gameLoaded) mazeInformation.push_back(1);
    turnCount = &mazeInformation.at(6);
    gameStarted = true;
    std::cout << "\nAnleitung:\nBewege dich durch das Labyrinth und versuch zum Ziel (B) zu kommen.\n\nSteuerung:\nO,8: Oben   R,6: Rechts   U,2: Unten   L,4: Links\n" << std::endl;
    std::cout << "Gib 'S' ein um zu speichern.\nGib 'X' ein um zu beenden." << std::endl;
    while(!gameWin() && !endGame){ /** fuehrt das Spiel aus waehrend es nicht gewonnen und nicht beendet wurde */
        printMaze();
        std::cout << "Dein " << *turnCount << ". Zug ist:" << std::endl;
        playerAction();
        if(!gameWin() && !endGame) ++*turnCount; /** wenn das Spiel nicht beendet wird, dann wird der Zugzaehler erhoeht */
    }
    if (!endGame){ /** gibt das Feld aus, dass den Spieler auf dem Endpunkt zeigt */
        printMaze();
        std::cout << "Geschafft!" << std::endl << "Du hast " << *turnCount << " Zuege gebraucht." << std::endl;
    }
    std::cout << "Das Spiel wurde beendet." << std::endl; /** wird aufgerufen wenn das Spiel gewonnen oder beendet wurde */
}


void game::saveGame(){
    std::string mazeSaveText;
    std::string temp;
    for (size_t i = 0; i < mazeInformation.size(); ++i){ /** fuegt die mazeInformation zu einem String zusammen */
        temp = std::to_string(mazeInformation.at(i));
        mazeSaveText.append(temp);
        mazeSaveText.push_back(' ');
        if (i % 2 != 0 || i == 6){ /** die ersten 6 Zahlen sind formatiert wie im urspruenglichen Dokument (maze.txt) und die letzte Zahl (turnCount) wird in eine neu Zeile geschrieben */
            mazeSaveText.append("\n");
        }
    }
    for (size_t i = 0; i < height; ++i){ /** schiebt Zeile fuer Zeile des actualMaze (Labyrinths) in die mazeSaveText unter die Daten der mazeInformation */
        for (size_t j = 0; j < width; ++j){
            mazeSaveText.push_back(actualMaze.at(j).at(i));
        }
        mazeSaveText.append("\n");
    }
    std::ofstream mazeSave("mazeSave.txt"); /** Stream zur Speicherdatei */
    mazeSave << mazeSaveText; /** mazeSaveText (Speichertext des aktuellen Spielstandes) wird in die Datei geschrieben */
    mazeSave.close(); /** Datei wird geschlossen */
}
