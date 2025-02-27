# [check-permutation-lcci](https://leetcode.cn/problems/check-permutation-lcci)

![image-20250227205958993](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250227205959110.png)

## overview

我们需要确认, 一个字符串中的元素经过重新排列后是否能变为另一个字符串

## solution

首先, 仍旧是暴力破解. 我们可以首先统计第一个字符串中的字符信息, 然后以穷举的方式组合出所有可能得重排字符串, 如果其中一种可能与另一个字符串相同, 则意为着, 它们互为重排字符.

当然, 我们不会写暴力破解. 如果两个字符串可以通过重排的方式相互转换, 这说明, 这两个字符串中的字符元素在种类和数目上都是对应相同的, 为此, 我们可以引入一个哈希表, 考虑到统计的元素十分简单, 可以使用数组实现哈希表, 前一个字符串加加, 后一个字符串减减, 最后再把数组遍历一遍, 全为0则说明它们互为重排字符串.                在上面的逻辑上, 我们可以进行一定的优化, 首先, 其实在减减过程中, 若个数出现了负数, 那当然可以直接得答案了.     另外, 如果两个字符串长度都不一样, 那就根本没必要进行其他操作, 并且, 当确保字符串长度相同的基础上, 如果它们不是互为字符重排, 说明, 一定会有元素的个数最终变为负数, 所以就不需要再把数组遍历一遍了.

## code

```cpp
class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
        if(s1.size() != s2.size())
            return false;
        
        int hash[26] = {0};
        for(auto e : s1)
        {
            int idx = e - 'a';
            ++hash[idx];
        }

        for(auto e : s2)
        {
            int idx = e - 'a';
            --hash[idx];
            if(hash[idx] < 0)
                return false;
        }
        return true;
    }
};
```

# end