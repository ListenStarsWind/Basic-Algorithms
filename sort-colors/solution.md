# [sort-colors](https://leetcode.cn/problems/sort-colors)

![image-20250109172604591](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250109172604669.png)

## overview

今天我们进入一个新的章节, 分治. 所谓分治就是分而治之, 将一个问题, 转化为相同或者类似的小问题, 再将这个小问题转化为规模更小的同类题型, 最终, 会转化出一个非常简单的小问题,  从而解决整个问题.   在以往我们学习的排序算法中, 快排和归并就是典型的分治思想. 

本题其实和分治没有太大的关系, 而是和快排的一部分有关系.  我们知道最基本的快排是将数据分成三部分,   一部分是小于某个基准值, 另一部分是大于相同的基准值, 而基准值就是第三部分,   有人将需要被序列的序列划分成如上三部分的过程称之为"三路划分".  本道题其实考的就是三路划分.

给你一个数组,  该数组中有三种元素,  `0, 1, 2`, 现需要你对其进行递增排序.

## solution

其实模拟一下即可. 我们使用三指针法,  对数组元素进行遍历即可. 以示例一为例.

共有三个指针, 它们分别是`left  idx  right`,  这三个指针可以把数组划分为四个部分, 第一部分是`[0, left]`, 其中存放的小于基准值的元素, 第二部分是`[left+1, idx - 1]`, 存放的是基准值, 第三部分是`[idx, right - 1]`, 表示未检查的部分, 第四部分是`[right size-1]` 表示大于基准值的部分;初始阶段, `left`为`-1`, `right`为`size`, `idx`为`0`,  随后`idx`向后进行迭代.

当`idx`指向的元素小于基准值时, 先将`left+1`指向的元素与`idx`交换, 由于交换过来的元素已经被`idx`检查过了,  所以`idx+=1`,  如果`idx`指向的元素就是基准值, 那么, 继续`idx+=1`, 检查下一个元素即可,  如果`idx`指向的元素大于基准值, 那么就需要让`idx`指向的元素先与`right - 1`交换位置, 然后由于被换过来的元素还未被检查, 所以一定不能让`idx+=1`,  当`idx = right`时, 说明未检查的部分已经不存在了, 或者说, 所有元素都被遍历过一遍, 它们都去了应该去的部分, 因此, 可以退出循环了.

## code

```cpp
class Solution {
    public:
    void sortColors(vector<int>& nums) {
        size_t len = nums.size();
        size_t left = -1;
        size_t idx = 0;
        size_t right = len;
        while(idx < right)
        {
            if(nums[idx] < 1)
                swap(nums[++left], nums[idx++]);
            else if (nums[idx] > 1)
                swap(nums[--right], nums[idx]);
            else
                idx++;
        }
    }
};
```

# end