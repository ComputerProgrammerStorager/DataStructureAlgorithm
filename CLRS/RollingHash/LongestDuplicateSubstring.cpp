/*
Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or more times. The occurrences may overlap.

Return any duplicated substring that has the longest possible length. If s does not have a duplicated substring, the answer is "".

 

Example 1:

Input: s = "banana"
Output: "ana"
Example 2:

Input: s = "abcd"
Output: ""
 

Constraints:

2 <= s.length <= 3 * 104
s consists of lowercase English letters.
*/


// check the length using binary search and for each length check existence of dup string using rolling hash 
class Solution {
public:
    string longestDupSubstring(string s) {
        int n = s.size(); 
        if ( n == 0 )
          return "";
        int mod = 1000000007;
        int l = 0, r = n;
        while ( l <= r )
        {
          int m = l + (r-l)/2;
          if ( search(m,s,mod) != -1 )
          {
            l = m+1;
          }
          else 
          {
            r = m-1;
          }
        }

        int start = search(l-1,s,mod);
        return s.substr(start,l-1);
    }
private:
  // return the start index of a subtring of length L if it is duplicate
  int search(int L, const string& s, long mod )
  {
      unordered_map<long,vector<int>> hash2idx;
      long h = 0;
      for ( int i = 0; i < L; i++ )
      {
        h = (h*26 + (s[i]-'a')) % mod;
      }

      hash2idx[h].push_back(0);
      long a2L = 1;
      for ( int i = 1; i <= L; i++ )
      {
        a2L = (a2L * 26) % mod;
      }

      for ( int start = 1; start < s.size()-L+1; start++ )
      {
          h = (h*26 - ((s[start-1]-'a') * a2L % mod) + mod) % mod;
          h = (h+(s[start+L-1]-'a')) % mod;

          if ( hash2idx.count(h) != 0 )
          {
            for ( auto idx : hash2idx[h] )
            {
              if ( s.substr(start,L) == s.substr(idx,L) )
              {
                return idx;
              }
            }
          }
        hash2idx[h].push_back(start);
      }
      return -1;
  }
};