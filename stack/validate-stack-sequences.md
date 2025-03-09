# [validate-stack-sequences](https://leetcode.cn/problems/validate-stack-sequences)

![image-20250309093453985](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250309093454075.png)

## overview

我们在栈的学习阶段想必已经接触过这种题, 现在让我们在代码上复现它.

题目给我们两个序列, 分别代表入栈顺序和出栈顺序, 要求你检验它们是否正确.

## solution

我们可以直接模拟即可, 每轮循环我们都将`pushed`中的元素入栈, 入完栈后看栈顶和`popped`中的元素是否相同, 相同一方面弹出栈顶, 另一方面, `popped`下标向后加一. 注意这个对比过程是循环性, 它有可能连着比, 最后判断栈为空并且`popped`遍历完毕.

以`[4, 5, 3, 2, 1]`为例, 首先入`1`, 和`4`不相同, 接着入`2`, 和`4`不相同, 入`3`, 和`4`不相同, 入`4`, 和`4`相同, 弹出`4`, 栈顶`3`和`5`不相同, 入`5`, `5`和`5`相同, 弹出, `3`和`3`相同, 弹出, `2`和`2`相同, 弹出, `1`和`1`相同, 弹出, 栈为空, 进入下轮循环, `pushed`直接越界, 循环结束, 此时, 栈为空, `popped`也全部遍历完毕, 返回真.

## code

```cpp
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        vector<int> st;
        int i = 0, j = 0;
        int pushSize = pushed.size();
        int popSize = popped.size();
        while(i < pushSize)
        {
            st.emplace_back(pushed[i++]);
            while(!st.empty() && st.back() == popped[j])
            {
                ++j;
                st.pop_back();
            }
        }
        return st.empty() && j == popSize;
    }
};
```

# end