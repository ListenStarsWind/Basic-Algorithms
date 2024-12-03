# [Uncertain Peak](https://leetcode.cn/problems/find-peak-element)

![image-20241203205928211](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412032059317.png)

## overview

题目给我们一个过山车数组，这是我自己的说法。所谓过山车数组，就是其内部可能有多个山脉数组。形象的来说，过山车数组就是一会上升，一会下降，现在的需求是找到峰值位置，或者说，找到数组从上升到下降的那个拐点。为了让该数组无论如何都存在一个峰值，我们约定，逻辑上的`nums[-1]`和`nums[size]`都是`-∞`，又因为数组间相邻元素之间的关系一定是严格单调的，根据介值定理，这意味着肯定存在一个拐点，否则怎么重新回到`-∞`呢？这也暗示，数组实际的第一个元素和最后一个元素一定也可能是峰值点。另外要注意，如果有多个峰值，返回其中的任意一个就行了。

## solution

首先仍旧是暴力解法。我们要分三种情况。

第一种情况。`arr[0] > arr[1]`，此时意味着下标0就是峰值，直接返回即可。

第二种情况。整个数组一直在上升，这样的话，`size - 1`就是峰值位置，直接返回即可。

第三种情况。这就是一般情况，可能在中部的某个位置出现了峰值。

所以暴力破解就是一个个遍历，看下一个元素是否小于现在的元素，如果走到尾，那末尾就是峰值。

---------

接下来是优化方案。我们可以从数组中随机选择一个位置，比如`i`，当`arr[i] > arr[i + 1]`时，说明`[0, i]`区间必然存在一个峰值，否则这里怎么递减的？而当`arr[i] < arr[i + 1]`时，说明`[i+1, size -1]`区间中必然存在一个峰值，否则它怎么回到`-∞`的？也就是说，该数组存在二段性，尽管很抽象，但我们依旧可以使用二分查找。

## code
```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid + 1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};
```
# end