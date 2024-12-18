# [contiguous-array](https://leetcode.cn/problems/contiguous-array)

![image-20241218202928732](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241218202928870.png)

## overview

题目还是很清楚的，题目给我们一个二元数组，所谓二元数组，就是这个数组中的元素只有两种，现在我们需要在这个数组中找到一个子数组，该子数组含有相同数量的`0`和`1`，最后我们需要返回一个满足要求的最长子数组长度。

## solution

首先我们可以看到这个数组是二元的，所以我们可引入一个平衡因子，并规定，一种元素加入子数组，平衡因子加一，另一种元素加入子数组，平衡因子减一，当平衡因子为0式，就说明对应的子数组是符合要求的，这肯定是比直接统计元素个数要好。

于是我们现在的要求就是在数组中找到一个最长的，平衡因子为0的子数组。我们的主体思路仍旧是上一道题的思路。
![image-20241218093426428](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241218093426736.png)

稍微不同的是，此时哈希表中的映射关系变了，以前是元素和-出现次数，现在应该是元素和-对应子数组长度。最开始，哈希表没有记录任何数组的信息，所以我们可以认为此时的元素和为0，也就是空数组的元素和，空数组没有元素，所以其长度就是0，符合要求的子数组长度计算方法就应该是当前研究区域的子数组长度减去第一部分子数组的长度，除此之外，我们还需要注意到，当出现重复的元素和时，我们就不要更新对应的长度了，因为它以后是作为减数的角色出场的，当然是越小越好。

## code

```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> hash;
        hash[0]; // 空数组的元素和为0，其对应长度也为0
        int sum = 0, len = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i] == 0 ? -1 : 1;

            // true: 一方面，意味着出现重复元素，另一方面，意味着找到了符合要求的第一部分
            if (hash.count(sum)) 
                len = max(len, i + 1 - hash[sum]);
            else
                hash[sum] = i + 1;
        }
        return len;
    }
};
```



# end

