# [backspace-string-compare](https://leetcode.cn/problems/backspace-string-compare)

![image-20250306193856648](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306193856854.png)

## overview

本题与上一道题的思路相同.   题目给我们两个字符, 我们需要对这两个字符进行操作.  操作中, 若遍历到的字符不是`#`, 则将其录入, 若是`#`, 且文本不为空, 就将末尾字符弹出.

## solution  

使用`string`模拟栈,  对字符串元素进行遍历, 没遇到`#`, 将其压入`string`. 遇到`#`并且`string`不为空, 那就弹出末尾字符.

## code

```cpp
class Solution {
    string f(const string& s)
    {
        string result;
        for(auto ch : s)
        {
            if(ch != '#') result += ch;
            else
            {
                if(!result.empty()) result.pop_back();
            }
        }
        return result;
    }
public:
    bool backspaceCompare(string s, string t) {
        return f(s) == f(t);
    }
};
```

# end