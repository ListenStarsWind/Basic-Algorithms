# [sum-of-two-integers](https://leetcode.cn/problems/sum-of-two-integers)

![image-20241224143141603](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241224143141766.png)

## overview

题目已经很清楚了，在此不作论述。

## solution

首先需要强调的是，如果在笔试时遇到了这道题，就直接用`return a + b;`，因为对于笔试来说，除非真有人看代码，否则是无法判断你是否真的使用`+`的，笔试主要看能不能达到效果，实际上不在乎代码内容。同类题目，就是非常奇怪的限制条件，也同样处理。

现在老老实实来做这道题，不能用`+ -`，那就大概率要用位运算了。

首先使用异或，我们之前说过，异或是无进位相加，接下来就要去找进位，进位依靠按位与来获取。

举个例子。

![image-20241224150750329](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241224150750474.png)

最后还要注意一点，在按位与之后，可能会出现负数，由于负数最高位是1，所以左移这个一就会溢出，正负形就有可能改变，一般情况下，这是一种危险操作，所以会造成程序运行错误，但在此种场景下，其实这种溢出没有影响，但为了避免运行出错，所以我们要把这个按位与和移位都用无符号变量承接。

## code

```cpp
class Solution {
public:
    int getSum(int a, int b) {
        while (b) // 如果b本来就为0
        {
            int x = a ^ b;                     // 记录无进位相加结果
            unsigned int carry = (a & b) << 1; // 记录进位状态

            // 对迭代变量再初始化
            a = x;
            b = carry; // 如果没有进位 跳出
        }
        return a;
    }
};
```

