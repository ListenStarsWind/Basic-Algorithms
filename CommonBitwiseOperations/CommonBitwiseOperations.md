# Common Bitwise Operations

## 基础位运算

考虑到`<< >> ~`已经说过，所以这里不再赘述，下面我们来看`& | ^`这三种位运算。

`&`按位与，有0就是0，`|`按位或，有1就是1，`^`按位异或有两种记忆方法，一是相同为0，相异为1，二是无进位相加。

![image-20241221165418874](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221165419039.png)

## 判断二进制序列指定位的状态

![image-20241221170937301](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221170937345.png)

## 确保二进制序列指定位为1

![image-20241221171857720](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221171857752.png)

## 确保二进制序列指定位为0

![image-20241221172634533](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221172634560.png)

## 位图

当某个事物的状态只有两种时，就可以根据二进制序列的每个比特位的01与否分别表示这两种状态，把空间利用率榨干。

## 提取二进制序列最右侧的1

![image-20241221175348568](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221175348604.png)

## 将二进制序列最右侧1变为0

![image-20241221180033786](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221180033819.png)

## 优先级

不要记优先级，多加括号。

## 异或运算律

`a^0 = a, a^a = 0, a^b = b^a`

异或具有交换律，因为异或是不进位相加。加法是具有交换律的，1+1=0，它不管这两个1到底具体是从哪里来的(假如有一堆二进制序列异或);

## [位 1 的个数](https://leetcode.cn/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/)

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for(int i = 0; i < 32; i++)
            if((n>>i)&1) count++;
        return count;
    }
};
```

## [比特位计数](https://leetcode.cn/problems/counting-bits/)

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for (int i = 0; i < 32; i++)
            if ((n >> i) & 1)
                count++;
        return count;
    }
    vector<int> countBits(int n) {
        vector<int> ret;
        for (int i = 0; i <= n; i++)
            ret.push_back(hammingWeight(i));
        return ret;
    }
};
```

## [汉明距离](https://leetcode.cn/problems/hamming-distance/)

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for (int i = 0; i < 32; i++)
            if ((n >> i) & 1)
                count++;
        return count;
    }
    int hammingDistance(int x, int y) {
        int n = x ^ y;
        return hammingWeight(n);
    }
};
```

## [只出现一次的数字](https://leetcode.cn/problems/single-number/)

```cpp
public:
    int singleNumber(vector<int>& nums) {
        int val = 0;
        for(auto curr : nums)
            val ^= curr;
        return val;
    }
};
```

## [只出现一次的数字 III](https://leetcode.cn/problems/single-number-iii/)

```cpp
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        long long xorSum = 0; // 用于存储所有元素的异或结果
        for (int num : nums)
            xorSum ^= num;

        // 找到 xorSum 中的最低有效位（最右侧的 1）
        long long diffBit = xorSum & -xorSum;

        long long num1 = 0, num2 = 0; // 存储两个单独出现的数
        for (int num : nums) {
            if (num & diffBit)
                num1 ^= num;
            else
                num2 ^= num;
        }

        int ret1 = num1;
        int ret2 = num2;

        return {ret1, ret2};
    }
};
```

# end