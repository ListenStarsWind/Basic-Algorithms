# [as-far-from-land-as-possible](https://leetcode.cn/problems/as-far-from-land-as-possible)

![image-20250327195035414](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250327195035521.png)

## overview

给你一个`m*n`的二进制矩阵, 矩阵分为`m*n`个单元格, 为`1`的单元格表示陆地, 为`0`的单元格表示海洋, 现需要你对该矩阵进行地貌分析, 找出距离陆地最远的海洋, 并将距离返回, 若矩阵全为陆地或海洋, 则视为寻找不到, 距离返回-1. 注意此处的距离指的是两个单元格上下, 左右两个方向上的距离和, 比如, 对于`[0, 0]`, 和`[1, 2]`这两个单元格, 它们之间的距离就是上下方向上的相对距离1和左右方向上的相对距离2的和, 即三.

## solution

曼哈顿距离实际上就是宽度优先遍历的扩展圈数, 从中心点开始, 扩展一圈遇到的单元格与中心单元格的距离就是一. 所以本题的核心思路就是宽度优先搜索. 建立一个同等规模的辅助矩阵, 用来记录扩展的圈数, 开始, 先把陆地单元格扔进队列, 之后不断扩展, 进行bfs即可. 与矩阵那题的思路实际相同.

## code

```cpp
class Solution {
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
public:
    int maxDistance(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> temp(m, vector<int>(n, -1));
        for(int i = 0; i < m ; ++i)
        {
            for(int j = 0; j < n ; ++j)
            {
                if(grid[i][j] == 1)
                {
                    temp[i][j] = 0;
                    q.emplace(i, j);
                }
            }
        }

        int result = -1;
        while(!q.empty())
        {
            auto [a, b] = q.front(); q.pop();
            for(int k = 0; k < 4; ++k)
            {
                int x = a + dx[k];
                int y = b + dy[k];
                if(x >= 0 && x < m && y >= 0 && y < n && temp[x][y] == -1)
                {
                    if(grid[x][y] == 0)
                    {
                        result = temp[a][b] + 1;
                        temp[x][y] = result;
                        q.emplace(x, y);
                    }
                }
            }
        }

        return result;
    }
};
```

# end