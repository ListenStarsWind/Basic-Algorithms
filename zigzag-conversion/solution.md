# [zigzag-conversion](https://leetcode.cn/problems/zigzag-conversion)

![image-20250104204241187](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250104204241398.png)

## overview

给你一个字符串, 请把该字符串排列在指定行数`n`的矩阵之中, 使得矩阵中的字符形状为"N".

例如`"abcdefghijklmnopq"`, 行数为四, 所排成的矩阵就是这样的

![f7b916c1884f01c2c6a4aae388c98f3f](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250104205914772.png)

字符旁边的数字表示其在原字符串中的下标, 

不过我们不是返回这个矩阵, 而是把矩阵一行一行的读一下,形成一个新的字符串`"agmbfhlnceikoqdjp"`, 返回这个字符串

## solution

第一种方法, 就是按照上图那样真的模拟一遍, 定义一个二维数组, 这个二维数组的行数是确定的, 就是指定的行数, 列数可以研究一下周期性, 但也可以直接设为字符串的长度, 然后从矩阵的`[0 , 0]`位置开始, 一个一个地去填.  

把`s[0]`取出来, 放在`[0, 0]`位置,  把`s[1]`放到`[0, 1]`, 把`s[2]`放在`[0, 2]`, 把`s[3]`放在`[0, 3]`, 然后发现不能往下了, 就斜着向上走, 把`s[4]`放在`[1, 2]`, 把`s[5]`放在`[2, 1]`, 把`s[6]`放在`[3, 0]`, 不能往上了, 所以再重复之前的逻辑, 知道整个字符串都被遍历一遍. 

但如果这样写的话, 可以预料到, 一方面是代码不太好写, 有两种位置移动方式,还要来回切换, 少不了一堆条件语句, 另一方面, 将字符串读出的操作要遍历整个矩阵, 会耗费很多时间,  空间复杂度因为有矩阵的存在, 也必然不会很理想, 所以接下来我们就要使用第二种方法了.

当模拟算法直接模拟效果不好时, 就要尝试从模拟过程中寻找规律.

在读取矩阵时, 我们是从左往右, 从上往下, 一行一行进行读取的, 比如拿上面的图来说,

首先是第一行,  第一个被读到的是下标为`0`的字符, 第二个被读到的是下标为`6`的字符, 第三个被读到的是下标为`12`的字符, 我们发现, `0, 6, 12`之间的间隔是固定的, 这是不是特例呢? 很显然, 不是, 这里的间隔其实就是它们之间相差的字符, 由于形状的是固定的, 所以间隔也是固定的.

![image-20250104214121250](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250104214121316.png)

那这间隔怎么算呢? 其实很简单,  分为垂直和倾斜两部分, 垂直部分的个数就是`4`, 而倾斜部分就是`4 - 2`, 倾斜部分除了第一行和最后一行之外, 其它行都有一个字符, 这样我们就得到了读取时,相邻字符下标的间隔, 或者说, 步长, 步长的计算公式就是  行数 * 2 - 2;  同样的规律对于最后一行也适用.

对于中间行来说,  可以分为两个部分,  第一个部分是 垂直部分, 比如`b  h`之间的步长和第一行字符的步长是一致的,  倾斜部分, 比如`f l`之间的步长也是之前的步长. 在实际代码中, 可以把单个垂直部分和倾斜部分当做一个整体, 先把垂直部分的字符加到返回字符串中,  再把倾斜部分的字符加到返回字符串中,然后它们都向后迭代即可,  

最后需要注意的是, 可能存在行数为一的可能, 当行数为一时, 步长为0, 会导致程序陷入死循环, 所以需要特别处理, 之间返回原字符串.

## code

```cpp
class Solution {
    public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;

        string result;
        size_t len = s.size();
        size_t step = 2 * numRows - 2;

        // 第一行
        for (size_t pos = 0; pos < len; pos += step) 
            result += s[pos];

        // 中间行
        for (size_t row = 1; row < numRows - 1; ++row) 
        {
            for(size_t mainPos = row, diagPos = step - row; mainPos < len || diagPos < len; mainPos += step, diagPos += step)
            {
                if(mainPos < len) result += s[mainPos];
                if(diagPos < len) result += s[diagPos];
            }
        }

        // 最后一行
        for (size_t pos = numRows - 1; pos < len; pos += step) 
            result += s[pos];

        return result;
    }
};

```

# end

