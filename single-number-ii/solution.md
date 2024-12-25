# [single-number-ii](https://leetcode.cn/problems/single-number-ii)

 ![image-20241225091514230](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241225091514439.png)

## overview

题目表达的已经很清晰了,在此不作赘述.

## solution

将数组中的元素都视为二进制序列串, 根据题目, 每个比特位的和无非四种情况:

- 3n个0加上0得0
- 3n个0加上1得1
- 3n个1加上0得3n
- 3n个1加上1得3n+1

再把结果都余上`3`, 就是`0 % 3 = 0, 1 % 3 = 1, 3n % 3 = 0, (3n+1)% 3 = 1`, 于是我们就可以总结出一个规律: 当仅出现一次的元素比特位为1时, 这些元素对应比特位的和对3取余就是1, 如果是0, 就是0.

这种规律在数组中除某个元素只出现一次,其它元素都出现`m`次的场景仍旧适用.

## code

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (int i = 0; i < 32; i++) {
            int sum = 0;
            for (auto e : nums) {
                if ((e >> i) & 1)
                    sum++;
            }
            sum %= 3;
            if (sum)
                ret |= (1 << i);
        }
        return ret;
    }
};
```

# end