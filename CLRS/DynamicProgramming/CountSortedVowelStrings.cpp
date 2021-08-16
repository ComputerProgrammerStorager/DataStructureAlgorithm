/*
Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.

A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.

 

Example 1:

Input: n = 1
Output: 5
Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
Example 2:

Input: n = 2
Output: 15
Explanation: The 15 sorted strings that consist of vowels only are
["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.
Example 3:

Input: n = 33
Output: 66045
 

Constraints:

1 <= n <= 50 
*/

// dynamic programming, for each position, we could reach it from five different cases ending with the five vowels, respectively. 
// Since it needs to be lexicographically sorted, then the only valid cases for the current position are from preceeding cases whose ending vowels come before the considered vowel 
// let dp[i][c] represent the number of satisfied string ending with vowel c, then the transfer equation is:
// dp[i][c] += dp[i-1][x] for every x <= c. 
class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n,vector<int>(5,0));
        int res = 0;
        for ( int i = 0; i < 5; i++ )
            dp[0][i] = 1;
        for ( int i = 1; i < n; i++ )
        {
            for ( int j = 0; j < 5; j++ )
            {
                for ( int k = 0; k <= j; k++ )
                    dp[i][j] += dp[i-1][k];
            }
        }
        
        for ( int i = 0; i < 5; i++ )
            res += dp[n-1][i];
        return res;
    }
};

// We can also use backtracking method to calculate the result
class Solution {
public:
    int countVowelStrings(int n) {
        return helper(n,0);
    }
    
    int helper( int n, int cur_vowel )
    {
        int res = 0;
        if ( n == 0 )
            return 1;
        for ( int i = cur_vowel; i < 5; i++ )
            res += helper(n-1,i);
        return res;
    }
};

// observing the pattern: 
// for any position, we could use either use a certain char (i.e., then we still have all available choices for the preceeding positions) or we could choose not to use 
// that char ( i.e., we will to need to construct up to this position using the chars excluding this one).
// base cases are easy to understand. 
class Solution {
public:
    int countVowelStrings(int n) {
        return helper(n,5);
    }
    
    int helper( int n, int num_vowels )
    {
        if ( n == 1 )
            return num_vowels;
        if ( num_vowels == 1 )
            return 1;
        return helper(n,num_vowels-1) + helper(n-1,num_vowels);
    }
};

// using math: it's actually the number of combinations selecting 5 out of n. 
// Note: those combinations can be sorted lexicographically 
class Solution {
public:
    int countVowelStrings(int n) {
        return (n+4)*(n+3)*(n+2)*(n+1) / 24;
    }
};