# [find-pivot-index](https://leetcode.cn/problems/find-pivot-index)

![image-20241215154902211](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241215154902273.png)

## overview

题目说的已经很清楚了。现有一个整数数组，要求我们寻找一个下标，这个下标可以将数组分为三个部分，下标前的子数组，下标后的子数组，和下标元素，如果两个子数组的元素和相等，则就是我们要找的下标，称之为“中心下标”。如果中心下标有多个，比如对于数组`[0,0,0,0]`，返回最左边的中心下标。

## solution

首先仍旧是暴力破解。从前往后依次遍历，分别求出左边子数组的和，右边子数组的和，最后比对一下，相等返回，不同继续，它的复杂度为$O(N^2)$。

第二个解法是前缀和思想，我们可以在正式查找前，创建一个前缀和数组和一个后缀和数组，对于前缀和数组，我们定义`front[i]`的含义为`i`左边子数组的元素和，而对于`back[i]`来说，其表示`i`右边子数组的元素和，最后查找过程中只需要比对两个数组对应下标的元素是否相同即可。

而对于`front[i]`的初始化，使用的仍是一种分治思想：“`i`左边数组的元素和等于`i-1`左边数组的元素和再加上`nums[i-1]`”，即`front[i] = front[i-1] + nums[i-1]`，同理，对于`back[i]`来说，则是`back[i] = back[i+1] + nums[i+1]`，最后注意边界条件即可。

`front`应从下标一开始，因为下标0左边没有元素，所以`front[0] = 0`，同理，`back[0] = 0`

## code

```cpp
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        size_t size = nums.size();
        vector<int> front(size);
        vector<int> back(size);

        for (int i = 1; i < size; i++)
            front[i] = front[i - 1] + nums[i - 1];

        for (int i = size - 2; i >= 0; i--)
            back[i] = back[i + 1] + nums[i + 1];

        for (int i = 0; i < size; i++)
            if (front[i] == back[i])
                return i;

        return -1;
    }
};
```

