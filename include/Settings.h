#ifndef SETTINGS_H
#define SETTINGS_H


// ROOT include.
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
// C++ include.
#include <vector>
#include <string>
#include <iostream>

#include "SortedEvent.h"
#include "TFile.h"
#include "TTree.h"
#include "TEnv.h"

#include <filesystem>
#include <iostream> 
#include <cstdlib>  



class Settings {
public:
    Settings(const std::string& filename);// config(new TEnv(filename.data())) {}
    ~Settings();

    void getValues();
    void dumpValues();


    const double& getPressure() const { return pressureMbar; }
    const unsigned int getNumberOfStrips_P() const { return numberOfStrips_P; }
    const unsigned int getNumberOfStrips_N() const { return numberOfStrips_N; }
    const unsigned int getNumberOfDetectors() const { return numberOfDetectors; }

private:
    TEnv *config;

    double pressureMbar; // [mbar]
    unsigned int numberOfStrips_P;
    unsigned int numberOfStrips_N;
    unsigned int numberOfDetectors;
    //ClassDef(Settings, 1);

};



#endif // SETTINGS_H