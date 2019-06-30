#ifndef __jch_AlgStats_hpp__
#define __jch_AlgStats_hpp__

#include <vector>

/**
 * @brief Structure containing data for one test iteration of an algorithm.
 * 
 */
struct StatsEntry {
public:
    StatsEntry() {};
    StatsEntry(size_t n, size_t b, size_t m, size_t w);

public:
    size_t mNumOfElements;
    size_t mBestCaseTime;
    size_t mMidCaseTime;
    size_t mWorstCaseTime;
};


/**
 * @brief Class containing the results of tested sorting algorithm.
 * 
 */
class AlgStats {
public:
    /**
     * @brief Construct a new Alg Stats object
     * 
     */
    AlgStats() {};

    /**
     * @brief Destroy the Alg Stats object
     * 
     */
    ~AlgStats();
    
    /**
     * @brief Method adds the entry e to the mHistory vector.
     * 
     */ 
    void Add(StatsEntry* e);

    /**
     * @biref Method returns a reference on the mHistory vector.
     * 
     */
    const std::vector<StatsEntry*>& GetHistory() const;

private:
    std::vector<StatsEntry*> mHistory = {};
};

#endif