# [contains-duplicate](https://leetcode.cn/problems/contains-duplicate)

![image-20250228204817419](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250228204817588.png)

## overview

试判断一个数组中是否有相同元素. 有返回`true`, 无返回`false`

## solution

这道题和两数之和那道题相似, 那道题是找符合要求的另一半, 这里只需要看看有没有自己就行了.  还是和之前一样, 先固定一个元素, 然后看看这个元素和之前的元素是否相同, 通过哈希表的方式.

## code

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> hash;
        for(auto e : nums)
        {
            if(hash.count(e))
                return true;
            else
                hash.emplace(e);
        }
        return false;
    }
};
```

# end