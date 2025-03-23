# [word-ladder](https://leetcode.cn/problems/word-ladder)

![image-20250323191754229](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250323191754378.png)

## overview

这题其实和上一题, 也就是最小的基因变化完全一样, 没什么好说的. 有三个对象, 一个起始字符串, 一个目标字符串, 一个字典, 现在请尝试讲起始字符串变为目标字符串, 每次变化只能改变字符串中的一个字符, 并且只有改变后的形成的新字符串在字典中, 此次变化才是能被保留的. 最后请返回寻找路径中遇到的字符串个数, 包括起始字符串本身. 

## solution

和上一题一模一样, 略

## code

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int result = 1;
        unordered_set<string> vis;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<string> q;
        q.emplace(beginWord);
        vis.emplace(beginWord);
        while(!q.empty())
        {
            ++result;
            int size = q.size();
            for(int i = 0; i < size; ++i)
            {
                auto curr = q.front();
                q.pop();
                for(int j = 0; j < curr.size(); ++j)
                {
                    char self = curr[j];
                    for(int k = 'a'; k <= 'z'; ++k)
                    {
                        char other = k;
                        if(self == other) continue;
                        string temp = curr;
                        temp[j] = other;
                        if(dict.find(temp) != dict.end())
                        {
                            if(temp == endWord) return result;
                            if(vis.find(temp) == vis.end())
                            {
                                q.emplace(temp);
                                vis.emplace(temp);
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }
};
```

# end