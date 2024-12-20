# [matrix-block-sum](https://leetcode.cn/problems/matrix-block-sum)

![image-20241220083216806](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220083217015.png)

## overview

题目有些晦涩难懂，所以我们直接上图。

![image-20241220083958987](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220083959048.png)

如图现有一个矩阵数组`mat`和一个整数`k = 1`，我们要再建立一个同等规模的矩阵数组`answer`，记录对应位置的信息，什么信息呢？

![image-20241220084731716](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220084731781.png)

比如说对于`answer[0][0]`来说，就是`mat[0][0]`想周围扩展`k`个单位所形成子矩阵的元素和，对于超出`mat`边界的区域，我们不考虑。

![image-20241220084624551](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220084624618.png)

`1+2+4+5=12`，所以`answer[0][0] = 12`。对于`answer[1][1]`来说，器对应的子矩阵就是这样的

![image-20241220084943472](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220084943536.png)

元素和是`45`，所以`answer[1][1] = 45`。

## solution

之前我们再牛客那边写过二维数组的前缀和，这道题和牛客的区别在于左上角和右下角的坐标需要我们自己来计算，除此之外，这里的数组下标是从`0`开始的，所以必须要特别注意各个矩阵中位置的映射关系。

首先我们仍旧是建立一个表示子矩阵元素和的`dp`数组

![image-20241220090943425](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220090943480.png)

其中`dp[i][j]`记录了`mat`以`[0,0]`为左上角，以`[i-1][j-1]`为右下角子矩阵元素的和。比如，`dp[1][1]`表示以`mat[0][0]`为左上角，`dp[0][0]`为右下角的元素和。

![image-20241220090423739](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220090423791.png)

`dp[1][2]`

![image-20241220090530597](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220090530649.png)

`dp[3][2]`

![image-20241220090646278](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220090646330.png)

接下来我们看看这个元素和该怎么求。还是老样子，元素和是间接求解的，比如现在我们想求出`dp[2][2]`的值

![image-20241220092118356](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220092118447.png)

如果要求`A+B+C+D`的和，我们可以用`(A+B)+(A+C)-A+D`

![image-20241220092531391](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220092531441.png)

为什么要这样求呢？因为`A+B, A, A+C`都是左上角下标为`[0][0]`的子矩阵，这意味这我们能从`dp`里面直接把它们给查出来，特别要注意一下`D`，注意，对于`dp[i][j]`来说，其对应的`D`是`mat[i-1][j-1]`。这样的话`A+B`就是以`[i-2][j-1]`为右下角的矩阵，其对应的元素和可由`dp[i-1][j]`查出，而对于`A+C`来说，它是以`[i-1][j-2]`为右下角的矩阵，可由`dp[i][j-1]`查出，这样我们就得出了`dp[i][j]`的求和公式
$$
dp[i][j] = dp[i][j-1]+dp[i-1][j]-dp[i-1][j-1]+mat[i-1][j-1]
$$
现在我们就得到了`dp`矩阵，现在我们需要依据`dp`矩阵初始化`answer`。

为了更好的理清映射关系，我们先直接看`mat`和`answer`。

![image-20241220094811853](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220094811993.png)

首先我们需要进行边界调整，比如对于`answer[0][0]`来说，其对应的子矩阵应该以`mat[-k][-k]`为左上角，以`mat[k][k]`为右下角，或者这样说，对于`answer[i][j]`来说，其对应的自己挣应该以`mat[i-k][j-k]`为左上角，以`mat[i+k][j+k]`为右下角，但很明显左上角和右下角是有可能越界的，所以我们必须进行边界处理，对于`mat`来说，其允许最左上角坐标为`[0][0]`，最右下角为`[m-1][n-1]`(m = mat.size(), n = mat[0].size())，所以我们要对左上角和右上角的坐标进行调整，若设左上角坐标为`[x1][y1]`，右上角坐标为`[x2][y2]`，则有`x1 = max(0, i-k), y1 = max(0, j-k), x2 = min(m-1, i+k), y2 = min(n-1, j+k)`，求出这两个坐标之后，我们就可以通过间接手段求解以`[x1][y1]`为左上角，`[x2][y2]`为右下角形成的矩阵。

![image-20241209112312440](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209112312564.png)

我们先求出以`mat[0][0]`为左上角，以`mat[x1][y1]`为右下角的矩阵和，记为`A`，接着我们要求出以`mat[0][0]`为左上角，以`mat[x2][y1-1]`为右下角的矩阵和，记为`B`，以`mat[0][0]`为左上角，以`mat[x1-1][y2]`为右下角的矩阵和，记为`C`，`B, C`重合的部分，也就是以`mat[x1-1][y1-1]`为右下角的矩阵和记为`D`，那么以`mat[x1][y1]`为左上角，以`mat[x2][y2]`为右下角的矩阵和就是`A-B-C+D`。

接下来我们要把`A, B, C, D`映射到`dp`上，我们要注意，对于以`mat[0][0]`为左上角，以`mat[i][j]`为右下角的矩阵和，其对应的`dp`元素下标为`[i+1][j+1]`，为此，我们应该在原来`x1, y1, x2, y2`的基础上，对这些坐标再加上一。

## code

```cpp
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] +
                           mat[i - 1][j - 1];

        vector<vector<int>> answer(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                answer[i][j] = dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] +
                               dp[x1 - 1][y1 - 1];
            }
        return answer;
    }
};
```

