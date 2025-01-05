# [count-and-say](https://leetcode.cn/problems/count-and-say)

![image-20250105202951897](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250105202952048.png)

## overview

外观数列是以`"1"`为首项的字符串阵列, 其中的每一项都是对前一项的描述, 描述的方法如下, 首先将被描述的字符串分为若干块, 每块由同一个字符构成, 随后对这些块进行描述, 使用两个字符对单个块进行描述, 第一个字符用于描述该块中字符的个数, 第二个字符用于描述 该块中的字符.

比如对于第一项来说, 其可以划分成一个块, 这个块由一个字符`1`构成, 所以这个块的描述就是`"11"`, 而第一项只有一个块, 所以第二项就是`"11"`,
对于第二项来说,其可以划分成一个块, 这个块由两个字符`1`构成, 所以第三项就是`21`
对于第三项来说, 其可被划分成两个块, 第一个快由一个字符`2`构成, 第二块由一个字符`1`构成, 所以第四项就是`"1211"`
对于第四项来说,其可被划分成三个块, 第一个块由一个字符`1`构成, 第二个字符由一个字符`2`构成, 第三个字符由两个字符`1`构成, 所以第五项就是`"111221"`

## solution

在概述环节, 我们就已经说明了模拟过程.

我们使用两个指针用于寻找一个块, 它们最开始都位于上一项的0号下标, 如果`end`所指向的字符与`start`所指向的字符相同, 那就让`++end`, 不相同时, 就意味着已经找到了一个块, 所以就可以对块进行解析了, 单个块的解析很简单, `end-start`就是字符的个数, `start`指向的字符就是重复的字符. 在解析块之后,将`start`移动到`end`, 注意为了避免最后一个块的越界, 当`end > len`时, 就也要停止块的寻找了.

## code

```cpp
class Solution {
public:
    string countAndSay(int n) {
        string result = "1";
        for (size_t i = 1; i < n; ++i) 
        {
            string nextSequence;
            size_t length = result.size();
            for (size_t start = 0, end = 0; end < length; ) 
            {
                // 找到连续字符的区间
                while (end < length && result[start] == result[end]) ++end;
                // 统计数量并记录字符
                nextSequence += end - start + '0';
                nextSequence += result[start];
                // 更新起始位置
                start = end;
            }
            result.swap(nextSequence);
        }
        return result;
    }
};

```

# end