/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef CMD_LINE_ARGS_HPP_
#define CMD_LINE_ARGS_HPP_

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Class to parse command line arguments.
 */
class CmdLineArgs
{
  public:
    /**
     * @brief Constructor for CmdLineArgs.
     * @param argc Number of arguments.
     * @param argv Arguments.
     */
    explicit CmdLineArgs(const int argc, const char* argv[]) : m_fileInputJson{paramValueOf(argc, argv, "-i")}
    {
    }

    /**
     * @brief Gets the input file path.
     * @return Input file path.
     */
    const std::string& inputFileJson() const
    {
        return m_fileInputJson;
    }

    /**
     * @brief Shows the help to the user.
     */
    static void showHelp()
    {
        std::cout << "\nUsage: ComfyChairCpp <option(s)>\n"
                  << "Options:\n"
                  << "\t-h \t\t\tShow this help message\n"
                  << "\t-i INPUT_FILE\t\tSpecifies the input file.\n"
                  << "\nExample:"
                  << "\n\t./ComfyChairCpp -i input.json\n"
                  << std::endl;
    }

  private:
    static std::string paramValueOf(const int argc, const char* argv[], const std::string& switchValue,
                                    const std::pair<bool, std::string>& required = std::make_pair(true, ""))
    {
        for (int i = 1; i < argc; ++i)
        {
            const std::string currentValue{argv[i]};

            if (currentValue == switchValue && i + 1 < argc)
            {
                // Switch found
                return argv[i + 1];
            }
        }

        if (required.first)
        {
            showHelp();
            throw std::runtime_error{"Switch value: " + switchValue + " not found."};
        }

        return required.second;
    }

    static bool paramExists(const int argc, const char* argv[], const std::string& switchValue,
                            const std::pair<bool, bool>& required = std::make_pair(false, false))
    {
        for (int i = 1; i < argc; ++i)
        {
            const std::string currentValue{argv[i]};

            if (currentValue == switchValue)
            {
                return true;
            }
        }

        if (required.first)
        {
            throw std::runtime_error{"Switch value: " + switchValue + " not found."};
        }

        return required.second;
    }

    static std::vector<std::string> splitActions(const std::string& values)
    {
        if (values.empty())
        {
            return {};
        }

        std::vector<std::string> actionsValues;
        std::stringstream ss{values};

        while (ss.good())
        {
            std::string substr;
            getline(ss, substr, ','); // Getting each string between ',' character
            actionsValues.push_back(std::move(substr));
        }

        return actionsValues;
    }

    const std::string m_fileInputJson;
};

#endif // CMD_LINE_ARGS_HPP_
