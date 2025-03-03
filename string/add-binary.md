# [add-binary](https://leetcode.cn/problems/add-binary)

![image-20250303215007650](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303215007752.png)

## overview

本题其实是高精度算法的模拟题.   所谓高精度就是非常大的数,   因为数太大了, 所以无法对其进行存储, 其实就需要把数字转变为字符串, 以字符串的形式参与加减乘除, 只要照着小学列竖式模拟就行了.

## solution

对于加法来说, 我们从两个字符串的最低位开始, 一个一个加, 因为这里是二进制, 所以最后要把和模二的结果输出到结果字符中, 就像之前我们写的那道链表字符相加一样, 循环条件有三个, 它们以逻辑或的形式组合在一起, 分别是两个字符串下标没有越位, 进位器不等于0, 当下标越位时, 我们就将其当做`0`处理, 也就是不加.  最后别忘了把结果字符串正序回来.

## code

```cpp
class Solution {
public:
    string addBinary(string a, string b) {
        string result;
        int _a = a.size() - 1;
        int _b = b.size() - 1;
        int add = 0;
        while(_a >= 0 || _b >=0 || add != 0)
        {
            if(_a >= 0) add += a[_a--] - '0';
            if(_b >= 0) add += b[_b--] - '0';
            result += (add % 2) + '0';
            add /= 2;
        }

        reverse(result.begin(), result.end());
        return result;
    }
};
```

# end