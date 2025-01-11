# [topK](https://leetcode.cn/problems/kth-largest-element-in-an-array)

![image-20250111123137775](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250111123137838.png)

## overview

针对`topK`问题, 有两种主流解决思路, 第一种, 就是堆排序, 第二种就是快速选择算法,.   堆排序的时间复杂度是$O(N*log_2N)$, 但题目的要求是$O(N)$, 所以我们需要使用快速选择算法.  关于快速选择算法时间复杂度的证明, 详见<算法导论>.

## solution

快速选择算法是基于快速排序分治思想的选择算法.  一个数组在经过快排的分治阶段之后, 会被划分成三个部分, 它们分别是小于基准值的部分, 等于基准值的部分, 大于基准值的部分, 当大于基准值的部分元素个数大于或者等于`k`时, 说明我们想找的第`k`个就在这一部分, 所以就要在这部分继续查找, 当大于基准值部分元素个数小于`k`时, 先看不小于基准值部分的元素个数, 如果它大于等于`k`, 则说明, 第`k`个就是基准值, 此时直接返回基准值即可, 当前面的两个分支都不成立时, 说明, 第`k`个, 在小于基准值的那部分中, 此时就要去这部分继续寻找, 注意, 此时`k`的只将发生变化, 因为我们已经把不小于基准值部分的那些元素都给淘汰掉了, 所以, `k`要减去这部分元素的个数.

## code

```cpp
// 堆排序
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        while(--k)
        {
            pq.pop();
        }
        return pq.top();
    }
};


// 快速选择算法
class Solution {
    int quickSelect(vector<int>& nums, int k, long long left, long long right)
    {
        int pivot = nums[left + rand() % (right - left + 1)];
        long long low = left - 1, mid = left, high = right + 1;
        
        while (mid < high)
        {
            if (nums[mid] < pivot)
            {
                swap(nums[mid++], nums[++low]);
            }
            else if (nums[mid] > pivot)
            {
                swap(nums[mid], nums[--high]);
            }
            else
                mid++;
        }

        // 计算大于基准值部分的元素个数
        long long greaterThanPivotSize = right - high + 1;
        // 计算不小于基准值部分的元素个数（包括等于和大于基准值的部分）
        long long notLessThanPivotSize = right - (low + 1) + 1;

        if (greaterThanPivotSize >= k)  
            return quickSelect(nums, k, high, right);
        else if (notLessThanPivotSize >= k)  
            return pivot;
        else 
            return quickSelect(nums, k - notLessThanPivotSize, left, low);
    }

public:
    int findKthLargest(const vector<int>& nums, int k) {
        vector<int> tmp = nums;
        srand(time(nullptr));
        return quickSelect(tmp, k, 0, tmp.size() - 1);
    }
};

```

