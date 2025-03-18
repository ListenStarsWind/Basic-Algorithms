# [number-of-islands](https://leetcode.cn/problems/number-of-islands)

![image-20250318213250033](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250318213250181.png)

## overview

这个其实还是`flood-fill`问题. 一片区域有很多小块, 性质相同的小块可以在上下左右四个方向相互连通, 可以连通的小块们共同组成一个大块, 问我们有多少大块.

## solution

我们从一个地址开始, 有序遍历整个区域, 只要小块未被检查并且为陆地, 那就以此为起点进行宽度优先搜索.    现在我们要面对一个问题, 那就是如何区分, 当前小块是否被检查过的, 有两种方式, 第一种方法我愿称之为"过河拆桥", 找到一块陆地, 就把它淹了, 也就是变为字符0, 因为它已经是零了, 所以就算是重复检查, 也不会起到实际效果,   但我们这里用的是第二种方法, 使用一个二维数组去标记那些数组是被遍历过的, 这种方法的优点是不改变二维数组的原先结构, 如果面试官要求不准改变原先结构就会非常有用, 而且, 这种思路也是非常常见的.

## code

```cpp
class Solution {
    typedef pair<int, int> pxy;

    int _m = 0, _n = 0;
    int _dx[4] = {0, 0, 1, -1};
    int _dy[4] = {1, -1, 0, 0};
    bool _vix[300][300] = {false};

    
    void mark(int i, int j, const vector<vector<char>>& grid)
    {
        queue<pxy> q;
        _vix[i][j] = true;
        q.emplace(i, j);
        while(!q.empty())
        {
            auto [m, n] = q.front();
            q.pop();
            for(int k = 0; k < 4; ++k)
            {
                int x = m + _dx[k];
                int y = n + _dy[k];
                if(x >= 0 && x < _m && y >= 0 && y < _n && grid[x][y] == '1' && _vix[x][y] == false)
                {
                    _vix[x][y] = true;
                    q.emplace(x, y);
                }
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int result = 0;
        _m = grid.size(), _n = grid[0].size();
        for(int i = 0; i < _m; ++i)
        {
            for(int j = 0; j < _n; ++j)
            {
                if(grid[i][j] == '1' && _vix[i][j] == false)
                {
                    mark(i, j, grid);
                    ++result;
                }
            }
        }
        return result;
    }
};
```

# end