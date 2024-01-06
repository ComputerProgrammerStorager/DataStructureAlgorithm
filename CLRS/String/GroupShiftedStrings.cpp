/*
We can shift a string by shifting each of its letters to its successive letter.

For example, "abc" can be shifted to be "bcd".
We can keep shifting the string to form a sequence.

For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
Given an array of strings strings, group all strings[i] that belong to the same shifting sequence. You may return the answer in any order.

 

Example 1:

Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
Example 2:

Input: strings = ["a"]
Output: [["a"]]
 

Constraints:

1 <= strings.length <= 200
1 <= strings[i].length <= 50
strings[i] consists of lowercase English letters.
*/

// group the strings based on hash value (kind of sorting) 
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string,vector<string>> m;
        vector<vector<string>> res;
        for ( auto str : strings ) {
            m[getkey(str)].push_back(str);
        }

        for (auto it : m ) {
            res.push_back(it.second);
        }
        return res;
    }

    char getshift(char ch, int shift) {
        return (ch-shift+26)%26+'a';
    }
    string getkey(string str) {
        int shift = str[0];
        string key;
        for (auto c : str )
            key.append(1,getshift(c,shift));
        return key;
    }
};