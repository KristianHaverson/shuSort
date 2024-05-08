#include "shuShort.h"

// MAIN //
// TODO: Tidy up calibrator class
// TODO: Create a class for input CAEN data
// TODO: make I/O class to be more generic


// saveSingles //
// TODO: check P and N logic? board 0 and board 1?

// calibrator //
// TODO: check P and N logic? board 0 and board 1?



// Data Flow Overview:
// - Output file can be built with or without calibration
// - Contains:
//    1) Tree: containing sorted data (can be read into a script for calibration)
//    2) SinglesHists: Histograms made using normal data, useful for debugging

// Limitations:
//  I) Calibration: Needs to be done externally by reading in the sorted tree
//  II) Event Hists: After calibration, single hists can be checked; then, it's safe to read in the "SORTED" tree to another script and make PCA plots elsewhere

int main(int argc, char *argv[]) {
    
    // Command line input parsing
    std::unique_ptr<CommandLineParser> parser = std::make_unique<CommandLineParser>(argc, argv);

    // Get and read settings file
    std::string filename_settings = parser->GetSettingsFilename();
    SettingsLog = std::make_unique<Settings>(filename_settings);

    // Read input filename and data to a generic I/O class
    std::string filename_input = parser->GetInputFilename();
    inputStream = std::make_unique<InputOutput>();
    inputStream->readTree(filename_input, "Data_R");
    inputStream->setInputBranch("Channel", Channel);
    inputStream->setInputBranch("Timestamp", Timestamp);
    inputStream->setInputBranch("Board", Board);
    inputStream->setInputBranch("Energy", Energy);
    inputStream->setInputBranch("EnergyShort", EnergyShort);

    // Create calibrator class; checks if option is set in CLI, if false then returns generic (1, 0)
    calibrator = std::make_unique<Calibrator>(SettingsLog, parser->GetParsedInfo("-c"));

    // Set output filename
    std::string filename_output = generateOutputFileName(filename_input);

    // Initialize data tree
    std::shared_ptr<SortedEvent> outData = std::make_shared<SortedEvent>();

    // Create output stream
    outputStream = std::make_unique<InputOutput>();

    // Initialize output file
    outputStream->initoutput(filename_output);

    // Link output tree
    outputStream->linkOutputData(outData);

    // Run loop and save tree
    runOutputLoop(outData); // Tree

    // Run loop and save histograms
    saveSingles(); // Histograms

    // Write and exit
    outputStream->writeFile();

    return 0;
}
