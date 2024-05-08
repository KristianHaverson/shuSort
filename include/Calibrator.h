#ifndef CALIBRATOR_H
#define CALIBRATOR_H


#include "SortedEvent.h"
#include "Settings.h"


#include <vector>
#include <iostream>
#include <string>
#include <utility>

class Calibrator {
public:
    Calibrator(std::unique_ptr<Settings>& settings, const std::pair<std::string*, bool> parsedOptions);  // Default constructor
    ~Calibrator(); // Destructor

    void printCalibrations() const;

    const double getGain(int Pside_or_Nside, int strip) const{return gains.at(Pside_or_Nside).at(strip);}
    const double getOffset(int Pside_or_Nside, int strip) const{return offsets.at(Pside_or_Nside).at(strip);}
private:
    std::unique_ptr<Settings>& settings;
    std::vector<std::vector<double>> gains;
    std::vector<std::vector<double>> offsets;

    unsigned int totalBoards;
    unsigned int stripsPerBoard;

    bool FLAG_readInFile=false;
    TEnv * calibFile;
};

#endif // CALIBRATOR_H
