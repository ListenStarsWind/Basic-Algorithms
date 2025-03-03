# [longest-palindromic-substring](https://leetcode.cn/problems/longest-palindromic-substring)

![image-20250303084326544](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303084326686.png)

## overview

有一字符串, 试在其中找到最长的回文子串.   所谓回文串, 就是第`n`个字符和倒数第`n`个字符相同的字符串, 字符串中可能有多个最长的回文子串, 你只需要返回其中任意一个即可.

## solution

我们使用的是中心扩展算法.   利用回文串的镜像对称性,  可以先固定一个中心字符, 然后让两指针往两边扩展, 直到两指针指向的元素越界或者不相同,   跳出循环分析长度, 更新回文串.

比如, 对于示例一来说, 可以先固定`[0]`号下标的字符`b`作为中心字符, 两指针初始都指向`[0]`, 之后往两边扩展, 出现越界, 分析现有长度,  发现比之前的回文串长, 于是更新.   之后将`[1]`作为中心点, 找出`bab`这个回文串.....

上面的扩展方式只能找出奇数个数的回文串,  所以我们还要进行第二遍查找, 初始时,两指针中一个指向中心点, 另一个指向中心点的前一个或者后一个字符,  我们这里就统一为, 最开始`left`是中心点, `right`是中心点下一个.

## code

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        pair<int, int> index;
        for(int i = 0; i < s.size(); ++i)
        {
            int left = i, right = i;
            while(left >= 0 && right < s.size() && s[left] == s[right])
            {
                --left;
                ++right;
            }
            if(right - left - 1 > index.second - index.first - 1)
            {
                index.first = left;
                index.second = right;
            }

            left = i, right = i + 1;
            while(left >= 0 && right < s.size() && s[left] == s[right])
            {
                --left;
                ++right;
            }
            if(right - left - 1 > index.second - index.first - 1)
            {
                index.first = left;
                index.second = right;
            }
        }

        return s.substr(index.first + 1, index.second - index.first - 1);
    }
};
```

# end