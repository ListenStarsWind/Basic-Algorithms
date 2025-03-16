# [top-k-frequent-words](https://leetcode.cn/problems/top-k-frequent-words)

![image-20250316181023682](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250316181023822.png)

## overview

这道题仍旧是TopK的变形, 特点在于存在多套规则.

题目给我们一个字符串数组, 在这个数组中, 这样的字符是被视为"大的": 出现频次高, 就大, 若频次相同, 则字典序在前的大.   最后请你返回一个字符串数组, 将前K个大的字符串以从大到小的顺序在数组中排列.

对于示例一来说, `i and love`都出现了两次, 所以它们相比只出现一次的`leetcode`来说, 是大的. 而在`i and love`内部, 因为`i`排在`love`前面, 所以`i`是更大的, 因此返回的是`[i, love]`

## solution 

本题在算法思路上还是很简单的, 先用哈希表将字符串数组中的元素进行统计, 弄清它们出现的次数. 然后, 因为这里是寻找前K大的, 所以使用的是小根堆, 小根堆需要特别写一下`greater`, 到时候直接写就行了. 之后就是让堆的元素根数变为k, 提取出来扔到数组里就行了. 需要注意的是, 由于它是小根堆, 所以拿出来是升序, 但我们要的是降序, 所以我们要倒着填.

## code

```cpp
class Solution {

    struct greater
    {
        bool operator()(const pair<string, int>& m, const pair<string, int>& n)
        {
            if(m.second == n.second)
            {
                return !(m.first > n.first);
            }
            else
                return m.second > n.second;
        }
    };

public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> hash;
        for(const auto& word : words)
        {
            ++hash[word];
        }

        priority_queue<pair<string, int>, vector<pair<string, int>>, greater> heap;
        for(const auto& e : hash)
        {
            heap.emplace(e);
        }

        while(heap.size() > k)
            heap.pop();

        vector<string> result(k);
        int i = k;
        while(heap.size())
        {
            result[--k] = heap.top().first;
            heap.pop();
        }

        return result;
    }
};
```

# end