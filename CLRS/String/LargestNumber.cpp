/*
Given a list of non-negative integers nums, arrange them such that they form the largest number.

Note: The result may be very large, so you need to return a string instead of an integer.

 

Example 1:

Input: nums = [10,2]
Output: "210"
Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"
Example 3:

Input: nums = [1]
Output: "1"
Example 4:

Input: nums = [10]
Output: "10"
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 109
*/

// The key obsersvation is that we want to put the largest possible values first, with the constrain being that 
// digits belonging to the same number must be tied together. This constrain would only need to be considered when there 
// are prefixes. Therefore, to determine the order of two numbers in the final result, we just compare the results of them 
// with swapped poistions. In nutshell, we just need a comparator function to sort the strings. 
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        auto cmp = [](string const& l, string const& r){
            string l_r = l+r, r_l = r+l;
            long l_r_val = stoll(l_r), r_l_val = stoll(r_l);
            if ( l_r_val > r_l_val )
                return true;
            return false;
        }; 
        
        vector<string> numstr;
        string res;
        for ( auto n : nums )
            numstr.push_back(to_string(n));
        sort(numstr.begin(),numstr.end(),cmp);
        if ( stoi(numstr[0]) == 0 )
            return "0";
        for ( auto n : numstr )
            res += n;
        return res;
    }
};

// In fact the comparator could be simplified 
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        auto cmp = [](string const& l, string const& r){
            return l + r > r + l;
        }; 
        
        vector<string> numstr;
        string res;
        for ( auto n : nums )
            numstr.push_back(to_string(n));
        sort(numstr.begin(),numstr.end(),cmp);
        if ( stoi(numstr[0]) == 0 )
            return "0";
        for ( auto n : numstr )
            res += n;
        return res;
    }
};