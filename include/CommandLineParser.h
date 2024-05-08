#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H


#include <string>
#include <vector>
#include <iostream>
#include <map>


class CommandLineParser {
public:
    CommandLineParser(int argc, char* argv[]);
    ~CommandLineParser(); 



    const std::string& GetInputFilename() const { return inputFileName; }
    const std::string& GetSettingsFilename() const { return settingsFileName; }
    const std::pair<std::string*, bool>& GetParsedInfo(std::string) const;
    
private:
    void ParseArguments(int argc, char* argv[]);
    
    void PrintPropertiesSet() const;
    void PrintHelp() const;


    std::map<std::string, std::pair<std::string*, bool>> optionMap;

    std::string inputFileName;
    std::string settingsFileName;
    //std::string outputFileName;
    std::string calibrationFileName;
    bool FLAG_helpRequested = false;

};

#endif // COMMANDLINEPARSER_H
