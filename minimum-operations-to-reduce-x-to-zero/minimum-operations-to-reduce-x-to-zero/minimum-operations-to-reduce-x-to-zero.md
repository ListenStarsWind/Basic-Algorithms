# [minimum-operations-to-reduce-x-to-zero](https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero)

![image-20241123150726523](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411231507653.png)

## overview

有一个只含有正整数的数组`nums`和一个正整数`k`，现要求你尝试从该数组的左右两边移除元素，使得最终移除元素的和恰好为`k`，我们称每次移除为一个操作，返回最小的操作次数，如果找不到，即返回-1。

以示例一为例：

比如我们先删除最左边的那个一，操作之后，`k`就变成了4，接下来我们就不能再考虑这个最左边的一了，这就是题目中请注意的意思：已经移除的元素不参与接下来的操作；接着我们可以再删除一，`k`就变成了`3`，然后再删除最右边的三，`k`就变成了0，所以这轮模拟的操作数结果为3。

我也可以先删除最右边的三，这样`k`就变成了`2`，接着再删除那个二，`k`就变成了0，所以这轮模拟的操作数为2。

返回最小的操作数2。

## solution

这道题正着做太难了，所以我们反着做：定义`sum`为数组中所有元素的和，则原问题可以转换成在题目中的`nums`中找到一个子数组，使得其元素和恰好为`sum -k`，选取长度最长的子数组作为结果。

同样是定义两个指针`left`和`right`最开始指向0，由于`target = sum -k`理应为非负数，所以`right`每次向后迭代，其子数组元素和必然就更接近`target`，当元素和超出`target`时，缩小子数组范围，`left`向后迭代，并且当元素和恰好为`target`时对`len`进行更新。

## code

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = 0;
        for (auto e : nums)
            sum += e;

        int left = 0, right = 0, len = 0, target = sum - x, sz = nums.size();
        sum = 0;

        if(target == 0)
        return sz;    

        while (right < sz) {
            sum += nums[right++];
            while (left < right && sum > target)
                sum -= nums[left++];
            if (sum == target)
                len = max(len, right - left);
        }

        if (len == 0)
            return -1;
        else
            return sz - len;
    }
};
```

在这份代码中，`target`存在负数可能，因此需要限制`left`，防止其越界，当`len`为0时，说明找不到对应的子数组，则返回`-1`。

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = 0;
        for (auto e : nums)
            sum += e;

        int left = 0, right = 0, len = -1, target = sum - x, sz = nums.size();
        sum = 0;

        if (target < 0)
            return -1;

        while (right < sz) {
            sum += nums[right++];
            while (sum > target)
                sum -= nums[left++];
            if (sum == target)
                len = max(len, right - left);
        }

        if (len == -1)
            return -1;
        else
            return sz - len;
    }
};
```

在这份代码中，`target`不存在负数可能，`len`最开始为标志位`-1`，当遍历之后`len`依旧为-1，说明找不到符合要求的子数组，遂返回-1。当`target`恰好为`0`时，`len`最终为`0`，此时亦可使用`sz - len`。

# end