#pragma once
#include <string>

/**
 * @brief Klasse, die bei einem Fehler geworfen wird
 */
class mazeError{
    public:
        /**
         * @param eM beinhaltet die Fehlermeldung
         */
        mazeError(std::string eM){
            errorMessage = eM;
        }

        /**
         * @returns errorMessage
         */
        std::string getErrorMessage();

    private:
        std::string errorMessage;
};
