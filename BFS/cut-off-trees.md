# [cut-off-trees](https://leetcode.cn/problems/cut-off-trees-for-golf-event)

![image-20250325192250242](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325192250465.png)

## overview

现有一片树林, 这片树林里有三种地貌, 一, 障碍物, 无法触碰, 二, 平地, 可以自由通过, 三, 树, 也可以自由通过, 现在, 要你去把这片树林砍了, 而且还不能乱砍, 必须先砍矮的树, 再砍更高的树.                                    为了方便描述这片树林, 我们可以把这片树林抽象成一处`m*n`的矩形地块, 地块中的每个单元格上都有一个数字, 这个数字描述了该单元格的地貌情况. 有三种具体可能, 一, 数字为零, 表示障碍物, 无法触碰, 二, 数字为一, 表示平地, 可以自由通过, 三, 大于一的数字, 表示树, 数字越大, 树就越高, 其中, 为零或者为一的单元格可能有多个, 但大于一的单元格不会存在重复情况, 所以不用担心选择困难, 树的高度一定是强升序的, 不会出现相同的高度.

你将从矩形地块`[0, 0]`下标开始砍树, 然后返回砍完树的所需的最小步数, 如果因为障碍而不能砍完全部的树, 那就返回-1.

## solution

这道题就像一道窗户纸, 只要有了合适的思路, 捅破了, 就很容易了. 下面我们就来捅这张算法题. 

就和计算机网络差不多, 局域网里靠Mac, 广域网里靠IP, 一步一步走, 因为它要求升序地去砍树, 这意味着我们要先砍最矮树, 再砍第二矮的树, 再砍第三矮的树...我们先把矩形地块遍历一遍, 统计出它的升序状况, 从`[0, 0]`开始, 宽度优先遍历, 找到第一个矮的树, 顺便统计一下这个过程的步数, 然后从第一矮的树开始, 去找第二矮的树, 顺便统计一下...   最后把这些个数累加在一起即可, 在过程中, 如果有某个子过程过不去, 那就说明无法完全砍完树,  返-1吧. 

## code

```cpp
class Solution {
    typedef pair<int, int> pair;
    pair begin;
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int task(int end, const vector<vector<int>>& forest)
    {
        bool vis[50][50] = {{false}};
        int result = 0;
        queue<pair> q;
        int a = begin.first, b =  begin.second;
        q.emplace(a, b);
        vis[a][b] = true;
        while(!q.empty())
        {
            ++result;
            int size = q.size();
            for(int i = 0; i < size; ++i)
            {
                auto [c, d] = q.front();
                q.pop();
                for(int j = 0; j < 4; ++j)
                {
                    int x = c + dx[j];
                    int y = d + dy[j];
                    if(x >= 0 && x < m && y >= 0 && y < n && forest[x][y] > 0)
                    {
                        if(vis[x][y] == false)
                        {
                            if(forest[x][y] == end) 
                            {
                                begin.first = x;
                                begin.second = y;
                                return result;
                            }
                            vis[x][y] = true;
                            q.emplace(x, y);
                        }
                    }
                }
            }
        }
        return -1;
    }

public:
    int cutOffTree(vector<vector<int>>& forest) {
        m = forest.size(), n = forest[0].size();
        priority_queue<int, vector<int>, greater<int>> tasks;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                int height = forest[i][j];
                if(height > 1) tasks.emplace(height);
            }
        } 

        int result = 0;
        begin.first = 0, begin.second = 0;
        while(!tasks.empty())
        {
            int end = tasks.top();
            tasks.pop();
            if(end == forest[begin.first][begin.second]) continue;
            int size = task(end, forest);
            if(size == -1) return -1;
            result += size;
        }
        return result;
    }
};
```

# end