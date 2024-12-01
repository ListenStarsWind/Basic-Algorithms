# [sqrtx](https://leetcode.cn/problems/sqrtx)

![image-20241201091947956](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412010919026.png)

## overview

求一个非负整数的向下取整算数平方根。

## solution

首先仍旧是暴力查找，比如对于`x == 17`来说，相当于有一个`1`到`17`的序列存在，接下来我们就可以逐个遍历，就可以找到了。

接下来我们可以对其进行优化，本题的问题可以转换一下：在序列中寻找一个最近小于或者等于的值，比如对于`x == 17`来说，是在`1`到`17`之间寻找一个介于`4`到`5`的小数，要的结果就是4，又如当`x == 36`时，需要寻找的值就是6，所以说，找的是等于或向下取整小于的值。

因此我们就可以依据最终的结果把数组分成两部分，一部分是小于等于目标值，另一部分是大于目标值，这表明它们具有二段性，因此可以使用非严格弱序的二分查找。

## code

```cpp
class Solution {
public:
    int mySqrt(int x) {
        if (x < 1)
            return 0;

        int left = 1, right = x;
        while (left < right) {
            long long mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }
};
```

因为0的算数平方根仍旧是0，所以要做特殊处理，此外，为了让防止`mid`相乘而溢出，需要将它的类型范围扩大一些。

# end