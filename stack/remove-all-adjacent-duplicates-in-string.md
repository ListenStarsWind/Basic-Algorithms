# [remove-all-adjacent-duplicates-in-string](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string)

![image-20250305123508609](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305123508682.png)

## overview

今天我们进入一个全新的容器专题算法, 栈.   栈本身是比较简单的,   难的是,  写题目的时候能不能想到用栈解决的方法.  

本题是一个"字符消消乐",  循环性的删除字符串中的所有重复项. 比如对于`abbaca`来说, 首先删除`bb`变为`aaca`, 然后删除`aa`, 变成`ca`.

## solution

先入`a`, 再入`b`, `b`前面是`a`, 那不作为, 再入`b`, `b`前面还是`b`, 这个`b`不会入, 之前的`b`也会弹出.....  这就是栈的逻辑.

挑选一个字符, 如果栈中不为空, 且栈顶和这个字符相同, 则弹出栈顶, 否则, 入栈.

但我们不需要真的用栈,   因为如果真的要用栈,  挑选完后还要把栈中剩余的元素弹出, 再逆序, 所以我们直接用字符串模拟栈就行了

## code

```cpp
class Solution {
public:
    string removeDuplicates(string s) {
        string stack;
        for(auto ch : s)
        {
            if(!stack.empty() && stack.back() == ch) 
                stack.pop_back();
            else
                stack += ch;
        }

        return stack;
    }
};
```

# end