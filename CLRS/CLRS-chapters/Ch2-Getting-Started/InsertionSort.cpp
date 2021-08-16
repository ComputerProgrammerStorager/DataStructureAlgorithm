/*
    Testbook Pseudocode: 
    1   for j <--  2 to length(A)
    2       do key <-- A[j]
    3           <c> Insert A[j] into the sorted sequence A[1..j-1].
    4           i <-- j-1
    5           while i > 0 and A[i] > key 
    6               do A[i+1] <-- A[i]
    7                   i <-- i-1 
    8           A[i+1] = key
*/

// worst case: O(n^2), when the data is reversely sorted 
// Best Case: O(n), when the data is already sorted

#include "../../Common/common_api.h"

void InsertionSortNonDecreasing(vector<int> &A)
{
    int n = A.size();
    if ( n < 2 )
        return;
    for ( int j = 1; j < n; j++ )
    {
        int i = j - 1;
        int key = A[j];
        while ( i >= 0 && A[i] > key )
        {
            A[i+1] = A[i];
            i = i - 1;
        }

        A[i+1] = key;
    }
}

void InsertionSortNonIncreasing(vector<int> &A) 
{
    int n = A.size();
    if ( n < 2 )
        return ;
    for ( int j = 1; j < n; j++ )
    {
        int i = j - 1;
        int key = A[j];
        while ( i >= 0 && A[i] < key )
        {
            A[i+1] = A[i];
            i = i - 1;
        }
        A[i+1] = key;
    }
}

int main()
{
    vector<int> data;
    GenerateVectorNumber(data,TENS_SZ,false);
    string sorted = VectorIsSorted(data) ? "NonIncreasingSorted" : (VectorIsSorted(data,false) ? "NonDecreasingSorted" : "Not Sorted");
    cout << "The data is (before sorting) " << sorted << endl;
    PrintVector(data);
    InsertionSortNonDecreasing(data);
    cout << "The data is after Non descreasing sorting" << endl;
    PrintVector(data);
    assert(VectorIsSorted(data));

    GenerateVectorNumber(data,TENS_SZ,false);
    sorted = VectorIsSorted(data) ? "NonIncreasingSorted" : (VectorIsSorted(data,false) ? "NonDecreasingSorted" : "Not Sorted");
    cout << "The data is (before sorting) " << sorted << endl;
    PrintVector(data);
    InsertionSortNonIncreasing(data);
    cout << "The data is after non increasing sorting" << endl;
    PrintVector(data);
    assert(!VectorIsSorted(data));
}
