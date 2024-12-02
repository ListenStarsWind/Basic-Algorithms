# [peak](https://leetcode.cn/problems/peak-index-in-a-mountain-array)

![image-20241202203035583](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412022030630.png)

## overview

题目给我们一个山脉数组，什么是山脉数组，山脉数组中的元素遵循着先上升再下降的规律。例如示例一，从`0`到`1`是上升，从`1`到`0`是下降，我们需要找到最高点的下标索引，所以示例一返回下标1，至于示例二，最高点是`2`，所以返回下标一。

## solution

最开始，仍是暴力破解。很明显，对于最高点，有大于前一个元素，也大于后一个元素的性质，由于山峰数组一定是先上升再下降的，所以我们只需要找到一个大于后一个元素的位置即可，那我们就可以从数组的起始位置开始，向后逐个遍历，找到该最高点即可。

接下来，我们可以对暴力破解进行优化。我们发现，最高点可以把数组分为两个部分，为方便起见，我们记最高点的下标为`peak`，则该数组就可以被分为`[0, peak]`和`[peak + 1, size -1]`这两个部分，对于处于前一个区间的元素来说，始终有，前一个元素严格小于后一个元素，即`arr[i - 1] < arr[i] `，而对于后一个区间来说，始终有，前一个元素严格大于后一个元素，即`arr[i - 1] > arr[i]`，所以，山脉数组具有二段性，可使用二分查找。

当`arr[mid] > arr[mid -1]`时，`left = mid`，当`arr[mid] < arr[mid - 1]`时，`right = mid -1`。

## code
```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 0 , right = arr.size() -1;
        while(left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if(arr[mid] > arr[mid - 1])
                left = mid;
            else
                right = mid -1;
        }
        return left;
    }
};
```
考虑到最高点一定不位于数组首尾，如果位于的话，那就满足不了山脉数组先升后降的性质了，所以稍微修改一下也行。

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 2;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (arr[mid] > arr[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }
};
```

# end