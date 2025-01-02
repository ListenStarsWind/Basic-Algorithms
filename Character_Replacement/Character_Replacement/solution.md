# [Character_Replacement](https://leetcode.cn/problems/replace-all-s-to-avoid-consecutive-repeating-characters)

![image-20250102171408586](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250102171408746.png)

## overview

今天, 我们进入一个新的算法分支-----模拟.  所谓模拟算法, 其实就是照葫芦画瓢: 题目自己就给出了解题思路, 剩下来要做的事就是把题目给出的思路转化成代码.  

一般情况下, 模拟算法所给出的思路都有些空泛, 所谓空泛就是说它只提供了大思路, 具体怎么实现这个思路它是一句也不讲. 所以对于模拟算法来说, 我们主要操心两件事: 一是理解题目思路到底是什么; 二是, 要处理好细节问题.

## solution

思路很简单, 虽然题目没直接说.  把输入的字符串逐个扫描, 遇到`?`,就替换. 唯一的替换要求就是不出现连续的重复字符.   

当找到`?`,就要执行替换逻辑.  我们就从`a`开始,拿26个字母逐个试, 为了避免出现重复的连续字符, 需要将迭代字符与`?`前和`?`后的字符比对一下,只有迭代字符与前后两个字符都不相等, 才可以替换. 这里要注意,可能会出现没有前一个字符或者没有后一个字符的情况,  如果没有,我们不比较即可.

相比`if`语句,  逻辑或的短路特性   ------    如果前一个条件 为真  就不会执行下一个条件 (如果前/后没有字符, 那就不要比)  很明显更好   ,而且也能让逻辑更加融洽  

## code

```cpp
class Solution {
public:
    string modifyString(string s) {
        size_t len = s.size();
        for (size_t i = 0; i < len; i++) 
        {
            if (s[i] == '?') 
            {
                for (char ch = 'a'; ch <= 'z'; ch++) 
                {
                    if ((i == 0 || ch != s[i - 1]) &&
                        (i == len - 1 || ch != s[i + 1])) {
                        s[i] = ch;
                        break;
                    }
                }
            }
        }
        return s;
    }
};
```

注意一下 逻辑与的两个条件在逻辑上是并发的, 所以要带括号 , 确保优先级. 

# end