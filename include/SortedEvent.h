#ifndef SORTED_EVENT_H
#define SORTED_EVENT_H

// ROOT include.
#include <TROOT.h>
// C++ include.
#include <vector>
#include <string>

// Define the SortedEvent class
class SortedEvent {
public:
    SortedEvent();
    virtual ~SortedEvent() {}
    void Clear();

    void setPressure(double p) { pressure = p; }
    void setHitNumber(int hn) { hitNumber = hn; }
    void setThreshold(int th) { threshold = th; }
    
    void addChannel(UShort_t ch) { Channel.push_back(ch); }
    void addTimeStamp(ULong64_t ts) { TimeStamp.push_back(ts); }
    void addBoard(UShort_t bd) { Board.push_back(bd); }
    void addEnergyLong(UShort_t el) { Energy_long.push_back(el); }
    void addEnergyShort(UShort_t es) { Energy_short.push_back(es); }
    void addEnergyLongCal(UShort_t elc) { Energy_long_cal.push_back(elc); }
    void addEnergyShortCal(UShort_t esc) { Energy_short_cal.push_back(esc); }

private:
     
    bool checkVectorLengths() const;

    double pressure;
    int hitNumber;
    int threshold;
    std::vector<UShort_t> Channel;
    std::vector<ULong64_t> TimeStamp;
    std::vector<UShort_t> Board;
    std::vector<UShort_t> Energy_long;
    std::vector<UShort_t> Energy_short;
    std::vector<UShort_t> Energy_long_cal;
    std::vector<UShort_t> Energy_short_cal;

    ClassDef(SortedEvent, 1);

};

#endif // SORTED_EVENT_H
