# [minimum-window-substring](https://leetcode.cn/problems/minimum-window-substring)

## overview

![image-20241128082604715](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411280826954.png)

题目将会给我们两个字符串`s`和`t`，`s`是待处理的目标字符串，`t`是存储关键字的字符串，现在的要求是从`s`中找到一个子字符串，该子字符串必须涵盖`t`中的所有元素，子字符串中可以有其它字符串，即，可以多，但不能少。最后返回长度最小的那个。

比如，以示例一为例。`s = "ADOBECODEBANC"`， `t = "ABC"`，我们可以以`s`的下标0开始，找出`ADDBEC`，这就是一个满足要求的子字符串，也可以从下标3开始，找出`BECODEBA`，这也是一个满足要求的子字符串，也就是说子字符串中的同种关键字个数大于`t`中对应字符的个数是没关系的，这就是第一项注意想强调的内容。但这个子字符串还是太长了，所以可以再从5开始，找出`CODEBA`，或者从下标9开始找起，`BANC`，对比一下，`BANC`最短，所以就返回它。注意第二项的意思是最短子字符串是唯一的，那示例一的`t`来说，是不可能出现类似`BANC`和`BAZC`这种令人困惑，不知道该返回谁的情况。

## solution

第一种仍旧是暴力解法，其实就是上面题目概述过程中的穷举。还是先定义两个指针`left`和`right`，按照某种顺序，比如从左往右，逐个确定子字符串的起始位置，然后从该起始位置开始，`right`向后迭代，扩大子字符串的长度，直到找到一个符合要求的子字符串，由于题目要求的是最短子字符串，所以只要找到符合要求的子字符串，就可以换起始位置了。

如何确定当前`left`和`right`维护的子字符串是满足要求的呢？同样是使用哈希表进行比对，先把`t`遍历一遍，用关键哈希表记录它的关键信息。然后在扩大子字符串的时候看看新进来的字符是否是关键字，如果是。那就更新目标哈希表，最后两个哈希表比较一下，如果目标的对应位大于等于关键，即意味着子字符串是符合要求的。

现在我们优化一下暴力解法。现在假设`left`已经锁定了某个关键字，之后`right`向后迭代，迭代几次之后找到了一个符合要求的子字符串，然后`left`迭代，更新起始位置，现在假设`left`已经找到了一个符合要求的起始位置了，按照之前的思路，就是要把`right`移回`left`了，此时就可以进行优化了，在`left`向后迭代之后，两指针所维护的子字符串无非两种可能，一是还是满足要求（可能`left`把多余的关键字给丢弃了），此时需不需要把`right`重新移回`left`？不需要，因为现在的子字符串就是满足要求的，而且由于当前子字符串是`left`向后迭代才得到的，现在的子字符串比原先的满足要求的子字符串更短；二是不满足要求，此时`right`需要重新回来吗？还是不用，`right`回去走到这里得到的子字符串还是不满足要求的，所以为什么要回来呢？对于第一种情况来说，既然现在子字符串还是满足要求的，那就再更新一下起始位置，对于第二种情况，既然现在的子字符串是不满足要求的，那自然需要`right`继续向后迭代。

也就是说，我们的优化方法是滑动窗口。

首先，两指针仍旧指向下标0，接着`right`向后迭代，扩大子字符串长度，当子字符串满足要求时，先尝试记录一下当前子字符串的起始位置和长度，方便我们返回的时候重新拼接出子字符串，然后`left`向后迭代，缩短子字符串长度，如果缩短之后，子字符串仍旧满足要求，那就继续缩短。

上面的思路已经可以解题了，但我们还可以优化一下。在之前，为了降低哈希表比对过程中的花销，我们定义了一个计数器去统计窗口中的有效元素个数，典型的，就是上一题。

![image-20241128093420206](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411280934522.png)

但这里不能这样做，此时计数器统计的个数不是有效元素的个数，而是有效元素的种类数，为什么不能这样做呢？

比如现在关键哈希表的内容是`[A:1, B:1, C:1]`，现在我们两指针维护的子字符串已经是满足要求的了，其目标哈希内容为`[A:1, B:2, C:1]`，如果计数器统计的是有效元素个数，此时`count == 4`，假设现在`left`丢弃了`A`，则现在`count == 3`，但关系哈希的`count`也是三，所以就误判了。

如果换成有效元素的种类，就不会出现这种情况了，还是上面的例子，此时关键哈希的计数器是3，表示有三种关键字，它们分别是`A, B, C`，而目标哈希的内容仍旧是`[A:1, B:2, C:1]`，此时`left`若是丢弃`A`，有效种类个数就变成了2，所以就不会误判了。

具体的实现方式是，当子字符串新进入字符后，在目标哈希中看看这个新字符映射的值，如果它等于关键哈希的对应值，则种类计数器加一，这里的关键是必须严格等于，如果是大于等于的话，也会多统计，同样在丢字符前，计数器的减一条件仍旧是严格等于。

## code

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int keys_hash[128] = {0};
        int kinds_size = 0;
        for (const auto& e : t) {
            if (keys_hash[e]++ == 0)
                kinds_size++;
        }

        int left = 0, right = 0, count = 0, target_size = s.size(), pos = INT_MAX, len = INT_MAX;
        int target_hash[128] = {0};
        while (right < target_size) {
            const char& in = s[right++];
            target_hash[in]++;
            if (keys_hash[in] != 0 && target_hash[in] == keys_hash[in])
                count++;

            while (count == kinds_size) {
                if (len > right - left) {
                    pos = left;
                    len = right - left;
                }

                const char& out = s[left++];
                if (keys_hash[out] != 0 && target_hash[out] == keys_hash[out])
                    count--;
                target_hash[out]--;
            }
        }

        if (len == INT_MAX)
            return string();
        else
            return s.substr(pos, len);
    }
};
```

最后要注意一些细节，比如找不到要返回空字符串。计数器更新的两个`if`中，前面的条件可加可不加，我这里加上是为了让逻辑更加清晰，哈希表里没这个关键字就不要比了。

## 后记

后来我又重新做了这道题, 我认为, 使用字符个数进行控制是完全可行的, 而不是像之前我说的那样, 统计次数的时候会引发`count`错误更新, 引发误判, 只不过, 字符个数的控制对代码的顺序有很高的要求, 另外吐槽一点, 以前写的代码说实话不太好, 怎么单个字符都要用引用, 有一种想学好却弄巧成拙的感觉.

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int hash1[128] = {0};
        int hash2[128] = {0};

        for(auto c : t) ++hash1[c];

        int left = 0, right = 0, count = 0;
        int ans_begin = -1, ans_len = INT_MAX; 
        int end = s.size(), len = t.size();
        while(right < end)
        {
            char c = s[right++];

            ++hash2[c];
		   
            // 如果hash1[c] == 0, 则在之前的加加中
            // hash2[c] > 0, 所以不会触发0 == 0
            // count不会被更新
            if(hash2[c] <= hash1[c])
                ++count;

            while(count == len)
            {
                // 尽管会明显进行冗余判断, 但对性能几乎没有影响
                if(right - left < ans_len)
                {
                    ans_begin = left;
                    ans_len = right - left;
                }


                char temp = s[left++];
				
                // 如果hash1[temp] == 0
                // 出窗口, temp本来就在窗口中
                // hash2[temp]>0(现在还没减)
                // 不会触发count--;
                if(hash2[temp] <= hash1[temp])
                    --count;
                
                --hash2[temp];
                
                // count仍然精确地被确保是有效字符的个数
                // 不会重复或缺少
            }
        }

        if(ans_begin != -1)
            return s.substr(ans_begin, ans_len);
        else
            return string();
    }
};
```

# end