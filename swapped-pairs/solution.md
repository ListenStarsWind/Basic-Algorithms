# [swapped-pairs](https://leetcode.cn/problems/reverse-pairs)

![image-20250219112627898](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250219112628024.png)

## overview

本题和逆序对那道题一脉相承, 从数组中找出两个数, 前一个数比后一个数的二倍还要大.

## solution

还是像往常一样, 我们可以在归并排序的过程中解决本题, 可以把数组分成两个有序的子数组, 之后再依据子数组的有序性进行计数, 需要注意的是, 由于本题的比较比例不再像往常那样是`1 : 1`, 所以计数环节无法融合在排序环节中, 所以我们要把计数环节独立出来, 在排序环节之前进行.

具体的实现策略有两条

- 降序环境下, 计算当前元素后面, 有多少元素的两倍比我小
- 升序环境下, 计算当前元素之前, 有多少元素的一半比我大

以降序为例, 现在我们已经把原来的数组分成了两个降序数组, 左右两个指针分别指向子数组的开头, 当右元素的两倍大于左元素时, 右指针指向下一位, 当右元素的两倍小于左元素时, 由于数组降序排列, 所以右元素后面的元素也必然满足"重要翻转对"的要求, 之后, 左指针向后移动, 我们知道之前的右元素两倍必然大于原来的左元素, 而现在左元素变小了, 因此, 之前右元素两倍必然大于现在的左元素, 也就是, 右指针不必回档重新开始, 还是在原来位置的基础上进行移动.

对于升序来说, 当左元素的一半比右元素小时, 左指针向后遍历, 而当左元素一半比右元素大时, 则意味着左元素后面的一半也比右元素大, 进行计数, 之后, 右指针向后移动, 左指针不变.

需要特别强调的是, 整型乘2存在溢出风险, 所以我们要把乘法变成除法. 

## code

```cpp
class Solution {
    void merge(vector<long long>& nums, int left, int right, vector<int>& temp, int& count)
    {
        if(left >= right)
            return ;

        int mid = left + (right - left) / 2;
        merge(nums, left, mid, temp, count);
        merge(nums, mid + 1, right, temp, count);

        int i, j, k = left;
        for(i = left, j = mid + 1; i <= mid && j <= right; )
        {
            if(nums[i] / 2.0 >  nums[j])
            {
                count += right - j + 1;
                i++;
            }
            else
            {
                j++;
            }
        }

        for(i = left, j = mid + 1; i <= mid && j <= right; )
        {
            if(nums[i] > nums[j])
            {
                temp[k++] = nums[i++];
            }
            else
            {
                temp[k++] = nums[j++];
            }
        }

        while(i <= mid)
        {
            temp[k++] = nums[i++];
        }

        while(j <= right)
        {
            temp[k++] = nums[j++];
        }

        for(k = left; k <= right; k++)
        {
            nums[k] = temp[k];
        }
    }

public:
    int reversePairs(vector<int>& nums) {
        size_t size = nums.size();
        vector<long long> array(nums.begin(), nums.end());
        vector<int> temp(size);
        int count = 0;
        merge(array, 0, size - 1, temp, count);
        return count;
    }
};


class Solution {
    int temp[50000];

    int mergeSort(vector<int>& nums, int left, int right)
    {
        if(left >= right)
            return 0;

        int count = 0;
        int mid = left + (right - left) / 2;
        count += mergeSort(nums, left, mid);
        count += mergeSort(nums, mid + 1, right);

        int i, j, k = left;
        for(i = left, j = mid + 1; i <= mid && j <= right; )
        {
            if(nums[i] / 2.0 >  nums[j])
            {
                count += mid - i + 1;
                j++;
            }
            else
            {
                i++;
            }
        }

        for(i = left, j = mid + 1; i <= mid && j <= right; )
        {
            if(nums[i] > nums[j])
            {
                temp[k++] = nums[j++];
            }
            else
            {
                temp[k++] = nums[i++];
            }
        }

        while(i <= mid)
        {
            temp[k++] = nums[i++];
        }

        while(j <= right)
        {
            temp[k++] = nums[j++];
        }

        for(k = left; k <= right; k++)
        {
            nums[k] = temp[k];
        }

        return count;
    }

public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};
```

# end