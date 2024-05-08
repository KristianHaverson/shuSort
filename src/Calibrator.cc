#include "Calibrator.h"

Calibrator::Calibrator(std::unique_ptr<Settings>& settings , const std::pair<std::string*, bool> parsedOptions): settings(settings) {
    
    unsigned int totalStrips_P = settings->getNumberOfStrips_P();
    unsigned int totalStrips_N = settings->getNumberOfStrips_N();
    unsigned int totalDetectors = settings->getNumberOfDetectors();


    gains.resize(2*totalDetectors);
    offsets.resize(2*totalDetectors);

    gains[0].resize(totalStrips_P);
    gains[1].resize(totalStrips_N);

    offsets[0].resize(totalStrips_P);
    offsets[1].resize(totalStrips_N);

    if(parsedOptions.second){

        calibFile = new TEnv(parsedOptions.first->data());
        FLAG_readInFile= true;

        for (unsigned int stripIndex = 0; stripIndex < settings->getNumberOfStrips_P(); ++stripIndex) {
            gains[0][stripIndex] = calibFile->GetValue(Form("calib_P_%d_gain", stripIndex), 1.0);
            offsets[0][stripIndex] = calibFile->GetValue(Form("calib_P_%d_offset", stripIndex), 0.0);
        }

        for (unsigned int stripIndex = 0; stripIndex < settings->getNumberOfStrips_N(); ++stripIndex) {
            gains[1][stripIndex] = calibFile->GetValue(Form("calib_N_%d_gain", stripIndex), 1.0);
            offsets[1][stripIndex] = calibFile->GetValue(Form("calib_N_%d_offset", stripIndex), 0.0);
        }
        

    }else{
        for (unsigned int stripIndex = 0; stripIndex < settings->getNumberOfStrips_P(); ++stripIndex) {
            gains[0][stripIndex] = 1;
            offsets[0][stripIndex] = 0;
        }

        for (unsigned int stripIndex = 0; stripIndex < settings->getNumberOfStrips_N(); ++stripIndex) {
            gains[1][stripIndex] = 1;
            offsets[1][stripIndex] = 0;
        }




    }
    
    printCalibrations();

}

Calibrator::~Calibrator() {

    if(FLAG_readInFile){
        delete calibFile;
    }
}


void Calibrator::printCalibrations() const {
    std::cout << "Board Index\tStrip Index\tGain\tOffset" << std::endl;
    
    unsigned int side = 0;
    for (unsigned int stripIndex = 0; stripIndex < settings->getNumberOfStrips_P(); ++stripIndex) {
            std::cout << side << "\t\t" << stripIndex << "\t\t" << gains.at(side).at(stripIndex) << "\t" << offsets.at(side).at(stripIndex) << std::endl;
    }
    side = 1;
    for (unsigned int stripIndex = 0; stripIndex < settings->getNumberOfStrips_N(); ++stripIndex) {
            std::cout << side << "\t\t" << stripIndex << "\t\t" << gains.at(side).at(stripIndex) << "\t" << offsets.at(side).at(stripIndex) << std::endl;
    }

}
