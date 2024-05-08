#include "CommandLineParser.h"
#include "SortedEvent.h"
#include "Settings.h"
#include "InputOutput.h"
#include "SortedHistograms.h"
#include "Calibrator.h"

// ROOT include.
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
// C++ include.
#include <vector>
#include <string>


// GLOBALS - Common Objects Only
std::unique_ptr<Settings> SettingsLog;
std::unique_ptr<InputOutput> inputStream;
std::unique_ptr<InputOutput> outputStream;
std::unique_ptr<Calibrator> calibrator;

// INPUTS
UShort_t  Channel;
ULong64_t Timestamp;
UShort_t  Board;
UShort_t  Energy;
UShort_t EnergyShort;
UInt_t   Flags;



std::string generateOutputFileName(std::string filename_input){

    unsigned int last_slash_pos = filename_input.find_last_of('/');
    if (last_slash_pos != std::string::npos) {
        filename_input = filename_input.substr(last_slash_pos + 1);
    }
    std::string filename_output = "sorted_" + filename_input;

    return filename_output;
}


void runOutputLoop( std::shared_ptr<SortedEvent> outData) {
    unsigned int tree1_entries = inputStream->getTree()->GetEntries();

    const int chunkSize = 10; // from TreeRead.cpp


    // get time stamps
    double timeStamp_array[tree1_entries];
    for(unsigned long int i = 0; i<tree1_entries;i++){
        inputStream->getTree()->GetEntry(i);
        timeStamp_array[i] = Timestamp;
    }



    // do automation for threhsold
    // fill and delte hist
    // lastbin

    
    // gets indicies
    unsigned int j;
    unsigned int i;
    double threshold = 1400e+3; //TODO: move to settings file
    std::vector<int> Event;
    std::vector<int> Mult;
    double tdiff;
    while(i < tree1_entries - chunkSize){
        Event.push_back(i);
        j = 1;
        tdiff = 0;
        while (j<chunkSize && tdiff<=threshold){
            tdiff = timeStamp_array[i+j] - timeStamp_array[i];

            if(tdiff <= threshold){

                j++;  
            }
        }
        i=i+j;
        Mult.push_back(j);

    }

    std::cout << "Event.size() == "<<Event.size()<<std::endl;
    for(long unsigned int i=0;i<Event.size();i++){

        int eventIndex = Event[i];
        int eventMult = Mult[i];


  
        bool valueSet=false;        
        for(int j=0;j<eventMult;j++){
            int treeIndex = eventIndex;


            inputStream->getTree()->GetEntry(treeIndex);



            double gain = calibrator->getGain(Board,  Channel );
            double offset = calibrator->getOffset(Board, Channel);


            outData->setPressure(1.0); 
            if(!valueSet)outData->setThreshold(threshold); 
            if(!valueSet)outData->setHitNumber(eventMult);

            outData->addChannel(Channel);
            outData->addTimeStamp(Timestamp);
            outData->addBoard(Board);
            outData->addEnergyLong(Energy);
            outData->addEnergyShort(EnergyShort);
            outData->addEnergyLongCal(Energy*gain+offset);
            outData->addEnergyShortCal(EnergyShort*gain+offset);


            eventIndex = treeIndex + 1;
            valueSet=true;
        }


        outputStream->getTree()->Fill();
        outData->Clear();


    }






    /*
    for (unsigned long int i = 0; i < tree1_entries; i++) {
        
        // get from inTree
        inputStream->getTree()->GetEntry(i);

        // apply sort logic

        //for loop
            //std::cout << Channel <<std::endl;
            //std::cout << Timestamp <<std::endl;
            //std::cout << Channel <<std::endl;
            //std::cout << Channel <<std::endl;

        

        //




        int hit = 2;   


        // write to Sorted Class
        outData->setPressure(10.0); 
        //outData->setHitNumber(hit); 
        //setThreshold->setHitNumber(100);
        //
        //for(int i = 0 ; i <hit; i++){
//
        //    outData->addChannel(32430)
        //    outData->addTimeStamp(3430)
        //    outData->addBoard(340)
        //    outData->addEnergyLong(550)
        //    outData->addEnergyShort(550)
        //    outData->addEnergyLongCal(3)
        //    outData->addEnergyShortCal(1)
//
        //}


        

        // write to out tree
        outputStream->getTree()->Fill();
        

        //clear Sorted Class
        outData->Clear();
    }
    */

    return;

}

void saveSingles() {

    outputStream->getTFile()->mkdir("singles/Pside");
    outputStream->getTFile()->mkdir("singles/Nside");

    TH1F* h1_Pside_singles_raw = new TH1F("h1_Pside_singles_raw", "h1_Pside_singles_raw 1", 2000, 0, 10000);
    TH1F* h1_Pside_singles_cal = new TH1F("h1_Pside_singles_cal", "h1_Pside_singles_cal 1", 2000, 0, 10000);
    
    TH1F* h1_Nside_singles_raw = new TH1F("h1_Nside_singles_raw", "h1_Nside_singles_raw 2", 2000, 0, 10000);
    TH1F* h1_Nside_singles_cal = new TH1F("h1_Nside_singles_cal", "h1_Nside_singles_cal 2", 2000, 0, 10000);

    TH2F *h2_Pside_singles_raw = new TH2F("h2_Pside_singles_raw","h2_Pside_singles_raw",16,0,15,2000,0,10000);
    TH2F *h2_Pside_singles_cal = new TH2F("h2_Pside_singles_cal","h2_Pside_singles_cal",16,0,15,2000,0,10000);
    
    TH2F *h2_Nside_singles_raw = new TH2F("h2_Nside_singles_raw","h2_Nside_singles_raw",16,0,15,2000, 0, 10000);
    TH2F *h2_Nside_singles_cal = new TH2F("h2_Nside_singles_cal","h2_Nside_singles_cal",16,0,15,2000, 0, 10000);

    unsigned int tree1_entries = inputStream->getTree()->GetEntries();

    for (unsigned long int i = 0; i < tree1_entries; i++) {

        inputStream->getTree()->GetEntry(i);
        //inputStream->getTree()->Scan();
        //std::cout<<Energy << " , " <<Channel<< " , "<<Board<< " , "<<Timestamp<< std::endl;

        double gain = calibrator->getGain(Board,  Channel );
        double offset = calibrator->getOffset(Board, Channel);

        if(Board==0){
            h1_Pside_singles_raw->Fill(Energy);
            h1_Pside_singles_cal->Fill(Energy*gain+offset);
            h2_Pside_singles_raw->Fill(Channel,Energy);
            h2_Pside_singles_cal->Fill(Channel,Energy*gain+offset);

        }
        if(Board==1){
            
            h1_Nside_singles_raw->Fill(Energy);
            h1_Nside_singles_cal->Fill(Energy*gain+offset);
            h2_Nside_singles_raw->Fill(Channel,Energy);
            h2_Nside_singles_cal->Fill(Channel,Energy*gain+offset);
        }
    
    
    }


    outputStream->getTFile()->cd("singles/Pside");
    h1_Pside_singles_raw->Write();
    h1_Pside_singles_cal->Write();
    h2_Pside_singles_raw->Write();
    h2_Pside_singles_cal->Write();

    outputStream->getTFile()->cd("singles/Nside");
    h1_Nside_singles_raw->Write();
    h1_Nside_singles_cal->Write();
    h2_Nside_singles_raw->Write();
    h2_Nside_singles_cal->Write();
        
    delete h1_Pside_singles_raw;
    delete h1_Pside_singles_cal;
    delete h1_Nside_singles_raw;
    delete h1_Nside_singles_cal;

    delete h2_Pside_singles_raw;
    delete h2_Pside_singles_cal;
    delete h2_Nside_singles_raw;
    delete h2_Nside_singles_cal;


    return;
}



