#ifndef __jch_TesterFramework_hpp__
#define __jch_TesterFramework_hpp__

#include <iostream>
#include <memory>
#include <chrono>
#include <fstream>

#include "Sorting.hpp" 

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

/**
 * @brief Framework for testing sortin algorithms.
 * 
 */
class TesterFramework {
public:
    /**
     * @brief Construct a new TesterFramework object
     * 
     */
    TesterFramework() {};

    /**
     * @brief Adds an algorithm object to the algorithm vector.
     * 
     * @param alg_ptr - unique pointer to the algorithm object
     */
    void AddAlg(std::unique_ptr<AbstractSort> alg_ptr);

    /**
     * @brief Starts the whole testing process with given parameters.
     * 
     * @param max_elements - factor of vector lenght generation
     * @param repeat_test - number test repetitions to get a time average
     * @param arrays_tested - number of uniqie vectors tested for middle case scenario
     */
    void StartTests(size_t max_elements = 15, size_t repeat_test = 1000,
                    size_t arrays_tested = 3);

private:
    /**
     * @brief Generates a new random vector for testing.
     * 
     * @param len - lenght of the generated vector
     */
    void GenerateArray(int len);

    /**
     * @brief Runs the middle case scenario sorting test
     * 
     * @param alg - tested algorithm
     * @param rep - number test repetitions to get a time average
     */
    void TestMidCase(std::unique_ptr<AbstractSort>& alg, size_t rep);

    /**
     * @brief Runs the best case scenario sorting test
     * 
     * @param alg - tested algorithm
     * @param rep - number test repetitions to get a time average
     */
    void TestBestCase(std::unique_ptr<AbstractSort>& alg, size_t rep);
    
    /**
     * @brief Runs the worst case scenario sorting test
     * 
     * @param alg - tested algorithm
     * @param rep - number test repetitions to get a time average
     */
    void TestWorstCase(std::unique_ptr<AbstractSort>& alg, size_t rep);

    /**
     * @brief Exports the testing history into a csv file for further analysis
     * 
     */
    void ExportData();
    
private:
    /**
     * @brief Vector of algorithm objects we want to test.
     * 
     */
    std::vector<std::unique_ptr<AbstractSort>> mAlgs;

    /**
     * @brief Original vector tested in current iteration.
     * 
     */
    std::vector<int> mArray;

    /**
     * @brief Sorted copy of mArray vector.
     * 
     */
    std::vector<int> mSorted;
};

#endif