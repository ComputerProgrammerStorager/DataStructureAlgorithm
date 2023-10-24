/*

Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and uses only constant extra space.

 

Example 1:

Input: nums = [1,3,4,2,2]
Output: 2
Example 2:

Input: nums = [3,1,3,4,2]
Output: 3
 

Constraints:

1 <= n <= 105
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or more times.
 

Follow up:

How can we prove that at least one duplicate number must exist in nums?
Can you solve the problem in linear runtime complexity?
*/

// It is easy to come up with approaches which either uses space or changes the given array 
// Use set 
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        set<int> st;
        for ( auto n : nums )
            if ( st.count(n) ) 
                return n;
            else {
                st.insert(n);
            }
        return -1;
    }
};

// Use sorting 
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        for ( int i = 1; i < nums.size(); i++ )
        {
            if ( nums[i] == nums[i-1] )
                return nums[i];
        }

        return -1;
    }
};

// considering the values belong to [1,n], we can use it's values to index the array and use sign to indicate 
// a value (index) has been seen before or not. 
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for ( const auto n : nums )
        {
            if ( nums[abs(n)] < 0 )
                return abs(n);
            nums[abs(n)] *= -1;
        }

        for ( auto &n : nums )
            n = abs(n);
        return -1;
    }
};

// try to put cur in position [cur]. if an instance is already in the target position, then a duplicate is identified 
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        return move_cur(nums,0);
    }
private:
    int move_cur(vector<int>& nums, int cur)
    {
        if ( cur == nums[cur] )
            return cur;
        int nxt = nums[cur];
        nums[cur] = cur;
        return move_cur(nums,nxt);
    }
};

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        while(nums[0] != nums[nums[0]] )
            swap(nums[0],nums[nums[0]]);
        return nums[0];
    }
};

// leverage the observation that the rank(less than or equal to) of a duplicate is larger than itself 
// So our goal is then to find the smallest number whose rank is larget than itself, using binary searching 
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        auto get_rank = [&](int cur) {
            int cnt = 0;
            for ( auto n : nums )
                if ( n <= cur )
                    cnt++;
            return cnt;
        };

        int l = 1, r = nums.size(), dup = -1;
        while( l <= r )
        {
            int m = (l+r)/2;
            if ( get_rank(m) > m )
            {
                dup = m;
                r = m-1;
            }
            else {
                l = m+1;
            }
        }

        return dup;
    }
};

// this is essentially a finding cycle entrace problem 
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int tortoise = nums[0], hare = nums[0];
        do {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        } while(tortoise != hare);

        tortoise = nums[0];
        while( tortoise != hare ) {
            tortoise = nums[tortoise];
            hare = nums[hare];
        }

        return tortoise;
    }
};