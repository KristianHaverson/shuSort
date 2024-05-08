#include "SortedEvent.h"

ClassImp(SortedEvent); 

SortedEvent::SortedEvent() {
    // Constructor implementation here
}

//SortedEvent::~SortedEvent() {}



bool SortedEvent::checkVectorLengths() const {
    // Get the length of the first vector
    size_t expectedLength = Channel.size();

    // Check the length of each vector against the expected length
    if (TimeStamp.size() != expectedLength ||
        Board.size() != expectedLength ||
        Energy_long.size() != expectedLength ||
        Energy_short.size() != expectedLength ||
        Energy_long_cal.size() != expectedLength ||
        Energy_short_cal.size() != expectedLength) {
        return false;
    }
    
    return true;
}


void SortedEvent::Clear() {
    // Clear vectors
    Channel.clear();
    TimeStamp.clear();
    Board.clear();
    Energy_long.clear();
    Energy_short.clear();
    Energy_long_cal.clear();
    Energy_short_cal.clear();

    // Clear scalar member variables
    pressure = -999.0;  // Set to a default value, e.g., -999.0
    hitNumber = -999;   // Set to a default value, e.g., -999
    threshold = -999;   // Set to a default value, e.g., -999
}