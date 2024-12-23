# [is-unique-lcc](https://leetcode.cn/problems/is-unique-lcci)

![image-20241223211703279](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241223211703455.png)

## overview

题目简单易懂，不作二次概述。注意字符串的长度在100以内。

## solution

第一种，创建一个元素个数为26的静态数组作为哈希表，逐个遍历字符串中的字符即可，先看这个字符在不在哈希表中，有，就返回假，无就继续迭代记录。

第二种，将静态数组直接优化成位图，这样只要一个`int`变量就可以表示所有的小写字母，我们约定，该整型的第一位映射字符`a`，次低位映射字符`b`，依旧是遍历整个字符串，先看对应比特位是否为1，为1就说明该位置之前已经有过相同字符，于是就可以返回假，每次检查之后记录哈希状态。

最后还可以稍微优化一下，小写字母一共有26个，如果字符串长度大于26，则说明一定会有重复，所以就可以直接返回假。

## code

```cpp
class Solution {
public:
    bool isUnique(string astr) {
        if (astr.size() > 26)
            return false;

        int bitMap = 0;
        for (auto ch : astr) {
            int i = ch - 'a';

            if ((bitMap >> i) & 1)
                return false;
            bitMap |= (1 << i);
        }
        return true;
    }
};
```

# end