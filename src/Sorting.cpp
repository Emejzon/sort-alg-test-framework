#include "Sorting.hpp"

AbstractSort::AbstractSort(std::string name) : mName(name) {}

AbstractSort::~AbstractSort() {}

void AbstractSort::SetArray(std::vector<int> newArr) {
    mArray = newArr;
}

const std::vector<int>& AbstractSort::GetArray() const {
    return mArray;
}

bool AbstractSort::isSorted() const {
    return std::is_sorted(mArray.begin(),mArray.end());
}

void AbstractSort::PrintArray() const {
    for (auto const & val: mArray)
        std::cout << val << " ";
    std::cout << std::endl;
}

void AbstractSort::AddMidCaseTime(size_t t) {
    mMidCaseTmp.push_back(t);
}

void AbstractSort::AddBestCaseTime(size_t t) {
    mTempStats.mBestCaseTime = t;
}

void AbstractSort::AddWorstCaseTime(size_t t) {
    mTempStats.mWorstCaseTime = t;
}

void AbstractSort::PushStats(size_t n) {
    mTempStats.mNumOfElements = n;
    mTempStats.mMidCaseTime = GetMidMidCase();

    mHist.Add(new StatsEntry(mTempStats));
    mMidCaseTmp.clear();
}

std::string AbstractSort::GetName() const {
    return mName;
}

const AlgStats& AbstractSort::GetStats() const {
    return mHist;
}

size_t AbstractSort::GetMidMidCase() {
    std::sort(mMidCaseTmp.begin(), mMidCaseTmp.end());
    return mMidCaseTmp[mMidCaseTmp.size()/2];
}

MergeSort::MergeSort() : AbstractSort("Merge Sort") {}

void MergeSort::Sort() {
    MergeSortRec(mArray, 0, mArray.size() - 1);
}

void MergeSort::Merge(std::vector<int>& arr, int l, int m, int r) {
    uint i, j, k; 
    uint n1 = m - l + 1; 
    uint n2 =  r - m;
  
    // new tmp vectors
    std::vector<int> L,R;
  
    // copy data
    for (i = 0; i < n1; i++) 
        L.push_back(arr[l + i]); 
    for (j = 0; j < n2; j++) 
        R.push_back(arr[m + 1+ j]); 
  
    // merge
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void MergeSort::MergeSortRec(std::vector<int>& arr, int l, int r) {
    if (l < r) { 
        int m = l+(r-l)/2;  
        // Sort first and second halves 
        MergeSortRec(arr, l, m); 
        MergeSortRec(arr, m+1, r); 
  
        Merge(arr, l, m, r); 
    } 
}

MtMergeSort::MtMergeSort(uint th) :
    AbstractSort("Merge Sort (mt"+std::to_string(th)+")"), mMaxThreads(th) {}


void MtMergeSort::Sort() {
    MtMergeSortRec(mArray, 0, mArray.size()-1);
}

void MtMergeSort::MtMerge(std::vector<int>& arr, int l, int m, int r) {
    uint i, j, k; 
    uint n1 = m - l + 1; 
    uint n2 =  r - m;
  
    // new tmp vectors
    std::vector<int> L,R;
  
    // copy data
    for (i = 0; i < n1; i++) 
        L.push_back(arr[l + i]); 
    for (j = 0; j < n2; j++) 
        R.push_back(arr[m + 1+ j]); 
  
    // merge
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void MtMergeSort::MtMergeSortRec(std::vector<int>& arr, int l, int r) {
    thread_cnt++;
    if (l < r) { 
        int m = l+(r-l)/2;  
        // Sort first and second halves 
        if (thread_cnt >= mMaxThreads) {
            MtMergeSortRec(arr, l, m); 
            MtMergeSortRec(arr, m+1, r); 
        } else {
            std::future<void> f = std::async(&MtMergeSort::MtMergeSortRec,
                                             this, std::ref(arr), l, m);
            MtMergeSortRec(arr, m+1, r); 
            f.wait();
        }
        MtMerge(arr, l, m, r); 
    } 
    thread_cnt--;
}

QuickSort::QuickSort(int pt) :
    AbstractSort("Quick Sort (pivotType "+ std::to_string(pt)+ ")"),
    mPivotType(pt) {}

void QuickSort::Sort() {
    QuickSortRec(mArray, 0, mArray.size() - 1);
}

int QuickSort::Partition(std::vector<int>& arr, int l, int h) {
    int pivot = GetPivot(arr, l, h);    // pivot value
    int i = (l - 1);  // Index of smaller element 
  
    for (int j = l; j <= h- 1; j++) { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) { 
            i++;    // increment index of smaller element 
            iter_swap(arr.begin() + i, arr.begin() + j);
            // arr.swap()swap(&arr[i], &arr[j]); 
        } 
    } 
    iter_swap(arr.begin() + i + 1, arr.begin() + h);
    return (i + 1); 
}

int QuickSort::GetPivot(std::vector<int>& arr, int l, int h) {
    switch (mPivotType) {
        case 0:
            return arr[h];
        case 1:
            return MidOfThree(arr[l+1], arr[(l + h)/2], arr[h]);
        default:
            return arr[h];
    }
}

int QuickSort::MidOfThree(int a, int b, int c) {
		if(a<=b && b<=c)
            return b;
        if(b<=a && a<=c)
            return a;
        if(a<=c && c<=b)
            return c;
        return -1;
}

void QuickSort::QuickSortRec(std::vector<int>& arr, int l, int h) {
    if (l < h) 
    { 
        int pi = Partition(arr, l, h); 
  
        QuickSortRec(arr, l, pi - 1); 
        QuickSortRec(arr, pi + 1, h); 
    } 
}

MtQuickSort::MtQuickSort(uint th) :
    AbstractSort("Quick Sort (mt"+std::to_string(th)+")"), mMaxThreads(th) {}

void MtQuickSort::Sort() {
    MtQuickSortRec(mArray, 0, mArray.size() - 1);
}

int MtQuickSort::MtPartition(std::vector<int>& arr, int l, int h) {
    int pivot = MtMidOfThree(arr[l+1],arr[(l + h)/2],arr[h]);    // pivot 
    int i = (l - 1);  // Index of smaller element 
  
    for (int j = l; j <= h- 1; j++) { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) { 
            i++;    // increment index of smaller element 
            iter_swap(arr.begin() + i, arr.begin() + j);
            // arr.swap()swap(&arr[i], &arr[j]); 
        } 
    } 
    iter_swap(arr.begin() + i + 1, arr.begin() + h);
    return (i + 1); 
}

int MtQuickSort::MtMidOfThree(int a, int b, int c) {
		if(a<=b && b<=c)
            return b;
        if(b<=a && a<=c)
            return a;
        if(a<=c && c<=b)
            return c;
        return -1;
}

void MtQuickSort::MtQuickSortRec(std::vector<int>& arr, int l, int h) {
    thread_cnt++;
    if (l < h) 
    { 
        int pi = MtPartition(arr, l, h); 

        if (thread_cnt >= mMaxThreads) {
            MtQuickSortRec(arr, l, pi - 1);
            MtQuickSortRec(arr, pi + 1, h);
        } else {
            std::future<void> f = std::async(&MtQuickSort::MtQuickSortRec, this, std::ref(arr), l, pi - 1);
            MtQuickSortRec(arr, pi + 1, h);
            f.wait();
        }
    } 
    thread_cnt--;
}

InsertSort::InsertSort() : AbstractSort("Insertion Sort") {}

void InsertSort::Sort() {
    size_t i,j;
    int key; 
    for (i = 1; i < mArray.size(); i++) { 
        key = mArray[i]; 
        j = i - 1; 
        while (j >= 0 && mArray[j] > key) { 
            mArray[j + 1] = mArray[j]; 
            j = j - 1; 
        } 
        mArray[j + 1] = key; 
    } 
}