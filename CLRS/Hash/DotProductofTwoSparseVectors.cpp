/*
Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) Initializes the object with the vector nums
dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
A sparse vector is a vector that has mostly zero values, you should store the sparse vector efficiently and compute the dot product between two SparseVector.

Follow up: What if only one of the vectors is sparse?

 

Example 1:

Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
Output: 8
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
Example 2:

Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
Output: 0
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
Example 3:

Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
Output: 6
 

Constraints:

n == nums1.length == nums2.length
1 <= n <= 10^5
0 <= nums1[i], nums2[i] <= 100
*/

// we use an hash table to store only the non-zero values in each vector
class SparseVector {
    // pos to value map 
    unordered_map<int,int> m;
public:
    
    SparseVector(vector<int> &nums) {
        for ( int i = 0; i < nums.size(); i++ )
            if ( nums[i] )
                m[i] = nums[i];
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int res = 0;
        for ( auto val : m )
        {
            if ( vec.m.count(val.first) != 0 )
            {
                res += val.second * vec.m[val.first];
            }
        }
        
        return res;
    }
};

// we can use two pointers technique to avoid the complexity of find the index in the other set in the above approach 
class SparseVector {
    // pos to value map 
    vector<pair<int,int>> idx2val;
public:
    
    SparseVector(vector<int> &nums) {
        for ( int i = 0; i < nums.size(); i++ )
            if ( nums[i] )
                idx2val.push_back(make_pair(i,nums[i]));
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int res = 0;
        int n1 = idx2val.size(), n2 = vec.idx2val.size();
        if ( n1 == 0 || n2 == 0 )
            return res;
        int p = 0, q = 0;
        while ( p < n1 && q < n2 )
        {
            if ( idx2val[p].first == vec.idx2val[q].first )
            {
                res += idx2val[p].second * vec.idx2val[q].second;
                p++;
                q++;
            }
            else if ( idx2val[p].first < vec.idx2val[q].first )
            {
                p++;
            }
            else
            {
                q++;
            }
        }
        
        return res;
    }
};