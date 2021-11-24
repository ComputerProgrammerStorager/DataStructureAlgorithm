/*
You are given an m x n char matrix board representing the game board where:

'M' represents an unrevealed mine,
'E' represents an unrevealed empty square,
'B' represents a revealed blank square that has no adjacent mines (i.e., above, below, left, right, and all 4 diagonals),
digit ('1' to '8') represents how many mines are adjacent to this revealed square, and
'X' represents a revealed mine.
You are also given an integer array click where click = [clickr, clickc] represents the next click position among all the unrevealed squares ('M' or 'E').

Return the board after revealing this position according to the following rules:

If a mine 'M' is revealed, then the game is over. You should change it to 'X'.
If an empty square 'E' with no adjacent mines is revealed, then change it to a revealed blank 'B' and all of its adjacent unrevealed squares should be revealed recursively.
If an empty square 'E' with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.
 

Example 1:


Input: board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
Output: [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
Example 2:


Input: board = [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]], click = [1,2]
Output: [["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 50
board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
click.length == 2
0 <= clickr < m
0 <= clickc < n
board[clickr][clickc] is either 'M' or 'E'.
*/

// dfs only the neighbors of the current node that has no neighboring mines 
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> revealed(m,vector<bool>(n,false));
        dfs(board,click[0],click[1],revealed);
        return board;
    }
private: 
    int GetNeighborMines( vector<vector<char>> const& board, int i, int j )
    {
        vector<pair<int,int>> dirs{{0,1},{0,-1},{-1,0},{1,0},{1,-1},{1,1},{-1,1},{-1,-1}};
        int m = board.size(), n = board[0].size(), neighbor_mines = 0;
        for ( auto d : dirs )
        {
            int n_x = d.first + i;
            int n_y = d.second + j;
            if ( n_x >= m || n_x < 0 || n_y >= n || n_y < 0 )
                continue;
            if ( board[n_x][n_y] == 'M' )
                neighbor_mines++;
        }
        
        return neighbor_mines;
    }
    void dfs( vector<vector<char>> &board, int i, int j, vector<vector<bool>> &revealed)
    {
        vector<pair<int,int>> dirs{{0,1},{0,-1},{-1,0},{1,0},{1,-1},{1,1},{-1,1},{-1,-1}};
        int m = board.size(), n = board[0].size(), neighbor_mines = GetNeighborMines(board,i,j);
        revealed[i][j] = true;
        if ( board[i][j] == 'M' )
        {
            board[i][j] = 'X';
        }
        else if ( neighbor_mines != 0 )
        {
            board[i][j] = '0'+ neighbor_mines;
        }
        else {
            board[i][j] = 'B';
            for ( auto d : dirs )
            {
                int n_x = d.first + i;
                int n_y = d.second + j;
                if ( n_x >= m || n_x < 0 || n_y >= n || n_y < 0 || revealed[n_x][n_y] )
                {
                    continue;
                }
                dfs(board,n_x,n_y,revealed);
            }
        }
    }
};

// as always, there is a bfs brother solution 
// It seems that we need to set revealed indication before pushing a position to the queue to avoid leetcode time exceeding
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> revealed(m,vector<bool>(n,false));
        bfs(board,click[0],click[1],revealed);
        return board;
    }
private: 
    int GetNeighborMines( vector<vector<char>> const& board, int i, int j )
    {
        vector<pair<int,int>> dirs{{0,1},{0,-1},{-1,0},{1,0},{1,-1},{1,1},{-1,1},{-1,-1}};
        int m = board.size(), n = board[0].size(), neighbor_mines = 0;
        for ( auto d : dirs )
        {
            int n_x = d.first + i;
            int n_y = d.second + j;
            if ( n_x >= m || n_x < 0 || n_y >= n || n_y < 0 )
                continue;
            if ( board[n_x][n_y] == 'M' )
                neighbor_mines++;
        }
        
        return neighbor_mines;
    }
    
    void bfs(vector<vector<char>> &board, int i, int j, vector<vector<bool>> &revealed )
    {
        vector<pair<int,int>> dirs{{0,1},{0,-1},{-1,0},{1,0},{1,-1},{1,1},{-1,1},{-1,-1}};
        int m = board.size(), n = board[0].size();
        queue<pair<int,int>> q;
        q.push({i,j});
        revealed[i][j] = true;
        while(!q.empty())
        {
            int cur_qs = q.size(); 
            for ( int i = 0;i < cur_qs; i++ )
            {
                auto cur_pos = q.front();
                int x = cur_pos.first;
                int y = cur_pos.second;
                
                q.pop();
                int neighbor_mines = GetNeighborMines(board,x,y);
                if ( board[x][y] == 'M' )
                {
                    board[x][y] = 'X';
                }
                else if ( neighbor_mines != 0 )
                {
                    board[x][y] = '0' + neighbor_mines;
                }
                else 
                {
                    board[x][y] = 'B';
                    for ( auto d : dirs )
                    {
                        int n_x = d.first + x;
                        int n_y = d.second + y;
                        if ( n_x >= m || n_x < 0 || n_y >= n || n_y < 0 || revealed[n_x][n_y] )
                            continue;
                        revealed[n_x][n_y] = true;
                        q.push({n_x,n_y});
                    }
                }
            }
        }
    }
};