/*
Implement the RandomizedSet class:

RandomizedSet() Initializes the RandomizedSet object.
bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
You must implement the functions of the class such that each function works in average O(1) time complexity.

 

Example 1:

Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 

Constraints:

-231 <= val <= 231 - 1
At most 2 * 105 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
*/

// we need to maitain val-->idx mapping so that we can achieve O(1) remove 
class RandomizedSet {
    vector<int> data;
    unordered_map<int,int> val2idx;
public:
    RandomizedSet() {
        data.clear();
        val2idx.clear();
    }
    
    bool insert(int val) {
        if ( val2idx.count(val) ) 
            return false;
        val2idx[val] = data.size();
        data.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if ( val2idx.count(val) == 0 )
            return false;
        int pos = val2idx[val], end_val = data.back();
        data[pos] = end_val;
        val2idx[end_val] = pos;
        val2idx.erase(val);     
        // it's important that this line should be after the above line.. if not think about a case where the following pop_back removes the last element, causing it's empty, resulting in a case where we don't have 
        // element in the array, but we still have some mapping in the val2idx mapping.. An example is as following: 
        // ["RandomizedSet","remove","remove","insert","getRandom","remove","insert"]
        // [[],[0],[0],[0],[],[0],[0]]
        data.pop_back();
        return true;
    }
    
    int getRandom() {
        int rnd_idx = rand() % data.size();
        return data[rnd_idx];
    }
};