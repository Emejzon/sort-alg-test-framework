#ifndef __jch_Sorting_hpp__
#define __jch_Sorting_hpp__

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <future>
#include <cassert>

#include "AlgStats.hpp"

/**
 * @brief Abstract function for sorting algorithms supported by our Testing Framework.
 * 
 */
class AbstractSort {
public:
    /**
     * @brief Construct a new AbstractSort object
     * 
     * @param name - printable name of the algorithm
     */
    AbstractSort(std::string name);

    /**
     * @brief Destroy the AbstractSort object
     * 
     */
    virtual ~AbstractSort() = 0;

    /**
     * @brief Set the mArray vector
     * 
     * @param newArr - new array (vector) to be sorted
     */
    void SetArray(std::vector<int> newArr);

    /**
     * @brief Get a reference to mArray vector
     * 
     * @return const std::vector<int>& 
     */
    const std::vector<int>& GetArray() const;

    /**
     * @brief Checks if the mArray vector is sorted
     * 
     * @return true - the vector is sorted
     * @return false - the vector is not sorted
     */
    bool isSorted() const;

    /**
     * @brief Prints the contents of mArray vector to the standart output
     * 
     */
    void PrintArray() const;

    /**
     * @brief Adds the middle case scenario time to the mMidCaseTmp vector. 
     * 
     * @param t - current middle case scenario time
     */
    void AddMidCaseTime(size_t t);

    /**
     * @brief Adds the best case scenario time to the current iteration stats.
     * 
     * @param t - current best case scenario time
     */
    void AddBestCaseTime(size_t t);

    /**
     * @brief Adds the worst case scenario time to the current iteration stats.
     * 
     * @param t - current worst case scenario time
     */
    void AddWorstCaseTime(size_t t);

    /**
     * @brief Ends the current iteration of sorting.
     * Saves the current iteration stats to history and resets the stats.
     * 
     * @param n - number of elements in the array for the current iteration
     */
    void PushStats(size_t n);

    /**
     * @brief Get the mName value
     * 
     * @return std::string - printable name of the sorting algorithm
     */
    std::string GetName() const;

    /**
     * @brief Get a reference to the mHist object
     * 
     * @return const AlgStats& - History of the testing
     */
    const AlgStats& GetStats() const;

    /**
     * @brief Pure virtual function for sorting
     * This function implements the Sorting of the algorithm we want to test.
     */
    virtual void Sort() = 0;

private:
    /**
     * @brief Get the middle value in the mMidCaseTmp vector
     * 
     * @return size_t - middle case scenario time
     */
    size_t GetMidMidCase();

public:
    std::vector<int> mArray = {};

private:
    std::string mName;
    AlgStats mHist;
    StatsEntry mTempStats;
    std::vector<size_t> mMidCaseTmp = {};
};

/**
 * @brief Simple recursive merge sort algorithm implementation
 * 
 */
class MergeSort : public AbstractSort {
public:
    /**
     * @brief Construct a new MergeSort object
     * 
     */
    MergeSort();

    /**
     * @brief Implements the merge sort algorithm
     * The method calls the first merge sort recursive call.
     */
    void Sort();

private:
    /**
     * @brief Merge two sorted partitions into one.
     * 
     * @param arr - vector being sorted
     * @param l - left boundary index of the merged partition
     * @param m - middle element index of the merged partition
     * @param r - right boundary index of the merged partition
     */
    void Merge(std::vector<int>& arr, int l, int m, int r);

    /**
     * @brief Recursive call for merge sort.
     * 
     * @param arr - vector being sorted
     * @param l - left boundary index of a partition being sorted
     * @param r - right boundary index of a partition being sorted
     */
    void MergeSortRec(std::vector<int>& arr, int l, int r);
};

/**
 * @brief Multithread merge sort algorithm implementation.
 * 
 */
class MtMergeSort : public AbstractSort {
public:
    /**
     * @brief Construct a new MtMergeSort object
     * 
     * @param th - number of available threads
     */
    MtMergeSort(uint th);

    /**
     * @brief Implements the multithread merge sort algorithm
     * The method calls the first multithread merge sort recursive call.
     */
    void Sort();

private:
    /**
     * @brief Merge two sorted partitions into one.
     * 
     * @param arr - vector being sorted
     * @param l - left boundary index of the merged partition
     * @param m - middle element index of the merged partition
     * @param r - right boundary index of the merged partition
     */
    void MtMerge(std::vector<int>& arr, int l, int m, int r);

    /**
     * @brief Recursive call for multithread merge sort.
     * Method splits current partition into two new partitions. 
     * If there are no additional threads available, sort
     * the partitions in the current thread. If there is
     * an additional thread available, use it for the first
     * partition and sort the second one on the current
     * thread.
     * 
     * @param arr - vector being sorted
     * @param l - left boundary index of a partition being sorted
     * @param r - right boundary index of a partition being sorted
     */
    void MtMergeSortRec(std::vector<int>& arr, int l, int r);

private:
    uint mMaxThreads;

    /**
     * @brief Number of threads currently being used.
     * 
     */
    std::atomic<uint> thread_cnt = 0;
};

/**
 * @brief Simple recursive quick sort algorithm implementation.
 * 
 */
class QuickSort : public AbstractSort {
public: 
    /**
     * @brief Construct a new QuickSort object
     * Pivot type 0: Select last element as a pivot
     * Pivot type 1: Select middle value from the first,
     * middle, and the last element.
     * 
     * @param pt - pivot selection type
     */
    QuickSort(int pt);

    /**
     * @brief Implements the quick sort algorithm
     * The method calls the first quick sort recursive call.
     * 
     */
    void Sort();

private:
    /**
     * @brief Selects the pivot and create two partitions around it.
     * 
     * @param arr - vector being sorted
     * @param l - low element index (left boundary)
     * @param h - high element index (right boundary)
     * @return int - pivot index
     */
    int Partition(std::vector<int>& arr, int l, int h);

    /**
     * @brief Recursive call for quick sort.
     * 
     * @param arr - vector being sorted
     * @param l - low element index (left boundary)
     * @param h - high element index (right boundary)
     */
    void QuickSortRec(std::vector<int>& arr, int l, int h);

    /**
     * @brief Returns the pivot based on the pivot selection type
     * 
     * @param arr - vector being sorted
     * @param l - low element index (left boundary) 
     * @param h - high element index (right boundary)
     * @return int - pivot value
     */
    int GetPivot(std::vector<int>& arr, int l, int h);

    /**
     * @brief Returns the middle value of the given three values.
     * 
     * @param a - first value
     * @param b - second value
     * @param c - third value
     * @return int - middle value out of a,b,c value
     */
    int MidOfThree(int a, int b, int c);

private:
    int mPivotType;
};

/**
 * @brief Multithread quick sort algorithm implementation.
 * 
 */
class MtQuickSort : public AbstractSort {
public: 
    /**
     * @brief Construct a new MtQuickSort object
     * 
     * @param th - number of available threads
     */
    MtQuickSort(uint th);
    
    /**
     * @brief Implements the multithread quick sort algorithm
     * The method calls the first multithread quick sort recursive call.
     */
    void Sort();

private:
    /**
     * @brief Selects the pivot and create two partitions around it.
     * 
     * @param arr - vector being sorted
     * @param l - low element index (left boundary)
     * @param h - high element index (right boundary)
     * @return int - pivot index
     */
    int MtPartition(std::vector<int>& arr, int l, int h);

    /**
     * @brief Recursive call for multithread quick sort.
     * Method calls MtPartition method. If there are no
     * additional threads available, sort the partitions
     * in the current thread. If there is an additional
     * thread available, use it for the first partition
     * and sort the second one on the current thread.
     * 
     * @param arr - vector being sorted
     * @param l - low element index (left boundary)
     * @param h - high element index (right boundary)
     */
    void MtQuickSortRec(std::vector<int>& arr, int l, int h);

    /**
     * @brief Returns the middle value of the given three values.
     * 
     * @param a - first value
     * @param b - second value
     * @param c - third value
     * @return int - middle value out of a,b,c value
     */
    int MtMidOfThree(int a, int b, int c);

private:
    uint mMaxThreads;

    /**
     * @brief Number of threads currently being used.
     * 
     */
    std::atomic<uint> thread_cnt = 0;
};

class InsertSort : public AbstractSort {
public: 
    InsertSort();
    void Sort();
};

#endif