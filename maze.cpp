#include "maze.hpp"


void maze::createMazeInformation(){
    std::ifstream ifs(mazeFile);
    if (!ifs) throw mazeError("Es fehlt eine wichtige Datei fuer das Ausfuehren des Programms.");
    mazeText = "";
    while (ifs){ /** speichert den Inhalt der Datei zeilenweise in den */
        std::string temp;
        std::getline(ifs, temp);
        mazeText.append(temp+"\n");
    }
    std::string tempNumber;
    for (size_t i = 0; i < mazeText.size(); ++i){ /** ueberprueft jede Stelle des Labyrinthstrings, ob es sich um eine Zahl (auch mehrstellig moeglich) */
        if (isdigit(mazeText.at(i))){ /** wenn es sich um eine Zahl handelt wird diese an tempNumber angehaengt (fuer diese Operation ist tempNumber ein String) */
            tempNumber.push_back(mazeText.at(i));
        }
        else {
            if (tempNumber.size() != 0){ /** wenn keine Zahl an der Stelle ist und die tempNumber eine gueltige Zahl ist wird diese an die mazeInformation angehaengt */
                int number = std::stoi(tempNumber);
                mazeInformation.push_back(number);
                tempNumber = "";
            }
        }
    }
    if (mazeFile == "maze.txt" && mazeInformation.size() != 6) throw mazeError("Das eingelesene Labyrinth ist fehlerhaft.");
    if (mazeFile == "mazeSave.txt" && mazeInformation.size() != 7) throw mazeError("Das eingelesene Labyrinth ist fehlerhaft.");
}


void maze::createMaze(){
    std::vector <std::vector <char> > tempMaze (width, std::vector<char>(height, ' '));
    std::ifstream ifs(mazeFile);
    size_t j = 0; /** Zeile des Labyrinths, in die geschrieben wird */
    while (ifs){ /** liest Zeile fuer Zeile die Datei mazeFile aus */
        std::string temp;
        std::getline(ifs, temp);
        if (temp.size()!=0){
            if (!std::isdigit(temp.at(0))){ /** wenn die Zeile nicht leer und das erste Zeichen keine Zahl ist */
                temp = lineOptimization(temp); /** passt die Zeile auf die Breite des Labyrinths an */
                    for (size_t i = 0; i < width; ++i){ /** geht die Zeile durch und schreibt diese in den 2 dimensionalen in die Zeile j */
                        if (mazeFile == "maze.txt" && temp.at(i) != ' ' && temp.at(i) != '*') throw mazeError("Das Laybrinth beinhaltet ungueltige Zeichen.");
                        tempMaze.at(i).at(j) = temp.at(i);
                    }
                ++j;
            }
        }
    }
    actualMaze = tempMaze;
}


void maze::printMaze(){
    std::cout << std::endl;
    for (size_t i = 0; i < height; ++i){
        for (size_t j = 0; j < width; ++j){
            std::cout << actualMaze.at(j).at(i);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void maze::buildMaze(){
    createMazeInformation();
    height = static_cast<size_t>(mazeInformation.at(0));
    width = static_cast<size_t>(mazeInformation.at(1));
    createMaze();
}


std::string maze::lineOptimization(std::string temp){
    size_t diff = 0;
    if (temp.size() < width){ /** Laenge der Zeile kleiner als Breite -> Zeile wird verlaengert */
        diff = width - temp.size();
        for (size_t i = 1; i <= diff; ++i){
            temp.push_back(' ');
        }
    }
    if (temp.size() > width){ /** Laenge der Zeile groeßer als Breite -> Zeile wird verkuerzt */
        diff = temp.size() - width;
        for (size_t i = 1; i <= diff; ++i){
            temp.pop_back();
        }
    }
    return temp;
}
