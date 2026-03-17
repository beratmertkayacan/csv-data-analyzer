#ifndef ANALYZER_H
#define ANALYZER_H
 
#include <string>
#include <vector>
#include <unordered_map>
 
struct ZoneCount {
    std::string zone;
    long long count;
};
 
struct SlotCount {
    std::string zone;
    int hour;
    long long count;
};
 
struct SlotKey {
    std::string zone;
    int hour;
 
    bool operator==(const SlotKey& o) const {
        return hour == o.hour && zone == o.zone;
    }
};
 
struct SlotHash {
    size_t operator()(const SlotKey& k) const {
        return std::hash<std::string>()(k.zone) ^ (std::hash<int>()(k.hour) << 1);
    }
};
 
class TripAnalyzer {
private:
    std::unordered_map<std::string, long long> zoneCounts;
    std::unordered_map<SlotKey, long long, SlotHash> slotCounts;
 
public:
    void ingestStdin();
    std::vector<ZoneCount> topZones(int k = 10) const;
    std::vector<SlotCount> topBusySlots(int k = 10) const;
};
 
#endif 
