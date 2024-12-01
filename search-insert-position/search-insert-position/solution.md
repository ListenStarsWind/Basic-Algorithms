# [search-insert-position](https://leetcode.cn/problems/search-insert-position)

![image-20241201195708745](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412011957856.png)

## overview

题目的要求很明确，就是寻找大于等于目标值的元素。

## solution

使用非严格弱序二分查找模版，其中`left`扮演开拓者，`right`扮演守成者。注意可能存在数组中元素全部小于目标值的情况，此时需要返回数组长度。

## code

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        if (nums[left] < target)
            return left + 1;
        else
            return left;
    }
};
```

# end