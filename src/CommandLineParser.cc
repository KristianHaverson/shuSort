#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int argc, char* argv[]) {

    optionMap["-i"] = {&inputFileName, false};
    optionMap["-c"] = {&calibrationFileName, false};
    optionMap["-s"] = {&settingsFileName, false};

    ParseArguments(argc, argv);

    if (FLAG_helpRequested) {
        PrintHelp();
        exit(0);
    }

    if (!optionMap.at("-i").second) {
        PrintHelp();
        exit(0);
    }

    if (!optionMap.at("-s").second) {
        //std::cout<<"Settings file must be provided"<<std::endl;
        PrintHelp();
        
        exit(0);
    }


    PrintPropertiesSet();
}

CommandLineParser::~CommandLineParser() {}

void CommandLineParser::ParseArguments(int argc, char* argv[]) {


    for (int i = 1; i < argc; ++i) {

        std::string arg = argv[i];

        if (optionMap.find(arg) != optionMap.end()) {

            if (i + 1 < argc) {
                
                *(optionMap[arg].first) = argv[++i];
                optionMap[arg].second = true; // Flag set

            } else {
                std::cerr << "Error: " << arg << " option requires a value." << std::endl;
            }

        } else if (arg == "-h") {
            FLAG_helpRequested = true;
        } else {
            std::cerr << "Error: Unknown option '" << arg << "'." << std::endl;
        }
    }
}

void CommandLineParser::PrintPropertiesSet() const {
    std::cout << "==========================\n";
    std::cout << "Command Line Parser:\n";
    std::cout << "==========================\n";

    std::cout << "Input filename:     ";
    if (optionMap.at("-i").second) {
        std::cout << "Yes ('" << *optionMap.at("-i").first << "')\n";
    } else {
        std::cout << "No\n";
    }

    std::cout << "Setting filename:    ";
    if (optionMap.at("-s").second) {
        std::cout << "Yes ('" << *optionMap.at("-s").first << "')\n";
    } else {
        std::cout << "No\n";
    }

    std::cout << "Calib filename:     ";
    if (optionMap.at("-c").second) {
        std::cout << "Yes ('" << *optionMap.at("-c").first << "')\n";
    } else {
        std::cout << "No\n";
    }
    std::cout << "==========================\n";

}

void CommandLineParser::PrintHelp() const {
    std::cout << "Usage:\n";
    std::cout << "  -i <filename>    Input filename (required)\n";
    std::cout << "  -s <filename>    Settings filename (required)\n";
    std::cout << "  -c <filename>    Calibration filename (optional) \n";
    std::cout << "  -h               Show help\n";
}

const std::pair<std::string*, bool>& CommandLineParser::GetParsedInfo(std::string cliKey) const {
    return optionMap.at(cliKey);
}
