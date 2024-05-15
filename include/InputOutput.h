#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H


// ROOT include.
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
// C++ include.
#include <vector>
#include <string>
#include <iostream>

#include "InputOutput.h"
#include "SortedEvent.h"
#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TEnv.h"

#include <filesystem>
#include <iostream> 
#include <cstdlib>  



class InputOutput {
public:
    InputOutput();
    ~InputOutput();


    //generic
    TTree* getTree() { return tree; }
    TFile* getTFile()  { return file; }
    //TDirectory* getFolder()  { return folder; }

    // input
    void readTree(const std::string& fileName, const std::string& treeName);
    void setInputBranch(std::string name,UShort_t &data);
    void setInputBranch(std::string name,ULong64_t &data);
    void setInputBranch(std::string name,UInt_t &data);

    //output
    void initoutput(const std::string& fileName);
    void linkOutputData( std::shared_ptr<SortedEvent> outData);
    void writeFile();
 //   void createFolder(std::string dirName);
private:

    TTree* tree = nullptr;
    TFile* file = nullptr;
   // TDirectory* folder =nullptr;


    bool FLAG_readFlag=false;
    bool FLAG_writeFlag=false;
};


#endif // INPUTOUTPUT_H