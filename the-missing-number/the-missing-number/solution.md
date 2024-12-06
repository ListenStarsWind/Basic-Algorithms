# [the-missing-number](https://leetcode.cn/problems/que-shi-de-shu-zi-lcof)

![image-20241206084333438](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206084333661.png)

## overview

题目为我们提供了一个严格升序数组，当数组个数为五时，相当于从0到5选出六个整数，去掉其中一个数，将其有序排列在数组上。例如示例一，`records = [0,1,2,3,5]`，数组的个数为5，即从0,1,2,3,4,5中抽出一个数，将其排列在数组中，而我们要找的就是丢失的那个数字。

## solution

本题有多种解法，且各种解法之间没有特别明显的优劣，所以我们一个个数。

第一种是哈希表。我们创建一个比数组大小大一个单位的哈希表，随后遍历一遍数组，再遍历一遍哈希表，就能找到丢失的数字。

第二种是直接遍历。依据数组下标从前往后遍历，因为数组严格升序，所以第一个数组内容和下标不相等的时候就找到了丢失的数字，就是此时的下标。

第三种是按位异或。异或是相异为真，相同为假，这意味着，0和任何数按位异或后得到的仍然是这个数，而两个相同的数按位异或后就会得到0。比如对于`[0,1,2,3,5]`来说，它的数组大小为5，那么就可以从0到5按位异或，然后再把数组中的内容接着之前的结果按位异或，最后得到的结果就是丢失的数字。

第四种是等差数列求和公式。如果数组没有丢失数字，那就是一个公差为1，首项为0的等差数列，我们可以很轻松地求出它们的和，然后拿这个和减去实际数组中所有元素的和即可。

第五种二分查找。比如对于`[0,1,2,3,5]`来说，可以把数组分成两个部分，一是`[0,1,2,3]`，二是`[5]`，我们看第一个部分，`[0]`的下标是0，`[1]`的下标是`[1]`，`[2]`的下标是2，`[3]`的下标是3，而对于第二个部分来说，`[5]`的下标是4。所以当数组内容与其对应下标相等时，意味着`mid`在第一个部分，所以`left = mid + 1`，如果`mid`在第二个部分，那么`right = mid`。这就是二分查找的核心思路，除此之外，还要稍微优化一下，比如对于`[0,1,2,3,4]`来说，丢失的是0到5中的某个数，也就是它丢失的就是5，所以当最后二分结果是数组的最后一个位置时，实际结果就应该是二分结果加一。

## code

```cpp
class Solution {
public:
    int takeAttendance(vector<int>& records) {
        int expected = records.size() + 1;
        vector<int> hash;
        hash.resize(expected, 0);
        for(const auto& e : records)
            hash[e]++;
        for(int i = 0; i < expected; i++)
        {
            if(hash[i] == 0)
            return i;
        }
        return -1;
    }
};
```

```cpp
class Solution {
public:
    int takeAttendance(vector<int>& records) {
        int i = 0;
        for( ; i < records.size(); i++)
        {
            if(records[i] != i)
                break;
        }
        return i;
    }
};
```

```cpp
class Solution {
public:
    int takeAttendance(vector<int>& records) {
        int i = 0;
        for(int j = 0; j <= records.size(); j++)
            i ^= j;
        for(const auto& e : records)
            i ^= e;
        return i;
    }
};
```

```cpp
class Solution {
public:
    int takeAttendance(vector<int>& records) {
        int i = (0 + records.size()) * (records.size() + 1) /2;
        int j = 0;
        for(const auto& e : records)
            j += e;
        return i - j; 
    }
};
```

```cpp
class Solution {
public:
    int takeAttendance(vector<int>& records) {
        int left = 0, right = records.size() - 1;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(records[mid] == mid)
                left = mid + 1;
            else
                right = mid;
        }

        if(records[left] == left)
            return left + 1;
        else
            return left;
    }
};
```

# end