# [max-area-of-island](https://leetcode.cn/problems/max-area-of-island)

![image-20250319214011364](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250319214011482.png)

## overview

有了前面两道题的铺垫之后, 相信这题已经变得很简单了, 我们只需要在bfs的过程中顺手数数有多少个坐标入队就行

## solution

和以前一样, 先找到一个一, 然后从它开始宽度搜索, 最后比较一下返回的面积就行.

## code

```cpp
class Solution {
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;

    int bfs(int i, int j, vector<vector<bool>>& vis, const vector<vector<int>>& grid)
    {
        int result = 1;
        queue<pair<int, int>> q;
        vis[i][j] = true;
        q.emplace(i, j);
        while(!q.empty())
        {
            auto [a, b] = q.front();
            q.pop();
            for(int k = 0; k < 4; ++k)
            {
                int x = a + dx[k];
                int y = b + dy[k];
                if(x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1 && vis[x][y] == false)
                {
                    vis[x][y] = true;
                    ++result;
                    q.emplace(x, y);
                }
            }
        }
        return result;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size(), n = grid[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(grid[i][j] == 1 && vis[i][j] == false)
                {
                    result = max(result, bfs(i, j, vis, grid));
                }
            }
        }
        return result;
    }
};
```

# end