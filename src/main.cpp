#include <iostream>
#include <ctime>

#include "src/TesterFramework.hpp"
#include "src/Sorting.hpp"


using namespace std;
/** \mainpage Sorting Algorithm Experimental Tester
 *
 * \section intro_sec Introduction
 *
 * This is documentation to a simple testing framework for sorting algoritms.
 *
 */

/**
 * @brief Main function of the tester.
 * 
 */
int main(/*int argc, char const *argv[]*/) {
    srand(time(NULL));
    TesterFramework tester = TesterFramework();
    // tester.AddAlg(make_unique<InsertSort>());

    // tester.AddAlg(make_unique<MergeSort>());
    // tester.AddAlg(make_unique<MtMergeSort>(2));
    // tester.AddAlg(make_unique<MtMergeSort>(3));
    // tester.AddAlg(make_unique<MtMergeSort>(4));

    // tester.AddAlg(make_unique<QuickSort>(0));
    // tester.AddAlg(make_unique<QuickSort>(1));

    // tester.AddAlg(make_unique<QuickSort>(1));
    // tester.AddAlg(make_unique<MtQuickSort>(2));
    // tester.AddAlg(make_unique<MtQuickSort>(3));
    // tester.AddAlg(make_unique<MtQuickSort>(4));

    // tester.AddAlg(make_unique<MtMergeSort>(3));
    // tester.AddAlg(make_unique<QuickSort>(1));

    tester.AddAlg(make_unique<MtMergeSort>(4));
    tester.AddAlg(make_unique<MtQuickSort>(4));

    tester.StartTests();
    return 0;
}
