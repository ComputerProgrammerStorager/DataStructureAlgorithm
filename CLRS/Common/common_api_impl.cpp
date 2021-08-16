#include "common_api.h"

//void GenerateVectorNumber( vector<int> &vec, array_size_order scale = TENS_SZ, bool unique = true)
void GenerateVectorNumber( vector<int> &vec, array_size_order scale, bool unique)
{
    long Mod = ONE_HUNDRED, n;
    unordered_set<int> s; 
    switch ( scale )
    {
        case TENS_SZ:
            Mod = ONE_HUNDRED;
            break;
        case HUNDREDS_SZ:
            Mod = ONE_THOUSAND;
            break;
        case THOUSANDS_SZ:
            Mod = TEN_THOUSAND;
            break;
        case MILLIOONS_SZ:
            Mod = ONE_HUNDRED_MILLIONS;
            break;
    }
    srand( time(nullptr) );
    n = rand() % Mod;
    if ( unique )
    {
        while ( s.size() < n )
        {
            s.insert((rand() % Mod ));
        }
        vec = vector<int>(s.begin(),s.end());
    }
    else {
        for ( long i = 0; i < n; i++ )
        {
            vec.push_back((rand()%Mod));
        }
    }
#ifdef DEBUG_OUT 
    cout << "Generate " << n << " numbers for the test " << endl;
#endif 
}

void PrintVector( const vector<int> &vec )
{
    long n = vec.size(), i;
    cout << "[";
    for ( i = 0; i < n-1; i++ )
    {
        if ( i != 0 && i % PRINT_NUM_LINE_SZ == 0 )
        {
            cout << endl;
        }
        cout << vec[i] << ",";
    }

    if ( n != 0 )
    {
        if ( i % PRINT_NUM_LINE_SZ == 0 )
            cout << endl;
        cout << vec[i];
    }
    cout << "]" <<endl;
}

void PrintVector2(const vector<vector<int>> &v )
{
    int r = v.size(), c = v[0].size();
    if  ( r == 0 || c == 0 )
    {
        cout << "[]" << endl;
        return ;
    }
    for ( int i = 0; i < r; i++ )
    {
        int j;
        cout << "[";
        for ( j = 0; j < c-1; j++ )
        {
            cout << v[i][j] <<",";
        }
        cout << v[i][j] << "]" << endl;
    }
    cout << endl;
}

bool VectorIsSorted( vector<int> const& v, bool NonDescreasingOrder )
{
    int n = v.size(), i;
    if ( n < 2 )
        return true;
    for ( i = 1; i < n; i++ )
    {
        if ( NonDescreasingOrder && v[i-1] > v[i] ) 
        {
            break;
        }
        else if ( !NonDescreasingOrder && v[i-1] < v[i] )
        {
            break;
        }
    }
    return i == n;
}