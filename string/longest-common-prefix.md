# [longest-common-prefix](https://leetcode.cn/problems/longest-common-prefix)

![image-20250301213844276](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301213844444.png)

## overview

题目说的很明白, 寻找字符串数组的最长公共前缀. 比如对于示例一来说, 这三个字符串都有相同的前缀`fl`, 且再往后一步就不相同了.

## solution

这道题有两种解题方法, 一是两两比较, 将字符串数组的元素进行两两比较, 获得它们的最长公共前缀字符串, 再拿得到的结果和第三放字符串继续比较.

二是一列一列比, 整个一列的字符都是相同的, 则该字符就可以被计入公共前缀的一部分.

这两种方法在本质上是一样的, 只是角度不同, 其实只是以不同的组织形式进行字符比较, 它们的时间复杂度相同, 都是字符串数组中总的字符个数.

## code

```cpp
class Solution {
    string CommonPrefix(const string& s1, const string& s2)
    {
        int min_length = min(static_cast<int>(s1.size()), static_cast<int>(s2.size()));
        string result;
        for(int i = 0; i < min_length; ++i)
        {
            if(s1[i] == s2[i])
                result += s1[i];
            else
                return result;
        }
        return result;
    }
public:
    string longestCommonPrefix(vector<string>& strs) {
        string result = strs[0];
        for(int i = 1; i < strs.size(); ++i)
        {
            result = CommonPrefix(result, strs[i]);
        }
        return result;
    }
};


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) 
    {
        if (strs.empty()) return "";
        int min_length = INT_MAX;
        for (const string& str : strs) 
        {
            min_length = std::min(min_length, static_cast<int>(str.size()));
        }

        string result;
        for (int i = 0; i < min_length; ++i) 
        {
            char key = strs[0][i];
            for (int j = 1; j < strs.size(); ++j) 
            {
                if (strs[j][i] != key) return result;
            }
            result += key;
        }
        return result;
    }
};
```

# end