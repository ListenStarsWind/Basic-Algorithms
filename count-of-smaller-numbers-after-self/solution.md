# [count-of-smaller-numbers-after-self](https://leetcode.cn/problems/count-of-smaller-numbers-after-self)

![image-20250218094800477](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250218094800586.png)

## overview

这道题其实和上一道题<逆序对>非常相似, 只是细节有所不同, 可以说上一道题求得是"集中式"逆序对个数, 而本道题求得是"分布式"逆序对个数, 所以就会在细节上有所不同, 总的来说, 主要思路都是相同的, 关键在于如何实现"分布式"的形式.

## solution

我们的思路仍然是归并排序, 很明显, 这道题求的是当前元素的后面有几个比它小的元素, 这很明显, 应该使用降序的方式来实现, 当然, 倒也不是说升序不能作, 但很明显, 降序在逻辑上更加简单, 所以我们用的还是降序方式.

现在, 我们假设已经将数组分成了两个降序的子数组.

![image-20250218101027957](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250218101028012.png)

当`m > n`时, 就说明`n`后面的那些元素也小于`m`, 于是我们就可以对`counts`中的对应位数据进行更新, 再把`m`写到辅助数组中, 之后, `m`指向下一个元素, 而当`m < n`的时候, `n`指向下一个元素, `n`写入辅助数组即可.

现在有个关键问题需要解决, 该如何找到`counts`中的对应位?   因为在排序的过程中, 有可能改变数组中元素的位置, 但我们最后需要的`counts`, 是依据元素初始位置进行排列的, 所以, 找对应位就变成了一个难题. 

我们把题目中的第一个示例稍微改动一下,  假设, 我们最开始输入的数组是`[2, 5, 6, 1]`, 在某个时间点, 它被分成了两个降序子数组`[5, 2], [6, 1]`, 依照上面的思路我们很明显可以得出`2`对应的`count`是`1`, 但是`2`的位置是发生变化的, 你不能把`1`放在`2`现在的对应位上, 而是要把`1`放在`2`原来的位置上. 那么, 问题就来了, 该如何知道元素原来的位置.

解决思路其实很简单, 但不容易想到, 那就是再创建一个下边数组, 还是`[2, 5, 6, 1]`,  我们最开始创建一个下边数组`[0, 1, 2, 3]`用来表示元素的原始下标, 然后, 将下标数组中的元素和`nums`中的元素在位置上绑定移动, `nums`中的元素怎么移动, `index`中的元素也作相同移动, 这样当来到`[5, 2], [6, 1]`的时候, 对应的下标数组就是`[1, 0, 6, 1]`,   这样就可以知道`nums`中元素的原始位置了,  由于`index`中的元素和`nums`中的元素有着相同的移动方式, `nums`有对应的辅助数组, 则`index`也有对应的辅助数组. 

## code

```cpp
class Solution {

    void merge(vector<int>& nums, vector<int>& index, int left, int right,
               vector<int>& nums_temp, vector<int>& index_temp,
               vector<int>& counts) {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        merge(nums, index, left, mid, nums_temp, index_temp, counts);
        merge(nums, index, mid + 1, right, nums_temp, index_temp, counts);

        int i = left, j = mid + 1;
        int k = left;
        while (i <= mid && j <= right) {
            if (nums[i] > nums[j]) {
                counts[index[i]] += right - j + 1;

                nums_temp[k] = nums[i];
                index_temp[k] = index[i];
                k++;

                i++;
            } else {
                nums_temp[k] = nums[j];
                index_temp[k] = index[j];
                k++;

                j++;
            }
        }

        while (i <= mid) {
            nums_temp[k] = nums[i];
            index_temp[k] = index[i];
            i++;
            k++;
        }

        while (j <= right) {
            nums_temp[k] = nums[j];
            index_temp[k] = index[j];
            j++;
            k++;
        }

        for (int i = left; i <= right; i++) {
            nums[i] = nums_temp[i];
            index[i] = index_temp[i];
        }
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        size_t size = nums.size();
        vector<int> index(size);
        vector<int> counts(size);
        vector<int> nums_temp(size);
        vector<int> index_temp(size);

        for (size_t i = 0; i < index.size(); i++) {
            index[i] = i;
        }

        vector<int> arry = nums;

        merge(arry, index, 0, arry.size() - 1, nums_temp, index_temp, counts);

        return counts;
    }
};
```

## end