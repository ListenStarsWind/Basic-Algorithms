# [group-anagrams](https://leetcode.cn/problems/group-anagrams)

![image-20250228215833745](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250228215833855.png)

## overview

现有一字符串数组, 请将其中同组的字母异位词放到一个新的字符串数组中, 并将得到的字符串数组阵列返回.   注: 所谓字母异位词就是可以通过其中字符再排列相互转化的一些词.   

## solution

之前我们写过如何判断字母异位词, 之前我们抓住的重点是字母异位具有在种类和数量对应相等的元素, 但在这里, 这种方法有些太麻烦了, 所以可以换一种思路, 我们可以对字符串进行排序, 对于字母异位词来说, 其排完序的结果都是相同的, 比如, `eat`排完是`aet`, `tea`排完之后还是`aet`, 所以我们可以创建一个哈希表, 哈希表的`key`是排完序的字符串. `val`是对应字母异位词的数组, 并且, `map`的`[]`在无`key`的时候还能自动插入, 所以我们甚至不用做什么判断.

## code

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> hash;
        for(auto& str : strs)
        {
            string temp = str;
            sort(temp.begin(), temp.end());
            hash[temp].emplace_back(str);
        }

        vector<vector<string>> result;
        for(auto& e : hash)
        {
            result.emplace_back(move(e.second));
        }

        return result;
    }
};
```

# end