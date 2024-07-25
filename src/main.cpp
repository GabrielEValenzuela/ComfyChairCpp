/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "cmdLineArgs.hpp"

int main(const int argc, const char* argv[])
{
    // LCOV_EXCL_START
    try
    {
        CmdLineArgs cmdLineArgs(argc, argv);
        auto jsonInput = cmdLineArgs.inputFileJson();

        if (jsonInput.empty())
        {
            CmdLineArgs::showHelp();
            return 1;
        }

        std::ifstream inputFile(jsonInput);
        if (!inputFile.is_open())
        {
            std::cerr << "Error: Unable to open file " << jsonInput << ". Did you check if the file exists? "
                      << std::endl;
            return 1;
        }

        nlohmann::json json;
        inputFile >> json;
        inputFile.close();
        std::cout << "Running ComfyChairCpp with input file: " << jsonInput << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // LCOV_EXCL_STOP
    return 0;
}
