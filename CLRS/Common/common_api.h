// put all the headers here 
#ifndef __COMMON_HEAD_TEST
#define __COMMON_HEAD_TEST

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>
#include <time.h>
#include <set>
#include <unordered_set>
#include <cstring>  // for memset 
#include <queue>
#include <cassert>

// user defined headers
#include "treenode.h"

using namespace std;

#define DEBUG_OUT  1 

const int ONE_HUNDRED = 100;
const int ONE_THOUSAND = 1000;
const int TEN_THOUSAND = 10000;
const int ONE_HUNDRED_MILLIONS = 100000000;

const int PRINT_NUM_LINE_SZ = 20;

enum array_size_order {
    TENS_SZ,
    HUNDREDS_SZ,
    THOUSANDS_SZ,
    MILLIOONS_SZ,
};

// randomly generate n numbers to the vector
void GenerateVectorNumber( vector<int> &vec, array_size_order scale = TENS_SZ, bool unique = true);
void PrintVector( const vector<int> &vec );
void PrintVector2( const vector<vector<int>> &v );
bool VectorIsSorted( vector<int> const& v, bool IncreasingOrder = true );

#endif 