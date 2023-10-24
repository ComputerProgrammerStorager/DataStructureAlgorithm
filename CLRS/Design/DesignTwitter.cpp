/*
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.

Implement the Twitter class:

Twitter() Initializes your twitter object.
void postTweet(int userId, int tweetId) Composes a new tweet with ID tweetId by the user userId. Each call to this function will be made with a unique tweetId.
List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent.
void follow(int followerId, int followeeId) The user with ID followerId started following the user with ID followeeId.
void unfollow(int followerId, int followeeId) The user with ID followerId started unfollowing the user with ID followeeId.
 

Example 1:

Input
["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
[[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
Output
[null, null, [5], null, null, [6, 5], null, [5]]

Explanation
Twitter twitter = new Twitter();
twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
twitter.follow(1, 2);    // User 1 follows user 2.
twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.unfollow(1, 2);  // User 1 unfollows user 2.
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.
 

Constraints:

1 <= userId, followerId, followeeId <= 500
0 <= tweetId <= 104
All the tweets have unique IDs.
At most 3 * 104 calls will be made to postTweet, getNewsFeed, follow, and unfollow.
*/

// Store all tweets together, and the check from backwords to get return the most recent first. 

class Twitter {
private:
    vector<pair<int,int>> tweets;   // <userId, tweetId> 
    unordered_map<int, unordered_set<int>> following;    // following list
public:
    Twitter() {
        tweets.clear();
        following.clear();
    }
    
    void postTweet(int userId, int tweetId) {
        tweets.push_back({userId, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        int cnt = 10;
        vector<int> res;
        unordered_set<int> followees = following[userId];
        for ( int i = tweets.size() - 1; i >= 0 && cnt; i-- )
        {
            if ( userId == tweets[i].first || followees.find(tweets[i].first) != followees.end() )
            {
                res.push_back(tweets[i].second);
                cnt--;
            }
        }

        return res;
    }
    
    void follow(int followerId, int followeeId) {
        following[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

// each user maintains his/her status 
struct Tweet {
    int id;
    int time;
    Tweet *next = nullptr;
    Tweet(int id, int time) : id(id), time(time) {}
};

struct User {
    int id;
    unordered_set<int> followeeIds;
    Tweet *tweethead = nullptr;
    User() {};
    User(int id) : id(id) {
        follow(id);
    }
    void follow(int followeeId) {
        followeeIds.insert(followeeId);
    }
    void unfollow(int followeeId) {
        followeeIds.erase(followeeId);
    }
    void post(int tweetId, int time) {
        Tweet *oldhead = tweethead;
        tweethead = new Tweet(tweetId,time);
        tweethead->next = oldhead;
    }
};

class Twitter {
private:
    int time = 0;
    unordered_map<int, User> users;
public:
    Twitter() {
        
    }
    
    void postTweet(int userId, int tweetId) {
        if ( users.count(userId) == 0 )
            users[userId] = User(userId);
        users[userId].post(tweetId,time++);
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        if ( users.count(userId) == 0 )
            return res;
        auto cmp = [](const Tweet* a, const Tweet* b) {
            return a->time < b->time;
        };
        priority_queue<Tweet*,vector<Tweet*>,decltype(cmp)> pq(cmp);
        for ( auto followeeId : users[userId].followeeIds ){
            Tweet* tweethead = users[followeeId].tweethead;
            if ( tweethead )
                pq.push(tweethead);
        }
        int cnt = 10;
        while( !pq.empty() && cnt )
        {
            Tweet* cur = pq.top();
            pq.pop();
            res.push_back(cur->id);
            if ( cur->next )
                pq.push(cur->next);
            cnt--;
        }

        return res;
    }
    
    void follow(int followerId, int followeeId) {
        if ( followerId == followeeId )
            return ;
        if ( users.count(followerId) == 0 )
            users[followerId] = User(followerId);
        if ( users.count(followeeId) == 0 )
            users[followeeId] = User(followeeId);
        users[followerId].follow(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if ( followerId == followeeId )
            return ;
        if ( auto it = users.find(followerId); it != users.end() && users.count(followeeId) )
            it->second.unfollow(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */