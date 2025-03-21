# [surrounded-regions](https://leetcode.cn/problems/surrounded-regions)

![image-20250321083304510](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250321083304674.png)

## overview

这道题的题干以前不是这样的, 现在说的比以前清楚, 说的很明白, 我们要找到被"围绕的"`O`, 并把它们改成`X`,  什么叫做"被围绕", 就是说, 这个`O`组成的区域块中没有一个元素在边界上, 且它周围的`X`组成了一个连通块.

## solution

对于这道题, 第一种思路是直接做, 遇到`O`就宽度搜索, 把它们改成`X`, 但很明显, 这种思路有个大问题, 那就是你在从连通块中的某个元素开始, 但这个连通块实际上有元素实际上在边界上的, 所以你实际上不能直接改, 要么你改过之后想办法还原, 要么记录一下块, 当发现其中有块在边界上, 就舍弃.  

第二种思路就是正难则反.   实际上,  被`X`所围绕这个条件可以合并到没有`O`在边界上, 因为这里只有两种可能, 要么是`O`, 要么是你`X`, 如果`O`不在边界上, 那边界上就是`X`, 所以`X`就可以借助于这个边界上的`X`连为一体.              这样的话, 我们可以先把边界遍历一下, 当遇到`O`时, 那就`bfs`一下, 把涉及到的`O`改成别的第三方符号, 之后再对整个区域进行遍历, 遇到这个第三方符号就改回`O`, 遇到`o`就改成`X`.

## code

```cpp
class Solution {
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {-1, 1, 0, 0};

    void bfs(int i, int j, vector<vector<char>>& board)
    {
        queue<pair<int, int>> q;
        q.emplace(i, j);
        board[i][j] = '#';
        while(!q.empty())
        {
            auto [a, b] = q.front();
            q.pop();
            for(int k = 0; k < 4; ++k)
            {
                int x = a + dx[k], y = b + dy[k];
                if(x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'O')
                {
                    board[x][y] = '#';
                    q.emplace(x, y);
                }
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        m = board.size(), n = board[0].size();
        for(int i = 0; i < n; ++i)
        {
            if(board[0][i] == 'O')  bfs(0, i, board);
            if(board[m-1][i] == 'O')  bfs(m-1, i, board);
        }
        for(int i = 0; i < m; ++i)
        {
            if(board[i][0] == 'O') bfs(i, 0, board);
            if(board[i][n-1] == 'O') bfs(i, n-1, board);
        }
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(board[i][j] == '#') board[i][j] = 'O';
                else if(board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }
};
```

# end