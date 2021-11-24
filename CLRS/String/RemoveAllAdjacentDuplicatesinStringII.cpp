/*
You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them, causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.

 

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
 

Constraints:

1 <= s.length <= 105
2 <= k <= 104
s only contains lower case English letters.

*/

// repeated delete the duplicate k chars until there is no change 
class Solution {
public:
    string removeDuplicates(string s, int k) {
        int len = -1;
        while ( len != s.size() )
        {
            len = s.size();
            for ( int i = 0, cnt = 0; i < s.size(); i++ )
            {
                if ( i == 0 || s[i] != s[i-1] )
                {
                    cnt = 1;
                }
                else if ( ++cnt == k )
                {
                    s.erase(i-k+1,k);
                    break;
                }
            }
        }
        
        return s;
    }
};

// use extra space remembering the cnt to avoid starting over for the begining of the string after removing characters 
// we only need to move back by k chars
class Solution {
public:
    string removeDuplicates(string s, int k) {
        vector<int> cnt(s.size());
        for ( int i = 0; i < s.size(); i++ )
        {
            if ( i == 0 || s[i] != s[i-1] )
            {
                cnt[i] = 1;
            }
            else 
            {
                cnt[i] = cnt[i-1] + 1;
                if ( cnt[i] == k )
                {
                    s.erase(i-k+1,k);
                    i = i-k;
                }
            }
        }
        return s;
    }
};

// use stack and associate with each stack number with its consecutive rank
class Solution {
    typedef pair<int,int> II;
public:
    string removeDuplicates(string s, int k) {
        stack<II> st;
        string res;
        for ( int i = 0; i < s.size(); i++ )
        {
            if ( st.empty() || st.top().first != s[i] )
            {
                st.push({s[i],1});
                continue;
            }
            st.push({s[i],st.top().second+1});
            if ( st.top().second == k )
            {
                int pop_cnt = k;
                while ( pop_cnt-- )
                {
                    st.pop();
                }
            }
        }
        
        while ( !st.empty() )
        {
            string::const_iterator it = res.cbegin();
            res.insert(it,st.top().first);
            st.pop();
        }
        
        return res;
    }
};

// we can optimize the above solution a bit
class Solution {
public:
    string removeDuplicates(string s, int k) {
        vector<II> vec;
        string res;
        for ( int i = 0; i < s.size(); i++ )
        {
            if ( vec.empty() || vec.back().first != s[i] )
            {
                vec.push_back({s[i],1});
            }
            else if ( ++vec.back().second == k )
            {
                vec.pop_back();
            }
        }
        
        for ( auto &p : vec )
        {
            res += string(p.second,p.first);
        }
        
        return res;
    }
};

class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char,int>> st;
        string res;
        for ( auto c : s )
        {
            if ( st.empty() || c != st.top().first )
            {
                st.push({c,1});
            }
            else {
                st.push({c,st.top().second+1});
                if ( st.top().second == k )
                {
                    int popcnt = k;
                    while(popcnt--)
                    {
                        st.pop();
                    }
                }
            }
        }
        
        while(!st.empty())
        {
            res.append(1,st.top().first);
            st.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
};