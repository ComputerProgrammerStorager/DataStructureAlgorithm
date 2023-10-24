/*
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

 

Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
 

Constraints:

1 <= haystack.length, needle.length <= 104
haystack and needle consist of only lowercase English characters.

*/

// check each possible substring 
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        for ( int i = 0; i <= m-n; i++ )
        {
            int p = i, j = 0;
            while( j < n && haystack[p] == needle[j] )
            {
                p++;
                j++;
            }
            if ( j == n )
                return i;
        }

        return -1;
    }
};

// Use rolling hash 
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = needle.size(), n = haystack.size();
        if ( n < m )
          return -1;
        int RADIX = 26;
        long max_weight = 1, MOD = 1000000033;

        for ( int i = 0; i < m; i++ ) 
          max_weight = (max_weight*RADIX) % MOD;

          long hashNeedle = hashvalue(needle,RADIX,MOD,m), hashHay = hashvalue(haystack.substr(0,m),RADIX,MOD,m);
          if ( haystack.substr(0,m) == needle )
            return 0;
          for ( int i = 1; i <= n-m; i++ )
          {
            //hashHay = ((hashHay * RADIX) % MOD -((int)(haystack[i-1]-'a')*max_weight) % MOD + (int)(haystack[i+m-1]-'a') + MOD) % MOD;
              hashHay = ((hashHay * RADIX) % MOD - ((int) (haystack[i - 1] - 'a') * max_weight) % MOD
               + (int) (haystack[i + m - 1] - 'a') + MOD) % MOD;
            if ( hashHay == hashNeedle)
            {
              for ( int j = 0; j < m; j++ ){
                if ( needle[j] != haystack[i+j])
                  break;
                if ( j == m-1 )
                  return i;
              }
            }
          }

          return -1;
    }
private:
    int hashvalue(string str, int RADIX, int MOD, int m)
    {
      int ans = 0;
      long factor = 1;
      for ( int i = m-1; i >= 0; i-- )
      {
        ans += ((int)(str[i]-'a')*factor) % MOD;
        factor = (factor * RADIX) % MOD;
      }

      return ans % MOD;
    }
};