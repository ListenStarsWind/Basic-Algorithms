# [Alien Dictionary](https://leetcode.cn/problems/Jf1JuT)

![image-20250328121232489](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250328121232593.png)

## overview

现有一个外星文明, 它们所使用的语言也是英语, 有26个字母, 与地球上的英语稍有不同的是, 外星英语的字典序和地球英语不同, 对于地球来说, 字典序是`a, b, c, d, e, f, g, h, i.....`, 而对于外星英文来说, 就可能不是按照地球的这种字典序, 而是`b, z, x, w, e, r, t, f.........`.

现在有一个字符串列表, 该列表已经根据外星英文的字典序进行了排序, 请你根据这个字符串列表, 推测出可能的外星英文字典序, 返回其中一种即可. 

该字典序的排序规则如下, 我们将进行排序的两个字符串记为`a, b`;

- 当`a, b`两个字符串从左往右可以找到第一个不相同的字符时, 比较这两个不相等的字符, 依据外星字典序进行排序
- 当`a, b`两个字符串找不到不相同的字符时, 若二者长度相同(其实就是完全一样), 可以从二者中任选一个放在前面, 如果二者长度不相同, 则一定是短的在前面, 长的在后面.(对于"ab"和"abc"来说, 一定是"ab"在前, "abc"在后)

注意, 字符串列表可能存在错误情况, 如, 一个字符既在一个字符前面, 又在一个字符后面`["z","x","z"]`, 或者相同前缀的两个字符串, 长的在前面`["abc", "ab"]`, 对于这种情况, 你只需要返回空字符串即可.

先看示例一`["wrt","wrf","er","ett","rftt"]`

首先我们可以看到, `"wrt"`是在`"wrf"`前面的, 这意味着, `t`在`f`前面, 然后再对比`"wrt"`和`"er"`可知, `w`在`e`前面, 比对`"er"`和`"rftt"`来说, 可知, `e`在`r`前面, 最后比对`"er"`和`"ett"`, 可以得到`r`在`t`前面, 所以最后返回的就是`"wertf"`.

再看`["ab","abc"]`

 由于`"ab"`和`"abc"`实际上并不能给我们透露任何信息, 所以`abc`这三个字符实际上可以以任意形式排序.

## solution

我们可以将字符串列表中出现的所有字符抽象成一个个点, 用一个有向图来表示字符之间的先后关系. 为此我们需要挑选出合适的容器来建图.   我们可以很容易想到, 它的邻接表应该是一个字符对应多个字符的集合.   为此我们可以用`unordered_map<char, vector<char>>`, 并且, 由于字符是离散的, 所以`unordered_map<char, unordered_set<char>> edges`明显更好, 对于入度的记录, 同理, 应该使用`unordered_map<char, int> in`,   需要稍微注意的是, 由于`in`是`unordered_map`, 而不是`vector<int>(26)`, 所以在正式开始收集信息之前, 需要把整个字符串列表整个遍历一下, 为`in`进行扩容, 否则到时候找不到入度为零的点.       之后我们就可以正式开始建图了,    使用两层循环, 将列表中的字符串进行两两比对, 收集其中的信息, 比如, 还是示例三, 先比对  `"wrt"`和`"wrf"`, `edges[t].emplace(f), ++in[f]`, 之后是`"wrt"`和`"er"`, 也进行相应的记录, 然后是`"wrt"`和`"ett"`, 需要注意的是,此时可以`edges[w]`, 但决不能`++in[e]`了, 因为这个关系已经记录过了, 不能重复记录.      除此之外, 在这个环节, 里应该提防一下`[......"abc","ab".....]`的情况出现, 一旦出现这种情况, 就意味着字符串表非法了, 你可以直接返回空字符串了. 

在遍历完成之后, 那就可以把入度为零的点扔进队列里, 不断迭代, 通过`edges`找到后续点, 通过`in`修改当前入度, 如果入度已经变为零, 重新压入队列, 最后判断是否所有点都被处理了即可.

## code

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> edges;
        unordered_map<char, int> in;

        for(const auto& word : words)
        {
            for(const char c : word)
            {
                in[c];
            }
        }

        int size = words.size();
        for(int i = 0; i < size; ++i)
        {
            const string& front = words[i];
            for(int j = i + 1; j < size; ++j)
            {
                int k = 0;
                const string& back = words[j];
                int len = min(front.size(), back.size());
                while(k < len && front[k] == back[k]) ++k;
                if(k >= len)
                {
                    if(front.size() > back.size()) return string();
                    continue;
                }                
                char b = front[k], a = back[k];
                if(edges[b].count(a) == 0)
                {
                    ++in[a];
                    edges[b].emplace(a);
                } 
            }
        }

        queue<char> q;
        for(auto [c, n] : in)
        {
            if(n == 0)
                q.emplace(c); 
        }

        string result;
        while(!q.empty())
        {
            char b = q.front(); q.pop();
            result += b;
            for(char a : edges[b])
            {
                --in[a];
                if(in[a] == 0)
                    q.emplace(a);
            }
        }

        if(result.size() == in.size())
            return result;
        else
            return string();
    }
};
```

# end