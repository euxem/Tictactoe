#include "tictactoe_c++/tictactoe+.h"
#include "tictactoe_c/tictactoec.h"

#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        if (((std::string)argv[1]).compare("--graphical") == 0 || ((std::string)argv[1]).compare("-g") == 0){
            graphical();
            return 0;
        }
        if (((std::string)argv[1]).compare("--help") == 0 || ((std::string)argv[1]).compare("-h") == 0) {
            std::cout << "Usage: tictactoe [OPTION]\n";
            std::cout << "Play a game of tictactoe\n";
            std::cout << "\nOptions list :\n";
            std::cout << "    -h | --help : help menu\n";
            std::cout << "    -g | --graphical : show graphical version of the game" << std::endl;
            return 0;
        }
        std::cerr << "tictactoe: invalid option " << argv[1] << "\n";
        std::cerr << "Usage: tictactoe [OPTION]" << std::endl;
        return 1;
    }
    terminal();
    return 0;
}