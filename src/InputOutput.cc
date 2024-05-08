#include "InputOutput.h"

InputOutput::InputOutput() {

}

InputOutput::~InputOutput() {

}



void InputOutput::readTree(const std::string& fileName, const std::string& treeName) {

    if (file) {
        file->Close();
        delete file;
    }

    file = TFile::Open(fileName.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Failed to open file " << fileName << std::endl;
        exit(0);
    }

    tree = dynamic_cast<TTree*>(file->Get(treeName.c_str()));
    if (!tree) {
        std::cerr << "Error: Failed to retrieve tree " << treeName << " from file " << fileName << std::endl;
        exit(0);
    }

    FLAG_readFlag=true;

}






void InputOutput::setInputBranch(std::string name,UShort_t &data){
    if(FLAG_readFlag)
        tree->SetBranchAddress(name.c_str(),&data);
    else{

        std::cout<<"file not set for reading "<<std::endl;
    }

}

void InputOutput::setInputBranch(std::string name,ULong64_t &data){
    if(FLAG_readFlag)
        tree->SetBranchAddress(name.c_str(),&data);
    else{
        std::cout<<"file not set for reading "<<std::endl;
    }}
    
void InputOutput::setInputBranch(std::string name,UInt_t &data){
    if(FLAG_readFlag)
        tree->SetBranchAddress(name.c_str(),&data);
    else{
        std::cout<<"file not set for reading "<<std::endl;
    }
}



void InputOutput::initoutput(const std::string& fileName) {
    if(FLAG_readFlag){
        std::cout<<"file set for reading "<<std::endl;
        exit(0);
    }
    file = new TFile(fileName.data(), "recreate");

    FLAG_writeFlag=true;

}



void InputOutput::linkOutputData( std::shared_ptr<SortedEvent> sortedEvent) {
    file->cd();
    tree = new TTree("event_tree", "event_tree");
    tree->Branch("SortedEvent", "SortedEvent", &(*sortedEvent));
    //tree->SetDirectory(0);
    
}



void InputOutput::writeFile() {
    if(!FLAG_writeFlag){
        std::cout << "file no set for writting" <<std::endl;
        exit(0);
    }
    if (file) {
        file->Write();
    }


}

//void InputOutput::createFolder(std::string dirName){
//    std::cout<<"HERE"<<std::endl;
//
//    if(FLAG_readFlag){
//        std::cout<<"file set for reading "<<std::endl;
//        exit(0);
//    }
//    std::cout<<"HERE"<<std::endl;
//    folder = file->mkdir(dirName.c_str());
//    if (!folder) {
//        std::cerr << "Error: Failed to create folder " << folder << std::endl;
//        exit(0);
//    }
//
//    return;
//}

//void InputOutput::createFolder(std::string dirName) {
//    std::cout << "Entering createFolder function" << std::endl; // Add debug output
//
//    // Check if reading flag is set
//    if (FLAG_readFlag) {
//        std::cout << "File set for reading, cannot create folder" << std::endl;
//
//        return; // Exit function early if reading flag is set
//    }
//
//    // Check if file pointer is valid
//    if (!file) {
//        file = new TFile("file", "recreate");
//        FLAG_writeFlag=true;
//
//    }
//
//    // Attempt to create folder
//    folder = file->mkdir(dirName.c_str());
//    if (!folder) {
//        std::cerr << "Error: Failed to create folder " << dirName << std::endl;
//        return; // Exit function if folder creation fails
//    }
//
//    // Debug output to confirm folder creation
//    std::cout << "Folder '" << dirName << "' created successfully" << std::endl;
//}
