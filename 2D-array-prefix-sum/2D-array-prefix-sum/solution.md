# [2D-array-prefix-sum](https://www.nowcoder.com/share/jump/9209693051733711273630)

![image-20241209102901633](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209102901751.png)

# overview

和一维数组前缀和一样，我们先建立一个下标为0的数组。

![image-20241209103856472](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209103856545.png)

那么`(1,2)`的位置就是`[2]`，`(3,4)`的位置就是`[8]`，它们俩包含的二维子数组就是这样

![image-20241209104403685](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209104403808.png)

其中的所有元素和32，输出的就是32。

# solution

第一个方法，仍然是暴力破解。每次查询都是一次单独事件，每次查询就是直接按照参数遍历一下子数组，加一下其中的元素，就能得到结果。

第二个方法是建立一个前缀和数组，记为`dp`

![image-20241209105140559](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209105140642.png)

我们约定，`dp[i][j]`表示从`arr[1][1]`开始，到`arr[i][j]`这个子数组中所有元素的和。

现在我们把数组稍微抽象一下，我们现在要求出`dp[i][j]`的值，为了方便我们把子数组中的元素和称为面积。

![image-20241209110901407](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209110901506.png)

`BC`的面积不好求，因为`dp[i][j]`表示从`arr[1][1]`开始，到`arr[i][j]`这个子数组中所有元素的和，但我们可以先查出`A+C`和`A+B`的面积，之后再加上`D`，再减去`A`即可，用公式来说就是
$$
A+B+C+D = (A+B)+(A+C)+D-A
$$
用`dp`表示就是
$$
dp[i][j] = dp[i-1][j] +dp[i][j-1]+arr[i][j]-dp[i-1][j-1]
$$
需要注意的是，由于`dp[i][j]`表示对应子数组的面积，`int`不一定能放得下结果，所以要用`long long`。

前缀和数组建立完后，就需要讨论在查询结果时如何利用。

![image-20241209112312440](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209112312564.png)

仍是使用分割的办法
$$
(x1,y1) : (x2,y2)=dp[x2][y2] - dp[x2][y1-1] - dp[x1-1][y2] + dp[x1-1][y1-1]
$$

# code

```cpp
#include <iostream>
#include<vector>
using namespace std;

int main() {
    int n,m,q;
    cin >> n >>m>>q;
    vector<vector<int>> v(n+1, vector<int>(m+1));
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        cin >> v[i][j];
    }

    vector<vector<long long>> dp(n+1, vector<long long>(m+1));
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + v[i][j];
    }

    int i1, j1, i2, j2;
    while(q--)
    {
        cin >> i1 >> j1 >> i2 >> j2;
        cout<< dp[i2][j2] - dp[i2][j1-1] - dp[i1-1][j2] + dp[i1-1][j1-1] <<endl;
    }
}
```

# end