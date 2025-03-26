# [map-of-highest-peak](https://leetcode.cn/problems/map-of-highest-peak)

![image-20250326130230460](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250326130230573.png)

## overview

正如他所提示的那样, 本题与542矩阵相同, 是我们不久前做过的一个题目, 但我们还是要读读题.

题目最开始给我们一个二进制矩阵, 其中一表示海洋单元格, 零表示陆地单元格. 如下图

![image-20250326130822861](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250326130822892.png)

现在要为这个矩阵中的每个单元格安排高度.     安排规则如下

- 海域的高度必须为零
- 相邻的单元格高度差不能超过一,    所谓相邻单元格, 就是该单元格上下左右四个方向的临近单元格.
- 将单元格的高度以同等规模的矩阵数组返回
- 请让返回矩阵数组中的最高高度最大.

## solution

首先, 因为海洋的高度是确定的, 所以我们可以先从海洋开始

![image-20250326131448769](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250326131448799.png)

向外一圈一圈的扩展, 因为它说要尽可能高度最高, 所以每次扩展我们都在原先基础上加一

![image-20250326131553061](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250326131553090.png)

![image-20250326131612786](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250326131612816.png)

![image-20250326131625130](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250326131625160.png)

整个过程和我们之前做的542矩阵相同, 代码可以说是一模一样.

## code

```cpp
class Solution {
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        queue<pair<int, int>> q;
        int m = isWater.size(),  n = isWater[0].size();
        vector<vector<int>> result(m, vector<int>(n, -1));
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(isWater[i][j] == 1)
                {
                    q.emplace(i, j);
                    result[i][j] = 0;
                }
            }
        }

        while(!q.empty())
        {
            auto [a, b] = q.front(); q.pop();
            int val = result[a][b]; ++val;
            for(int i = 0; i < 4; ++i)
            {
                int x = a + dx[i];
                int y = b + dy[i];
                if(x >= 0 && x < m && y >= 0 && y < n)
                {
                    if(result[x][y] == -1)
                    {
                        result[x][y] = val;
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