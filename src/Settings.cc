#include "Settings.h"

Settings::Settings(const std::string& filename) {

    if (!std::filesystem::exists(filename)) {
        std::cerr << "Error: File '" << filename << "' not found." << std::endl;
        exit(0);
    }


    config = new TEnv(filename.data());

    
    getValues();
    dumpValues();
}

Settings::~Settings() {
    delete config;
}


void Settings::getValues(){

    
    pressureMbar = config->GetValue("pressureMbar", -999.0); 
    numberOfStrips_P = config->GetValue("numberOfStrips_P", -999.0); 
    numberOfStrips_N = config->GetValue("numberOfStrips_N", -999.0); 
    numberOfDetectors = config->GetValue("numberOfDetectors", -999.0);  

}


void Settings::dumpValues(){

    std::cout << "==========================\n";
    std::cout << "Settings:\n";
    std::cout << "==========================\n";
    std::cout << "pressure: " << pressureMbar << std::endl;
    std::cout << "numberOfDetectors: " << numberOfDetectors << std::endl;
    std::cout << "numberOfStrips_P: " << numberOfStrips_P << std::endl;
    std::cout << "numberOfStrips_N: " << numberOfStrips_N << std::endl;
    std::cout << "==========================\n";


}