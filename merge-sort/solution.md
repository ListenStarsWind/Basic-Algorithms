# [merge-sort](https://leetcode.cn/problems/sort-an-array)

![image-20250113094237300](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250113094237456.png)

## overview

上次我们拿这道题写了快排, 这次我们用归并排序.

## solution

归并排序的核心仍旧是分治, 它将数组不断地分成一个个小数组, 直到数组天然有序, 此时再对相邻两个有序数组进行合并, 这样就将这两个小的数组合成了一个较大的有序数组, 两个较大有序数组继续合并又可以生成一个更大的有序数组, 继续下去, 就能把整个数组进行合并了.

## code

```cpp
class Solution {
    // 内部函数：递归实现归并排序
    void mergeSort(vector<int>& nums, int left, int right, vector<int>& temp) {
        if (left >= right) {
            return; // 递归终止条件
        }

        int mid = left + (right - left) / 2; // 防止溢出的写法
        mergeSort(nums, left, mid, temp);    // 排序左半部分
        mergeSort(nums, mid + 1, right, temp); // 排序右半部分

        // 合并两个已排序的区间
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }

        // 处理剩余元素
        while (i <= mid) {
            temp[k++] = nums[i++];
        }
        while (j <= right) {
            temp[k++] = nums[j++];
        }

        // 将合并后的结果拷贝回原数组
        for (int idx = left; idx <= right; ++idx) {
            nums[idx] = temp[idx];
        }
    }

public:
    // 主函数：对数组进行归并排序
    vector<int> sortArray(vector<int>& nums) {
        vector<int> temp(nums.size()); // 辅助数组，用于归并操作
        mergeSort(nums, 0, nums.size() - 1, temp);
        return nums;
    }
};

```

