# [contains-duplicate-ii](https://leetcode.cn/problems/contains-duplicate-ii)

![image-20250228211109430](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250228211109507.png)

## overview

有一数组, 试求是否存在两个元素, 它们在数值上相同, 并且它们的下标间距小于或等于特定数字`k`.  若存在, 则返回`true`, 否则返回`false`.

## solution

本题和之前的存在重复元素一类似, 仍采用向前搜索法, 只不过在出现重复元素后需要对两元素间距进行评价, 如果符合要求即退出, 不符合对下标进行覆盖, 因为它要`<=`, 自然越近越好.

## code

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> hash;
        for(int i = 0; i < nums.size(); ++i)
        {
            if(hash.count(nums[i]))
            {
                int key = nums[i];
                int spacing = i - hash[key];
                if(spacing <= k)
                    return true;
                else
                    hash[key] = i;
            }
            else
            {
                hash.emplace(nums[i], i);
            }
        }
        return false;
    }
};
```

  # end