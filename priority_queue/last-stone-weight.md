# [last-stone-weight](https://leetcode.cn/problems/last-stone-weight)

![image-20250314210149997](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314210150149.png)

## overview

给你一个数组, 对其中的元素不断进行如下操作:   从中取出最大的两个数, 用大的减去小的, 如果结果为零, 就不要把零扔回数组, 如果不为零, 就把结果扔回去. 直到已经取不出两个数的时候停止, 如果此时数组中已没有数, 返回零即可, 有, 就返回最后剩下的那个数.

## solution

用优先级队列来每次找出两个元素, 计算结果, 不断循环即可.

## code

```cpp
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> heap(stones.begin(), stones.end());
        while(heap.size() > 1)
        {
            auto first =  heap.top();
            heap.pop();
            auto second = heap.top();
            heap.pop();
            auto ret =  first - second;
            if(ret != 0)
                heap.emplace(ret);
        }

        if(heap.empty())
            return 0;
        else
            return heap.top();
    }
};
```

# end