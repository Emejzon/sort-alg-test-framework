#include "TesterFramework.hpp"

struct RandomGenerator {
	int maxValue;
	RandomGenerator(int max) : maxValue(max) {}
	int operator()() {return rand() % maxValue;}
};

void TesterFramework::AddAlg(std::unique_ptr<AbstractSort> alg_ptr) {
    mAlgs.push_back(std::move(alg_ptr));
}

void TesterFramework::StartTests(size_t max_elements, size_t repeat_test,
                                 size_t arrays_tested) {
    size_t len = 1;
    for (size_t n = 1; n <= max_elements; n++) {
        len += 2*n*n;
        std::cout << "Testing length: " << n << std::endl;
        for (size_t n_arr = 0; n_arr < arrays_tested; n_arr++) {
            GenerateArray(len);

            for (auto & alg: mAlgs) {
                TestMidCase(alg, repeat_test);

                if (n_arr == 0) {
                    TestBestCase(alg, repeat_test);
                    TestWorstCase(alg, repeat_test);
                } 
            }
        }
        for (auto & alg: mAlgs)
            alg->PushStats(n);
    }

    std::cout << "TESTING DONE!" << std::endl; 
    ExportData();
}

void TesterFramework::GenerateArray(int len) {
    mArray = std::vector<int>(len);
    std::generate(mArray.begin(), mArray.end(), RandomGenerator(2 * len));
}  

void TesterFramework::TestMidCase(std::unique_ptr<AbstractSort>& alg, size_t rep) {
    size_t t = 0; 
    for (size_t i = 0; i < rep; i++) {
        alg->SetArray(mArray);

        time_point<Clock> start = Clock::now();
        alg->Sort();
        time_point<Clock> end = Clock::now();
        
        nanoseconds diff = duration_cast<nanoseconds>(end - start);
        t += diff.count();
    }
    t /= rep;
    // std::cout << "MidCase: " << t << std::endl;
    alg->AddMidCaseTime(t);
}

void TesterFramework::TestBestCase(std::unique_ptr<AbstractSort>& alg, size_t rep) {
    size_t t = 0; 
    mSorted = std::vector<int>(mArray);
    std::sort(mSorted.begin(),mSorted.end());
    alg->SetArray(mSorted);
    for (size_t i = 0; i < rep; i++) {
        time_point<Clock> start = Clock::now();
        alg->Sort();
        time_point<Clock> end = Clock::now();
        
        nanoseconds diff = duration_cast<nanoseconds>(end - start);
        t += diff.count();
    }
    t /= rep;
    // std::cout << "BestCase: " << t << std::endl;
    alg->AddBestCaseTime(t);
}

void TesterFramework::TestWorstCase(std::unique_ptr<AbstractSort>& alg, size_t rep) {
    size_t t = 0; 
    mSorted = std::vector<int>(mArray);
    std::sort(mSorted.begin(),mSorted.end());
    std::reverse(mSorted.begin(), mSorted.end());
    for (size_t i = 0; i < rep; i++) {
        alg->SetArray(mSorted);

        time_point<Clock> start = Clock::now();
        alg->Sort();
        time_point<Clock> end = Clock::now();
        
        nanoseconds diff = duration_cast<nanoseconds>(end - start);
        t += diff.count();
    }
    t /= rep;
    // std::cout << "WorstCase: " << t << std::endl;
    alg->AddWorstCaseTime(t);
}

void TesterFramework::ExportData() {
    std::ofstream csv;
    csv.open ("output-data/results.csv");

    csv << ",n";
    for (auto const & stat: mAlgs[0]->GetStats().GetHistory())
        csv << ',' << stat->mNumOfElements;
    csv << std::endl;

    for (auto & alg: mAlgs) {
        const AlgStats& stats = alg->GetStats();
        for (uint i = 0; i < 3; i++){
            switch (i)
            {
                case 0:
                    csv << alg->GetName() << "," << "Best Case";
                    for (auto const & stat: stats.GetHistory())
                        csv << ',' << stat->mBestCaseTime;
                    csv << std::endl;
                    break;
                case 1:
                    csv << alg->GetName() << "," << "Most Likely Case";
                    for (auto const & stat: stats.GetHistory())
                        csv << ',' << stat->mMidCaseTime;
                    csv << std::endl;
                    break;
                case 2:
                    csv << alg->GetName() << "," << "Worst Case";
                    for (auto const & stat: stats.GetHistory())
                        csv << ',' << stat->mWorstCaseTime;
                    csv << std::endl;
                    break;
                default:
                    break;
            }
        }
    }
    csv.close();
}