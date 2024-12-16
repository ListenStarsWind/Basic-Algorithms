# [Prefix Product](https://leetcode.cn/problems/product-of-array-except-self)

![image-20241215215149736](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241215215149822.png)

## overview

题目说的已经很清楚了。它保证积的结果不会超过int类型。

## solution

第一种方法仍旧是暴力破解。从左往右依次遍历，求出其余元素的乘积，将其填入对应的下标中即可，复杂度为$O(N^2)$。

第二种方法的思路是将其余元素的乘积变为左边元素的乘积乘上右边元素的乘积。为此我们要建立相应的前缀积数组和后缀积数组。我们规定`prefix[i]`表示`[0, i-1]`对应元素的乘积，`suffix[i]`表示`[i+1, size-1]`元素的乘积，最后把它们相乘即可。

## code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        size_t size = nums.size();
        vector<int> prefix(size, 1);
        vector<int> suffix(size, 1);

        for (int i = 1; i < size; i++)
            prefix[i] = prefix[i - 1] * nums[i - 1];

        for (int i = size - 2; i >= 0; i--)
            suffix[i] = suffix[i + 1] * nums[i + 1];

        vector<int> ret(size);
        for (int i = 0; i < size; i++)
            ret[i] = prefix[i] * suffix[i];

        return ret;
    }
};
```

