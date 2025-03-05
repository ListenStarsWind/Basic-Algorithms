# [multiply-strings](https://leetcode.cn/problems/multiply-strings)

![image-20250305095733995](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305095734086.png)

## overview

本题仍是高精度运算题,   可能存在很大的数, 大到无法用计算机中的广义整数类型进行存储,   对于这些数, 可以把它们转换为字符串, 以字符串的形式进行计算.      本题就是一道字符串相乘,  注意, 这两个数都是非负数, 不需要考虑负数情况.

## solution

本题有两种主流思路,  它们都是基于模拟算法实现的.   其中第二种是第一种的优化.

第一种, 就是模拟我们以往的"列竖式运算"

![image-20250305102140955](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305102141040.png)

对于"列竖式"来说, 可以分为两个关键操作, 一是从下面锁定一个数, 然后与上面的数相乘, 比如锁定`3`, 与`456`相乘就可以得到`1368`,二是将得到的结果进行相加,   我们可以准备一个临时字符串, 将`1368`存下来,  然后与最终返回的字符串`result`进行字符串相加, 并将结果存入`result`.

在此过程中, 有若干点需要注意, 一是首先要对两个字符串进行逆序, 二是对于高位相乘需要在低位补上`0`,  比如`2 * 456`, 得到`912`, 但实际上是`9120`,  因为我们都是以逆序进行的, 所以要在正式运算前将`0`补齐,  三是要处理前导零, 题目只是说这两个是非负数, 所以存在某个数和零相乘的可能性, 此时最后会出现很多零, 但我们只要保留最低位的零就行了.

第二种,  也是列竖式, 但和我们在数学课上学的列竖式有些不相同, 它是无进位列竖式.

![image-20250305112053893](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305112054002.png)

相当于是把进位留到最后再进行.

首先我们创建一个元素个数为`size2 + size1 - 1`的数组, `size2`是第一个字符串(`num2`)`456`的元素个数, `size1`是第二个字符串(`num1`)`123`的元素个数,  为什么这样算呢? `vector<int>`的大小是由最后一行中间结果(图中的"456")决定的,   我们使用的是无进位,  所以元素的个数只要看乘多少次就行了,   `num2` 有三个元素, 那`num1`的最高位就要乘三次, 所以就要有三个元素的位置, 但这个`456`是没有补零的, 补零的个数就是`size1 - 1`.

在进行元素相加的时候, 下标的确定很简单, `3 * 6`得`18`, 它们的下标和是`0`, 那就把`18`放进(以自加的方式)`vector[0]`,  `3 * 5`的`15`, 下标和是`1`, 那就`vector[1] += 15`...... 再比如`2 * 6`, 下标和是`1`, 所以`vector[1] += 12`.

然后最后处理一下进位, 把前导零去除即可.

## code

```cpp
// 第一种
class Solution {
    string reverse_add(string num1, string num2)
    {
        string result;
        int _add = 0, i = 0;
        int size1 = static_cast<int>(num1.size());
        int size2 = static_cast<int>(num2.size());
        while(i < size1 || i < size2 || _add != 0)
        {
            if(i < size1) _add += num1[i] - '0';
            if(i < size2) _add += num2[i] - '0';
            result += (_add % 10) + '0';
            _add /= 10;
            ++i;
        }
        return result;
    }

public:
    string multiply(string num1, string num2) {
        string result("0");
        string temp;
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int size1 = static_cast<int>(num1.size());
        int size2 = static_cast<int>(num2.size());
        for(int i = 0; i < size1; ++i)
        {
            int carry = 0, j = 0;
            
            // 低位补零
            while(j < i) temp += '0', ++j;
            // 字符相乘
            for(j = 0; j < size2 || carry != 0; ++j)
            {
                if(j < size2)
                    carry += (num1[i] - '0')*(num2[j] - '0');
                temp += (carry % 10) + '0';
                carry /= 10;
            }
            result = reverse_add(result, temp);
            temp.clear();
        }

        // 去除前导零
        int k = result.size() - 1;
        while(k > 0 && result[k] == '0') --k;
        result.erase(k+1);

        reverse(result.begin(), result.end());
        return result;
    }
};


// 第二种
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0"  ||  num2 == "0")
            return "0";

        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int size1 = static_cast<int>(num1.size());
        int size2 = static_cast<int>(num2.size());
        vector<int> v(size2 + size1 - 1, 0);
        for(int i = 0; i < size1; ++i)
        {
            for(int j = 0; j < size2; ++j)
            {
                v[i + j] += (num1[i]-'0')*(num2[j]-'0');
            }
        }

        int i = 0;
        int add = 0;
        string result;
        while(i < size2 + size1 - 1 || add != 0)
        {
            if(i < size2 + size1 - 1)
                add += v[i++];
            result += (add % 10) + '0';
            add /= 10;
        }
        int j = result.size() - 1;
        while(result[j] == '0' && j > 0) --j;
        result.erase(j + 1);

        reverse(result.begin(), result.end());
        return result;
    }
};
```

   # end

