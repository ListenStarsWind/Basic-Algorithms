# [matrix](https://leetcode.cn/problems/01-matrix)

![image-20250325215504877](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325215504981.png)

## overview

今天我们进入一个全新的小节, 那就是多源BFS问题.         在说多源BFS问题之前, 我们先要说说单源最短路问题, 其实我们之前写的那些最短路问题就是单源最短路问题, 单源与多源的区别在于, 起点数目的不同,  单源最短路问题是一个起点去一个或者多个终点, 而多元最短路问题是多个起点去一个或者多个终点. 多元BFS就是用BFS解决多源最短路问题, 需要注意的是, 我们这里说的最短路, 仍旧是最简单的边权为一的最短路问题. 

对于边权为一的多源最短路问题, 有两种使用BFS的思路

- 一是暴力破解, 你不是有多个起点吗? 行, 我搞若干个循环, 每次循环都从其中的一个起点开始, 当成单源最短路问题. 当然, 这时间复杂度让人无法接受
- 二是并发竞争, 我们知道BFS它本质还是穷举, 以前单源最短路问题可能是, 比如, 孙悟空从起点开始, 每到一个分岔路口, 拔些毫毛, 变几个分身.    那对于多源最短路问题, 我们可以最开始就有几个孙悟空, 它们一起去找终点. 

这里对于第二种思路画一张图

![image-20250325221716130](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325221716180.png)

对于`a`来说, 由于它接下来无论走哪个方向, 都是被别人走过的, 所以就被自然淘汰了,    至于`b, c`, 它们会去竞争之后的节点, 谁先竞争到之后的节点,, 谁就能淘汰另一个.

代码改起来也很简单, 单源只有一个孙悟空, 你只要把这一个孙悟空扔进队列里不断迭代就行了, 多源就是把孙悟空们, 最开始都丢进队列, 然后继续迭代, 只是最开始不同而已.

对于这道题来说,  情况小有不同, 

现有一个矩阵, 矩阵中的每个单元格都有一个二进制数字, 现在把数字为零的单元格定义为终点, 请你就每个单元格都找出属于它们自己的, 去往起点的最短路径, 并将路径长度以同样规格的二维数组返回出去. 

比如我们看示例一, 对于那些为零的单元格来说, 它本身就是终点, 一步也不要走, 所以返回的二维数组对应位置都是零, 而对于中间的那个一来说, 无论是上下左右, 都是零, 所以它的路径长度就是一.

对于示例二来说, 零单元格我们就跳过了, 中间的一, 上左右是零, 所以走一步就行了, 边角上的两个一, 上面是零, 所以路径长度也是一, 至于下面中间的一, 无论是连着往上走两步, 还是左/右, 再上, 都是两步, 所以它就是两步. 

## solution

第一个解法, 那就是一个格子一个格子找, 一个一个BFS 但很明显, 复杂度有些太高了.

解法二就是并发竞争, 再加上正难则反.   

![image-20250325231041552](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325231041625.png)

你看, 对于那些为零的单元格, 都不用求, 就是零, 所以我们可以从那些为零的单元格开始(一开始就把它们放进队列), 零外面的那圈一的步长自然是一, 然后再来外面一圈就是二.

![image-20250325231523492](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325231523542.png)

如果我们不从零, 而从一开始就有很多麻烦事, 你要想办法存一下最开始的坐标, 等bfs结束, 再把对应的`result`二维数组位置该值, 你要引入一个布尔二维数组去描述那些单元格已经遍历过了, 每次最外层循环你都要计数一下, 否则不知道你一共跑了多少圈了.

从零开始找, 我们可以一开始把为一的单元格对应的`result`路径都定义为-1, -1的意思就是说, 这里没有改, 之后要是遇到了, 你要改的, 此时返回的那个`result`二维数组就起到了布尔二维数组的作用,  你甚至不需要专门定义一个值去统计走了多少圈, 你看, 比如上图中的青蓝色块, 它们都是从零这个单元格扩展出来的, 所以它们在`result`中的对应位置就是零对应路径长加一,

下图表示返回的`result`二维数组

![image-20250325232919341](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325232919396.png)

![image-20250325232938197](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325232938240.png)

![image-20250325232959546](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325232959590.png)

![image-20250325233026331](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325233026371.png)

![image-20250325233040891](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250325233040936.png)

当前路径长的值是中心值加一.

当然, 我语言讲起来也不是很清楚, 我们看代码吧

## code

```cpp
class Solution {
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        queue<pair<int, int>> q;
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> result(m, vector<int>(n, -1));
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(mat[i][j] == 0)
                {
                    result[i][j] = 0;
                    q.emplace(i, j);
                }
            }
        }

        while(!q.empty())
        {
            auto [a, b] = q.front(); q.pop();
            int val = result[a][b]; ++val;
            for(int j = 0; j < 4; ++j)
            {
                int x = a + dx[j];
                int y = b + dy[j];
                if(x >= 0 && x < m && y >= 0 && y < n && result[x][y] == -1)
                {
                    q.emplace(x, y);
                    result[x][y] = val;
                }
            }
        }
        return result;
    }
};
```

# end

