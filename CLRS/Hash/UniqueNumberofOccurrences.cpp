/*
Given an array of integers arr, write a function that returns true if and only if the number of occurrences of each value in the array is unique.

Example 1:

Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
Example 2:

Input: arr = [1,2]
Output: false
Example 3:

Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true
 

Constraints:

1 <= arr.length <= 1000
-1000 <= arr[i] <= 1000
*/

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> m;
        unordered_map<int,int> m2;
        for ( int n : arr )
        {
            m[n]++;
        }
        
        for ( auto it = m.begin(); it != m.end(); it++ )
        {
            m2[it->second]++;
        }
        
        for ( auto it = m2.begin(); it != m2.end(); it++ )
        {
            if ( it->second != 1 )
                return false;
        }
        
        return true;
    }
};

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> m;
        set<int> s;
        multiset<int> ms;
        for ( int n : arr )
        {
            m[n]++;
        }
        
        for ( auto it = m.begin(); it != m.end(); it++ )
        {
            s.insert(it->second);
            ms.insert(it->second);
        }
        
        if ( s.size() != ms.size() )
            return false;
        
        return true;
    }
};

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> m;
        vector<int> vec;
        for ( int n : arr )
        {
            m[n]++;
        }
        
        for ( auto it = m.begin(); it != m.end(); it++ )
        {
            vec.push_back(it->second);
        }
        
        sort(vec.begin(),vec.end());
        
        for ( int i = 0; i < vec.size() - 1; i++ )
            if ( vec[i] == vec[i+1] )
                return false;
        return true;
    }
};