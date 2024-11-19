# [longest-substring-without-repeating-characters](https://leetcode.cn/problems/longest-substring-without-repeating-characters)

![image-20241119175344627](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411191753745.png)

## overview

首先还是让我们看看题。

题目让我们从字符串`s`中找到一个子串，这个子串中不能有重复的字符，之后返回满足要求的最长子串长度即可。

比如对于示例1来说，我们可以找到子串`abc`，但之后就不能继续延伸子串长度了，因为下一个字符是`a`。同理，还可以找到其它一些子串，它们要么长度和`abc`一样，要么比`abc`短，所以最后返回3.

对于示例2来说，字符都一样，那也只能返回1了。

对于示例3来说，先是`p`，然后是`pw`，接着是`pww`，那就重复了，所以跳过第一个`w`，又有了`wk`，`wke`，之后是`wkew`，重复了，所以最后返回3。

## solution

首先，还是暴力解法。

我们从每个字符开始，一个一个地往后扩大子串范围，直到再扩大范围就要出现重复字符时结束，然后把起始字符往后移一位，重新开始，最后把最长的长度返回即可。

如何判断是否出现重复字符呢？我们通过哈希表来实现，题目也说了，字符串`s`是由英文字母、数字、符号和空格组成的，意思是它们是ASCII码，所以建一个128成员的数组即可。

暴力算法的时间复杂度就是等差数列，也就是$O(N^2)$。

接下来我们对暴力算法做一些优化。比如现在的字符串是`deabcabca`。最开始，`left`和`right`当然都是指向下标0的，之后`right`往后遍历，给我们检索出了`deabc`的子串，接下来`right`继续往后遍历，结果碰到了相同字符。按照暴力破解的逻辑，现在要把`left`和`right`都移到下标1了。这里就可以优化一下了，为什么我们重新找子串了，因为遇到了重复字符，可你现在就直接从下标1重找子串只能找到更短的子串，比如，就现在的场景来说，如果你从下标1重找子串，那`right`遇到第二个`a`，不还是要重来吗？而且很明显，`deabc`当然是比`eabc`长的，所以我们完全可以直接把`left`移到第一个`a`后的`b`开始重找子串，中间的那部分都不需要再尝试了，肯定是比`deabc`短的。接下来第二个优化点就是，当你已经把`left`已经移到`b`了之后，`right`要不要再回来呢？答案是不要的，因为`left`已经把两个重复字符中的第一个扔掉了，这意味着，现在`left`和`right`之间的字符是不重复的。

当我们找到一个合法子串后，我们需要更新一下有效`len`，之后让`left`往后迭代，直到两指针不再有重复字符后再扩大子串长度。

其实就是经典的滑动窗口算法，每次进窗口，都更新一下哈希表，然后检查哈希表中是否有重复项，如果有，就先存储长度，然后不断循环让`left`把第一个重复项扔掉即可，在此基础上，再重新搜索子串。

## code

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int right = 0;
        int len = 0;
        int sz = s.size();
        int arr[128] = {0};

        while (right < sz) {
            arr[s[right++]]++;
            while (arr[s[right - 1]] > 1) {
                len = max(len, right - left - 1);
                arr[s[left++]]--;
            }
        }

        len = max(len, right - left);

        return len;
    }
};
```

可能整个字符串`s`都没有重复项，那就一次都不会进入内循环，为此在循环结束之后，我们还需要尝试更新一下长度。

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ret = 0; // 记录结果
        int n = s.length();
        // 1. 枚举从不同位置开始的最⻓重复⼦串
        // 枚举起始位置
        for (int i = 0; i < n; i++) {
            // 创建⼀个哈希表，统计频次
            int hash[128] = {0};
            // 寻找结束为⽌
            for (int j = i; j < n; j++) {
                hash[s[j]]++;       // 统计字符出现的频次
                if (hash[s[j]] > 1) // 如果出现重复的
                    break;
                // 如果没有重复，就更新 ret
                ret = max(ret, j - i + 1);
            }
        }
        // 2. 返回结果
        return ret;
    }
};
```

代码形式怎样都无所谓，重要的还是思想。

# end