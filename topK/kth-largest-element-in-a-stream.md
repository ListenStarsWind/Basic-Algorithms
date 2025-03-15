# [kth-largest-element-in-a-stream](https://leetcode.cn/problems/kth-largest-element-in-a-stream)

![image-20250315192837616](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250315192837818.png)

## overview

本题是TopK问题的变形, 对于TopK问题来说, 有两种主流思路, 一是使用堆, 二是使用快速选择算法. 

题目中的注意, 意思是说, 如果有相同的元素, 它们的个数是分别计算的, 而不是算作一个. 

现在我们来看示例一, 首先我们得到一个数组, 是`[4, 5, 8, 2]`, 这个数组的元素个数一定大于`k`, 然后我们进行若干轮循环, 每次循环, 往数组中新加入一个元素, 你需要在加入元素后, 把第`k`大的元素返回. 比如, 第一次添加了`2`, 数组就变成了`[4, 5, 8, 2, 2]`, 第三大的是`4`, 第二次加入`10`. 数组变为`[4, 5, 8, 2, 2, 10]`, 其中第三大的元素是`5`, 第三次加入`9`, 数组变为`[4, 5, 8, 2, 2, 2, 10, 9]`, 第三大的元素是`8`, 最后加入`9`, 变为`[4, 5, 8, 2, 2, 2, 10, 9, 9]`, 第三大的是`8`. 

## solution

如果弄清了TopK的堆解法, 这题就很简单, 如果要找第k大的数, 那就要用小堆, 让小堆一直保持k个元素, 因为, 只有堆顶的元素是我们可以操作的, 对于元素个数为k的小根堆, 堆顶就是这k个数里面最小的, 其它的数都比堆大, 那堆顶不就是第k个大的数吗? 

## code

```cpp
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> _heap;
    int _k;

public:
    KthLargest(int k, vector<int>& nums) :_heap(nums.begin(), nums.end()), _k(k) {
        while(_heap.size() > _k)
            _heap.pop();
    }
    
    int add(int val) {
        _heap.emplace(val);
        if(_heap.size() > _k)
            _heap.pop();
        return _heap.top();
    }
};

```

# end