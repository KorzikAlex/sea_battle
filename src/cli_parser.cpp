#include "cli_parser.hpp"

CLIParser::CLIParser(const int argc, char **argv): size_x(10), size_y(10) {
    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg[0] == '-') {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                this->options[arg] = argv[i + 1];
                ++i;
            } else this->options[arg] = "";
        }
    }

    for (const auto &[fst_opt, snd_opt]: options) {
        if (fst_opt == "--size_x" && snd_opt != "")
            this->size_x = std::stoi(snd_opt); // set size_x of board from parser
        else if (fst_opt == "--size_y" && snd_opt != "")
            this->size_y = std::stoi(snd_opt); // set size_y of board from parser
        if (fst_opt == "--help" || fst_opt == "-h") {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "--size_x:" << " [<int> arg] " << "set width size of board" << std::endl;
            std::cout << "--size_y:" << " [<int> arg] " << "set height size of board" << std::endl;
            std::cout << "--help: " << "get information about program" << std::endl;
            std::cout << std::endl;
            exit(EXIT_SUCCESS);
        }
    }
}

int CLIParser::getSizeX() const noexcept {
    return this->size_x;
}

int CLIParser::getSizeY() const noexcept {
    return this->size_y;
}


