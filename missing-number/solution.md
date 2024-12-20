# [missing-number](https://leetcode.cn/problems/missing-number)

![image-20241220152234804](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241220152234904.png)

## overview

现从`[0, n]`这`n+1`个数中抽取`n`个数组成数组`nums`，请找出缺失的那个数。

## solution

这道题有多种解法。

第一种就是使用`n+1`规模大小的哈希表，然后记录一下`nums`中出现的数字，最后查看那个元素没有被标记即可。

第二种是使用高斯求和公式，`[0, n]`实际上是以`0`为首项，以`1`为公差的等差数列，可以先使用高斯求和公式找到该等差数列的和，再减去`nums`的元素和即可。

第三种是使用按位异或，对于相同值，按位异或的结果为0，且按位异或具有交换律，所以可以先把`[0, n]`这`n+1`个数进行异或，再接着`nums`里的元素进行异或，结果就是缺失的数。

## code

```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int size = nums.size(), ret = 0;
        for (int i = 0; i <= size; i++)
            ret ^= i;
        for (int i = 0; i < size; i++)
            ret ^= nums[i];
        return ret;
    }
};
```

