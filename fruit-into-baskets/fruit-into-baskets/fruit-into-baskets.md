# [fruit-into-baskets](https://leetcode.cn/problems/fruit-into-baskets)

![image-20241124170117981](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411241701185.png)

## overview

这是一道阅读理解题。你来到一个农场里，这个农场里种有若干果树，这些树可以抽象成一个整数数组，数组里元素的值可以表示为水果的种类。现要求你采摘水果，给你两个篮子，不考虑篮子的容量，每个篮子只能放一种水果，也就是说，你只能采摘两种水果；另外需要注意的是，你只能在一棵果树上采摘一个水果，采摘完这一个水果后就必须来到下一个临近的果树，题目的要求就是尽可能多采摘水果，并返回最后两个篮子里的水果树。

以示例二为例：如果从第零棵果树摘起，也就是种类为0的果树开始，摘过一个，就要来到第一课果树，再摘一个，来到第二课果树，但第二课果树摘不了了，因为这是第三种水果，所以这次模拟就结束了。我也可以从第一课果树开始摘起，就可以采摘 [1,2,2] 这三棵树，返回最多的，所以返回三。

## solution

我们把这个问题抽象化：尝试从数组中找到一个子数组，这个子数组中只有两个不同值，返回最长的子数组长度。

首先仍然是暴力破解。找到所有满足要求的子数组，返回最长的子数组长度。

现在我们在暴力破解的基础上进行优化，最开始`left and right`都指向0，每次`right`向后迭代一次，两指针维护的子数组就可能会多一个种类，可能种类数没变，也可能种类数加一，总之，肯定不会出现种类数减少的可能。这意味这`right`可以进行单向迭代，在`left`更新之后不用回到起始位置，契合滑动窗口的要求。

在每轮迭代中，`right`都试探性地往后迭代，尝试接近题目两种水果的要求，若子数组中元素种类超过2，则就需要`left`向后迭代，直到子数组元素种类满足要求为止，在每轮迭代的末尾，更新`len`的值，由于可能出现水果种类少于二的可能，所以只要子数组元素种类数弱满足要求（小于等于2）即可进行更新，而不需要强满足（种类必须为2）。

## code

```cpp
struct node {
    typedef node self;

    int _kinds;
    int _count;

    node(int kid) : _kinds(kid), _count(0) {}

    self operator++() {
        ++_count;
        return *this;
    }

    self operator--() {
        --_count;
        return *this;
    }
};

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        vector<node> v;
        for (int i = 0; i < fruits.size(); i++)
            v.push_back(node(i));

        int left = 0, right = 0, len = 0, flag = 0, sz = fruits.size();
        while (right < sz) {
            if (v[fruits[right]]._count == 0)
                flag++;
            ++v[fruits[right++]];
            while (flag > 2) {
                --v[fruits[left++]];
                if (v[fruits[left - 1]]._count == 0)
                    flag--;
            }
            len = max(len, right - left);
        }

        return len;
    }
};
```

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        vector<int> hash;
        hash.resize(fruits.size(), 0);

        int left = 0, right = 0, len = 0, kinds = 0, sz = fruits.size();
        while (right < sz) {
            if (hash[fruits[right]] == 0)
                kinds++;

            ++hash[fruits[right++]];

            while (kinds > 2) {
                --hash[fruits[left++]];

                if (hash[fruits[left - 1]] == 0)
                    kinds--;
            }
            len = max(len, right - left);
        }
        return len;
    }
};
```


# end