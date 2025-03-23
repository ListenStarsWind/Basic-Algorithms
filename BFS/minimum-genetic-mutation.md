# [minimum-genetic-mutation](https://leetcode.cn/problems/minimum-genetic-mutation)

![image-20250323095419425](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250323095419523.png)

## overview

这是一道生物题, 里面有三个对象, 第一个对象是原始基因, 第二个对象是目标基因, 第三个对象是一个基因库.  基因库中存放着那些能在自然环境下存活并且可以正常繁殖的那些基因, 意思就是说, 如果一个基因不在基因库里, 要么它根本无法在自然环境下存活, 要么即使存活了, 也因为无法繁殖, 所以不能把自已的基因传递下去, 更别说变化了.

题目想让我们求的是从原始基因到目标基因的最小变化次数, 一个基因由八个碱基构成, 其中的每个碱基都只能是`'A', 'C', 'G', 'T'`中的一个, 每次变化都只能变化一个碱基, 当突变出的新基因不在基因库中, 它便被自然淘汰, 因此它所在的这条进化路径就中断了.        原始基因默认是在基因库中的, 但也不排除由人工干预形成, 从而不在基因库中的情况.

比如我们看示例二, 原始基因是`AACCGGTT`, 目标基因是`AAACGGTA`, 基因库的内容是`"AACCGGTA","AACCGCTA","AAACGGTA"`, 我们可以闭着眼变, 从第一个碱基开始, 把它变成其它三个碱基, 但为了节约时间, 这里就不这样做了, 我们可以一眼看出, 第三个碱基和第八个碱基是不一样的, 如果第三个碱基和第八个碱基变不出来, 我们再尝试其它点位, 首先我们可以把第三个碱基变为`A`, 这样就是`"AAACGGTT"`, 但这种基因并不在基因库中, 所以它被淘汰了, 然后原本就是`C`, 所以我们可以直接跳过去, 至于变成`G`和`T`, 我们也可以看到, 不在基因库中, 所以接下来看第八个碱基, 首先我们可以把`T`变成`A`, 而`AACCGCTA`也确实是存在的, 所以保留下来, 至于`C`, `G`, 也可以很明显看出不在基因库中, 所以也被淘汰了, 然后`AACCGCTA`可以直接变成`AAACGGTA`, 所以就结束了, 变化次数是二

## solution

这道题很明显可以被转化成一个边权为一的最短路径问题, 从原始基因开始, 有八个碱基, 所以可以延伸出八个分支, 这是我们还是看示例二, 其它点位我们就不考虑了, 我们只看第三个和第八个点位, 对于第三个分支来说, 它又可以分成三个小分支, 因为一共有四种碱基, 除去它自己, 剩下的不就三个吗, 但三个小分支, 都被自然淘汰了,    第八个分支, 也可以细分成三个小分支, 其中只有一个是有效的, 它继续延伸, 就到了目标基因.

## code

```cpp
class Solution {
    char d[4] = {'A', 'C', 'G', 'T'};
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        unordered_set<string> alive(bank.begin(), bank.end());

        int result = 0;
        queue<string> q;
        unordered_set<string> existing;
        q.emplace(startGene);
        existing.emplace(startGene);
        while(!q.empty())
        {
            ++result;
            int size = q.size();
            for(int i = 0; i < size; ++i)
            {
                auto curr = q.front();
                q.pop();
                for(int j = 0; j < 8; ++j)
                {
                    auto self = curr[j];
                    for(int k = 0; k < 4; k++)
                    {
                        auto other = d[k];
                        if(self == other) continue;
                        string temp = curr;
                        temp[j] = other;
                        if(alive.find(temp) != alive.end())
                        {
                            if(temp == endGene) return result;
                            if(existing.find(temp) == existing.end())
                            {
                                existing.emplace(temp);
                                q.emplace(temp);
                            }
                        }
                    }
                }
            }
        }
        return -1;
    }
};
```

# end