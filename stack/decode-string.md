# [decode-string](https://leetcode.cn/problems/decode-string)

![image-20250308130041934](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250308130042010.png)

## overview

给你一个字符串, 这个字符串是以`k[encoded_string]`的形式嵌套组合而成的. 我们把`k[encoded_string]`这个东西称之为一个"基本结构", 基本结构的解析规则是将`[]`里的字符串重复`k`次, 变成`encoded_stringencoded_stringencoded_string` 的形式,  比如, 以示例二为例, 首先, 需要把最里面的基本结构解析出来, 转变为`3[acc]`,然后再进行解析, 就得到了`accaccacc`            再看示例三, `2[abc]3[cd]ef`中并不是完全由基本结构嵌套组成的, 它还包括"落单"的字符串`ef`.`abc    cd`该重复的重复, 再加上`ef`, 就有了`abcabccdcdcdef`

## solution

这道题有很多的解法. 因为它有很多的细节, 就有各种各样的处理方式, 我们这里会把各种情况都一对一处理, 讲的更详细些.

我们使用的基本容器是栈, 因为输入字符串是以嵌套形式组成的, 而且我们要从最里面进行解析.遇到`[`, 要把字符串传入栈中, 遇到`]`, 要把刚刚传入的字符串再拿出来, 是后进先出的模式, 所以自然是用栈的.

将会有两个栈, 一个负责维护`[]`前面的重复次数, 另一个用来维护`[]`里面的字符串.

我们以`1[a2[bc]]de2[f]`为例.  有四种情况:  碰到数字字符,   碰到`[`,  碰到`]`,  碰到落单字符串

当我们遇到一个数字字符时, 先把它提取出来, 因为数字不一定是一位的, 也有可能是两位的, 提取成`int`, 然后扔到整型栈里, 然后我们遇到了`[`, 就需要先把后面的字符串给扔进栈中, 也就是`"a"`, 注意, 这个`"a"`是不完整的`encoded_string`, 所以等到后面的基本结构被解析之后还要加到`"a"`这个字符串上, 接着我们遇到了`2`, 扔到栈里, `[`, 检索出后面的字符串`bc`, 仍进栈中, 接着遇到`]`, 此时就可以把字符串栈顶`"bc"`取出来, 再把整型栈顶`2`取出来, 然后在新的栈顶`"a"`上重复加上`2`次`bc`, 好的, 先暂停一下, 我们的字符串栈在定义时要先扔一个空字符串, 因为对于最外层的基本结构来说, 从栈中取出来, 栈就空了, 没有栈顶可以插入, 所以我们需要在字符串栈顶初始化时先扔一个空字符串.   现在, 字符串栈中两个元素, 栈顶是`"abcbc"`, 还有一个空字符串, 整型栈中也只有一个`1`, 我们接着继续, 发现又是`]`, 于是, 把`abcbc`取出来, 重复`1`次加到新栈顶上, 之后遇到一个落单字符串, 直接加到栈顶`"abcbc"`上变成`"abcbcde"`即可, 因为落单的字符串要么是`encoded_string`的一部分, 要参与后续的重复,所以要加到栈顶上, 要么它真的是独立的, 此时栈顶已经解析完了, 加上也没事 , 之后遇到`2`, 扔到栈中, 遇到`[`, 把`"f"`扔进栈中, 遇到`]`, 把`"f"`弹出, 重复两次加到栈顶上, 最后栈顶就是要返回的字符串.

遇到数字放到整型栈

遇到`[`, 把后面的字符串扔到栈里

遇到`]`, 拿出两个栈的栈顶, 解析, 加到字符串栈栈顶上

遇到落单字符串, 直接加到字符串栈顶上.

## code

```cpp
class Solution {
public:
    string decodeString(string s) {
        vector<string> st1(1, "");
        vector<int> st2;
        int idx = 0, len = s.size();
        while(idx < len)
        {
            if(s[idx] >= '0' && s[idx] <= '9')
            {
                int temp(0);
                // 可以不判断是否越界, 因为字符串本身是合法的, 数字后面一定有`[`
                while(s[idx] >= '0' && s[idx] <= '9')
                    temp = temp * 10 + (s[idx++] - '0');
                st2.emplace_back(temp);
            }
            else if(s[idx] == '[')
            {
                ++idx;
                string temp;
                // 可以不判断是否越界, 因为字符串本身是合法的, 有`[`必有对应的`]`
                while(s[idx] >= 'a' && s[idx] <= 'z')
                    temp += s[idx++];
                st1.emplace_back(temp);
            }
            else if(s[idx] == ']')
            {
                ++idx;
                string temp = st1.back();
                int cir = st2.back();
                st1.pop_back();
                st2.pop_back();
                for(int i = 0; i < cir; ++i)
                    st1.back() += temp;
            }
            else
            {
                string temp;
                // 这个必须将越界判断, 因为落单的字符串可能在最外层
                while(idx < len && s[idx] >= 'a' && s[idx] <= 'z')
                    temp += s[idx++];
                st1.back() += temp;
            }
        }

        return st1.back();
    }
};
```

## 后记

这道题的细节太多了, 用上面的方法非常容易出错, 对此, 不如用个`dfs`, 每遇到一个`[`都意味着一个新的决策树, 交给下一层的`dfs`, 接收返回值, 进行统一处理, 并跳过末尾`]`, 如果碰到一个无非配对的`]`, 说明本树已经空了, 跳出循环, 回溯.

```cpp
class Solution {
    int size;
    int pos = 0;

    string dfs(const string& s)
    {
        if(pos == size) return string();

        string res;
        int oper = 0;
        while(pos < size)
        {
            if(s[pos] == '[')
            {
                ++pos;

                string buff = dfs(s);

                ++pos;

                while(oper--) res += buff;
            }
            else if(s[pos] == ']') break;
            else if(isdigit(s[pos]))
            {
                int temp = 0;
                while(isdigit(s[pos])) temp = temp * 10 + (s[pos++] - '0');
                oper = temp;
            }
            else res += s[pos++];
        }

        return res;
    }


public:
    string decodeString(string s) {
        size = s.size();
        return dfs(s);
    }
};
```

# end