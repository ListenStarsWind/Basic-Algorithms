# [quickSort](https://leetcode.cn/problems/sort-an-array)

![image-20250111111609746](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250111111609969.png)

## overview

其实没什么好说的, 就是排序.  下面我们将使用快速排序来解决该题

## solution

在上一道题, 颜色排序中,  我们已经说明了最关键的三路划分步骤. 下面我们一笔跳过, 首先使用三路划分将待排数组划分为三个部分, 随后再分别对一三这两个部分继续排序即可.  当排序区间不合法时, 就停止排序.

需要另外说明的是, 基准值的选取有多种方案, 我们这里使用的是随机选取方案. 据说这种方案效率更高, 似乎在<算法导论>这本书中有相应证明.  我们使用伪随机函数`rand()`生成一个随机数, 然后对该随机数进行数组长度取余, 求出偏移量, 别忘了再加上左指针, 因为这是偏移量, 以左指针为开始的偏移量.

## code

```cpp
class Solution {
    void quickSort(vector<int>& nums, long long left, long long right)
    {
        if (left >= right)
            return;

        int pivot = nums[left + rand() % (right - left + 1)];
        long long smaller = left - 1, current = left, larger = right + 1;
        while (current < larger)
        {
            if (nums[current] < pivot)
            {
                swap(nums[current++], nums[++smaller]);
            }
            else if (nums[current] > pivot)
            {
                swap(nums[current], nums[--larger]);
            }
            else
                current++;
        }

        quickSort(nums, left, smaller);
        quickSort(nums, larger, right);
    }

public:
    vector<int> sortArray(const vector<int>& nums) {
        vector<int> result = nums;
        srand(time(nullptr));
        quickSort(result, 0, result.size() - 1);
        return result;
    }
};

```

考虑到`vector`的`size`是用`size_t`进行计数的, 所以我们的下标为`long long`为准, 下标不使用`size_t`的原因是, 在排序过程中, 可能会出现负数, 所以一定要是有符号的, `long`在`32`或者`64`位系统是有区别的, `long long`不看系统位数, 更加安全.

另外, 力扣这题有些问题,  日常的排序应该是直接排, 但力扣给的接口很像是要保证原数组不变, 实际上都应该是直接排序的, 另外那个`const`是我自己加的.