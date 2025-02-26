# [two-sum](https://leetcode.cn/problems/two-sum)

![image-20250226212005573](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250226212005734.png)

## overview

题目很简单, 从数组中寻找两个元素, 使这两个元素的和为`target`, 并返回这两个元素的下标, 题目保证, 只有一对满足要求的元素, 找到就能直接退出.

## solution

首先仍旧是暴力破解. 我们先锁定一个元素, 然后往后去遍历其它元素, 看它们能不能凑成我们需要的那一对, 如果全找完了, 就锁定下一个元素, 重复过程.

第二种仍旧是暴力破解, 我们先锁定一个元素, 然后往前去遍历其它元素, 看看能不能凑成我们需要的那一对, 如果前面的元素都找完了, 那就锁定下一个元素, 重复过程.

第三种是对第二种方法的优化, 在第二种方法中, 主要的时间被消耗在往前找符合要求的另一半, 如果能把前面的数用哈希表记录,就能大大提高寻找效率.当然, 由于返回的是下标, 所以要用`map`.

为什么我们要在第二种方法的基础上使用哈希表呢? 首先对于第一种方法的第一轮循环中, 由于可能存在的目标值在后面, 而后面的数没有进入哈希表, 所以必须要真的去找, 之后若是再用哈希表, 逻辑就不同了, 就要换种代码; 这并不是最致命的问题, 最致命的问题是, 为了解决前面那个不太致命的问题, 我们需要预处理, 先将数组中的元素扔到哈希表中, 然后进行判断, 此时就正好踩到坑了, 题目规定, 不可以使用同一个下标的元素, 我们想一下, 有一个数组, 这个数组有一个4, `target`是`8`, 所以要找的另一半是`4`, 所以就会找到自身, 对于这种情况, 我们需要增加额外的代码逻辑, 一方面, 在找到另一半之后, 要去判断是否是自身, 另一方面, 数组中可能存在相同的两个元素, 此时用`map`还会造成数据丢失, 所以要用`multimap`;    对于第二种方法而言,  是找完之后再把自身扔进哈希, 这意味着, 在数据丢失之前, 我就已经找到这一对了, 所以丢失是可以接受的, 另一方面, 这也保证不会找到自己.

## code

```cpp
// 我觉得返回值是pair<int, int>更好
// 但既然返回的是vecor<int> , 我就当它不是只有一组

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        for(int i = 0; i < nums.size(); ++i)
        {
            int self = nums[i];
            int key = target - self;
            for(int j = i - 1; j >= 0; --j)
            {
                if(nums[j] == key)
                {
                    result.emplace_back(i);
                    result.emplace_back(j);
                }
            }
        }
        return result;
    }
};


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> val_idx;
        vector<int> result;
        for(int i = 0; i < nums.size(); ++i)
        {
            int self = nums[i];
            int key = target - self;
            if(val_idx.count(key))
            {
                result.emplace_back(i);
                result.emplace_back(val_idx[key]);
            }
            val_idx.emplace(nums[i], i);
        }
        return result;
    }
};
```

# end
