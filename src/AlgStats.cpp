#include "AlgStats.hpp"

StatsEntry::StatsEntry(size_t n, size_t b, size_t m, size_t w) 
    : mNumOfElements(n), mBestCaseTime(b), mMidCaseTime(m), mWorstCaseTime(w) {}

AlgStats::~AlgStats() {
    for (auto const& val: mHistory)
        delete val;
}

void AlgStats::Add(StatsEntry* e) {
    mHistory.push_back(e);
}

const std::vector<StatsEntry*>& AlgStats::GetHistory() const {
    return mHistory;
}