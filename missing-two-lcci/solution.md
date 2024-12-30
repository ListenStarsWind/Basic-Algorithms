# [missing-two-lcci](https://leetcode.cn/problems/missing-two-lcci)

![image-20241230201947791](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241230201947876.png)

## overview

题目已经描述得很详细了,在此不作赘述

## solution

仍旧是使用位运算对其进行解答. 

我们知道,异或运算具有所谓"消消乐"的性质,如果丢失的只有一个数字,也就是`1 - N`中缺一个数, 想找出那个缺失的数就非常容易,只需把`1 - N`和现在数组中的所有元素都异或一遍,自然就能找到那个丢失的数.

而对于这道题来说,问题在于有两个丢失的数字,如果按上述操作进行异或操作,最后得到的,是两个丢失数的异或,所以怎么办呢? 我们需要再延伸一步,我们设丢失的两个数字为`a  b`,那么最后异或得到的结果就是`a ^ b`.

让我们回到异或的计算方式上,如果两个比特位是相同的,异或得到的结果就是0, 而如果两个比特位是不同的, 异或得到的结果就是1,这意为着,如果`a ^ b`结果的某一比特位是`1`,就意味`a b`在该比特位上的数值是不同的, 也就是说, `a b`在该比特位上,一定是一个为1, 一个为0, 于是我们就可以用这种方式把`a b`区分开来.

这样我们就可以把`1 - N` + `数组元素`分成两个部分,一个部分是该比特位值为1, 另一个是该比特位为0. 然后再对这两部分进行异或操作,就能得到丢失的两个数字了.

## code

```cpp
class Solution {
public:
    vector<int> missingTwo(vector<int>& nums) {
        int num_count = nums.size();
        int total_count = num_count + 2;

        // 计算所有数字的异或值（包括丢失的两个数）
        int xor_all = 0;
        for (int i = 1; i <= total_count; i++)
            xor_all ^= i;
        for (auto num : nums)
            xor_all ^= num;

        // 找到两个丢失数字在二进制表示中最低不同的一位
        int differing_bit = 0;
        while (((xor_all >> differing_bit) & 1) == 0) {
            differing_bit++;
        }

        // 根据最低不同位将数字分为两组，并分别计算异或值
        int missing1 = 0, missing2 = 0;
        for (int i = 1; i <= total_count; i++) {
            if ((i >> differing_bit) & 1) {
                missing1 ^= i;
            } else {
                missing2 ^= i;
            }
        }
        for (auto num : nums) {
            if ((num >> differing_bit) & 1) {
                missing1 ^= num;
            } else {
                missing2 ^= num;
            }
        }

        return {missing1, missing2};
    }
};
```

# end

