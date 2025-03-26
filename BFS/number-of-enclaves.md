# [number-of-enclaves](https://leetcode.cn/problems/number-of-enclaves)

![image-20250326120036043](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250326120036294.png)

## overview

给你一个大小为`m*n`的二进制矩阵, 其中的`1`表示陆地, `0`表示海洋,    对于陆地单元格来说, 每次只能移动到其上下左右四个方向的某个陆地单元格上, 海洋是无法通过的, 请你找出其中有多少陆地单元格是完全走不出矩阵的.  

先看示例一: ![img](https://assets.leetcode.com/uploads/2021/02/18/enclaves1.jpg)

只有和边界上陆地格构成一个连通块的陆地区域可以走出矩阵, 所以只有黄色的那个可以走出, 红色的就走不出,  返回走不出的陆地格数量, 即3.

## solution

第一个思路, 很暴力, 就遍历一下直接找, 碰到边界陆地格就把整个连通块标记一下, 这个思路光听上去就很麻烦.

第二个思路, 既然只有和边界陆地格连为一体的才能出去, 那以   为一的   边界单元格为起点开始,  往里面找, 把连为一体的标记一下即可, 最后再把矩阵遍历一下, 把没标记的一统计一下即可.                另外这里可能有多个边界一, 所以可以用多源BFS.

## code

```cpp
class Solution {
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
public:
    int numEnclaves(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        for(int i = 0; i < m; ++i)
        {
            if(grid[i][0] == 1)
            {
                q.emplace(i, 0);
                vis[i][0] = true;
            }
            if(grid[i][n-1] == 1) 
            {
                q.emplace(i, n-1);
                vis[i][n-1] = true;
            }
        }

        for(int i = 0; i < n; ++i)
        {
            if(grid[0][i] == 1) 
            {
                q.emplace(0, i);
                vis[0][i] = true;
            }
            if(grid[m-1][i] == 1) 
            {
                q.emplace(m-1, i);
                vis[m-1][i] = true;
            }
        }

        while(!q.empty())
        {
            auto [a, b] = q.front(); q.pop();
            for(int i = 0; i < 4; ++i)
            {
                int x = a + dx[i];
                int y = b + dy[i];
                if(x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1)
                {
                    if(vis[x][y] == false)
                    {
                        vis[x][y] = true;
                        q.emplace(x, y);
                    }
                }
            }
        }

        int result = 0;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(grid[i][j] == 1 && vis[i][j] == false)
                {
                    ++result;
                }
            }
        }

        return result;
    }
};
```

   # end

