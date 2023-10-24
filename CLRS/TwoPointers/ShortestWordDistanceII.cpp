/*
Design a data structure that will be initialized with a string array, and then it should answer queries of the shortest distance between two different strings from the array.

Implement the WordDistance class:

WordDistance(String[] wordsDict) initializes the object with the strings array wordsDict.
int shortest(String word1, String word2) returns the shortest distance between word1 and word2 in the array wordsDict.
 

Example 1:

Input
["WordDistance", "shortest", "shortest"]
[[["practice", "makes", "perfect", "coding", "makes"]], ["coding", "practice"], ["makes", "coding"]]
Output
[null, 3, 1]

Explanation
WordDistance wordDistance = new WordDistance(["practice", "makes", "perfect", "coding", "makes"]);
wordDistance.shortest("coding", "practice"); // return 3
wordDistance.shortest("makes", "coding");    // return 1
 

Constraints:

1 <= wordsDict.length <= 3 * 104
1 <= wordsDict[i].length <= 10
wordsDict[i] consists of lowercase English letters.
word1 and word2 are in wordsDict.
word1 != word2
At most 5000 calls will be made to shortest.
*/

// It boils down to find the min difference between two sorted lists of indices 
// Using two pointers: every time move the smaller one in the hope of finding a smaller difference 
class WordDistance {
    unordered_map<string,vector<int>> m;
public:
    WordDistance(vector<string>& wordsDict) {
        for ( int i = 0; i < wordsDict.size(); i++ )
        {
            m[wordsDict[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        return minDiff(m[word1],m[word2]);
    }
private:
    // calulate min difference between two sorted lists of indices 
    int minDiff(const vector<int>& l1, const vector<int>& l2)
    {
        int i = 0, j = 0, diff = INT_MAX;
        while( i < l1.size() && j < l2.size() ) 
        {
            diff = min(diff,abs(l1[i]-l2[j]));
            if ( l1[i] < l2[j] )
                i++;
            else 
                j++;
        }
        return diff;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */