#include "analyzer.h"
#include <iostream>
#include <algorithm>
 
using namespace std;
 
void TripAnalyzer::ingestStdin() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    string line;
    line.reserve(256);
 
    if (!getline(cin, line)) return;
 
    zoneCounts.reserve(200000);
    slotCounts.reserve(400000);
 
    while (getline(cin, line)) {
        if (line.empty()) continue;
 
        const char* s = line.c_str();
        int len = line.size();
        int comma[6], c = 0;
 
        for (int i = 0; i < len && c < 6; i++) {
            if (s[i] == ',') comma[c++] = i;
        }
 
        if (c < 5) continue;
 
        // Extract zone between comma[0] and comma[1]
        int zStart = comma[0] + 1;
        int zEnd = comma[1];
 
        // Trim spaces
        while (zStart < zEnd && s[zStart] == ' ') zStart++;
        while (zEnd > zStart && s[zEnd - 1] == ' ') zEnd--;
 
        if (zStart >= zEnd) continue;
 
        // Find colon after comma[2] for the hour extraction
        int colon = -1;
        for (int i = comma[2] + 1; i < len; i++) {
            if (s[i] == ':') {
                colon = i;
                break;
            }
        }
 
        if (colon < 2) continue;
 
        char h1 = s[colon - 2];
        char h2 = s[colon - 1];
 
        if (h1 < '0' || h1 > '9' || h2 < '0' || h2 > '9') continue;
 
        int hour = (h1 - '0') * 10 + (h2 - '0');
        if (hour > 23) continue;
 
        string zone(s + zStart, zEnd - zStart);
        zoneCounts[zone]++;
        slotCounts[{zone, hour}]++;
    }
}
 
vector<ZoneCount> TripAnalyzer::topZones(int k) const {
    vector<ZoneCount> v;
    v.reserve(zoneCounts.size());
    for (const auto& p : zoneCounts)
        v.push_back({p.first, p.second});
 
    int n = min(k, (int)v.size());
    partial_sort(v.begin(), v.begin() + n, v.end(),
        [](const ZoneCount& a, const ZoneCount& b) {
            if (a.count != b.count) return a.count > b.count;
            return a.zone < b.zone;
        });
 
    v.resize(n);
    return v;
}
 
vector<SlotCount> TripAnalyzer::topBusySlots(int k) const {
    vector<SlotCount> v;
    v.reserve(slotCounts.size());
    for (const auto& p : slotCounts)
        v.push_back({p.first.zone, p.first.hour, p.second});
 
    int n = min(k, (int)v.size());
    partial_sort(v.begin(), v.begin() + n, v.end(),
        [](const SlotCount& a, const SlotCount& b) {
            if (a.count != b.count) return a.count > b.count;
            if (a.zone != b.zone) return a.zone < b.zone;
            return a.hour < b.hour;
        });
 
    v.resize(n);
    return v;
}
