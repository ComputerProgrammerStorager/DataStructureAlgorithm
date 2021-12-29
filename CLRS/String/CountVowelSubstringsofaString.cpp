/*
A substring is a contiguous (non-empty) sequence of characters within a string.

A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.

Given a string word, return the number of vowel substrings in word.

 

Example 1:

Input: word = "aeiouu"
Output: 2
Explanation: The vowel substrings of word are as follows (underlined):
- "aeiouu"
- "aeiouu"
Example 2:

Input: word = "unicornarihan"
Output: 0
Explanation: Not all 5 vowels are present, so there are no vowel substrings.
Example 3:

Input: word = "cuaieuouac"
Output: 7
Explanation: The vowel substrings of word are as follows (underlined):
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
Example 4:

Input: word = "bbaeixoubb"
Output: 0
Explanation: The only substrings that contain all five vowels also contain consonants, so there are no vowel substrings.
 

Constraints:

1 <= word.length <= 100
word consists of lowercase English letters only.

*/

// consider each position as the start index of any possible substring 
class Solution {
public:
    int countVowelSubstrings(string word) {
        int n = word.size(), cnt = 0;
        unordered_set<char> vowels = {'a','e','i','o','u'};
        for ( int start = 0; start < n; start++ )
        {
            unordered_set<char> s;
            for ( int end = start; end < n; end++ )
            {
                if ( vowels.count(word[end]) )
                {
                    s.insert(word[end]);
                    if ( s.size() == 5 )
                        cnt++;
                }
                else
                    break;
            }
        }
        
        return cnt;
    }
};

// sometimes it's hard to calculate how many vowels are within a window, and it's easier to calculate the possibilities of having maximum vowels 
class Solution {
public:
    int countVowelSubstrings(string word) {
        return hasMostkVowels(word,5) - hasMostkVowels(word,4);
    }
private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'o' || c == 'i' || c == 'u';
    }
    
    int hasMostkVowels(string word, int k)
    {
        int n = word.size(), l = 0, ans = 0;
        unordered_map<char,int> win;
        for ( int r = 0; r < n; r++ )
        {
            if ( !isVowel(word[r]) )
            {
                win.clear();
                l = r + 1;
                continue;
            }
            win[word[r]]++;
            while( win.size() > k )
            {
                if ( --win[word[l]] == 0 )
                    win.erase(word[l]);
                l++;
            }
            ans += r-l+1;
        }
        
        return ans;
    }
};