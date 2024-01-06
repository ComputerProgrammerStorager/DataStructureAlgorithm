/*
Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.

 

Example 1:

Input: nums = ["01","10"]
Output: "11"
Explanation: "11" does not appear in nums. "00" would also be correct.
Example 2:

Input: nums = ["00","01"]
Output: "11"
Explanation: "11" does not appear in nums. "10" would also be correct.
Example 3:

Input: nums = ["111","011","001"]
Output: "101"
Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.
 

Constraints:

n == nums.length
1 <= n <= 16
nums[i].length == n
nums[i] is either '0' or '1'.
All the strings of nums are unique.
*/


class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        unordered_set<int> set;
        int n = nums[0].size();
        for ( auto num : nums ) {
            set.insert(stoi(num,nullptr,2));
        }

        for (auto val = 0; val < (1<<n); val++ ) {
            if ( set.count(val) == 0 )
                return to_binarystring(val,n);
        }

        return "";
    }

    string to_binarystring(int val, int n) {
        string res;
        while(val) { 
            res = to_string(val%2) + res;
            val /= 2;
        }
        int diff = n - res.size();
        res.insert(res.begin(),diff,'0');
        return res;
    }
};

// construct this way guarantees there will be at least one difference to any of the existing strings
class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        string res;
        int n = nums[0].size(), k = nums.size();
        for ( int i = 0; i < k; i++ ) {
            string val = nums[i][i] == '0' ? "1" : "0";
            res += val;
        }

        int diff = n - res.size();
        res.insert(res.begin(),diff,'0');
        return res;
    }
};