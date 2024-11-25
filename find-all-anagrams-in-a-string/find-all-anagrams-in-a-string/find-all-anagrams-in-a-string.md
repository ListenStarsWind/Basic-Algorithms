# [find-all-anagrams-in-a-string](https://leetcode.cn/problems/find-all-anagrams-in-a-string)

## overview

![image-20241125195322162](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411251953203.png)

我们首先要理解“异位词”这个概念，先从示例一看起。`p`字符串`abc`的长度为三，这意味着它异位词的长度也是三，并且这个异位词是`abc`中元素的再组合，再组合的意思就是把`p`拆成一个一个字符，然后对这些字符以任意方式排序。比如`abc`可以分解成'a',  'b',  'c'这三个字符，那么它们就有六种组合顺序："abc",  "acd",  "bac", "bca",  "cab", "cba"，这六个字符串都是`abc`的异位词。

现在的需求是，从字符串`s`中找到一个子字符串，让其为`abc`的异位词，并返回子字符串中起始字符的索引下标。

## solution

让我们先解决一个小问题：如何判断一个字符串是否为另一个字符串的“异位词”。

很明显，应该用哈希表来解决。创建两个哈希表，一个给`p`用，就叫它`target_hash`吧，另一个给`s`用，叫做`current_hash`。先把`p`遍历一下，记录一下内部的字符信息，之后再在`s`中寻找子字符串，把这个子字符串的哈希表和`tar_hash`作比较即可。

怎么找子字符串呢？首先还是暴力解法，把`s`的各个字符为子字符串的起始字符，向后延伸`p`的长度即可。当然，不用想也知道会超时，接下来我们就在暴力破解的基础上作优化即可。

还是老样子，我们先建立两个指针用于维护子字符串，这两个指针最开始仍旧指向第一个元素，再每轮迭代中，`right`向后迭代一次，并更新哈希表，如果子字符串的长度超过要求，则需要进行修改，不过由于我们这里的要求依据的是长度，所以这次可以直接用`if`而不是`while`，因为不满足要求肯定是超过一个长度，那`left`再向后迭代，这长度就刚好符合要求了，如果长度符合要求，就需要比对两个哈希表，如果比对成功，那就把`left`扔到返回容器中即可。

## code

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int tar_hash[26] = {0};
        int cmp_hash[26] = {0};
        vector<int> ret;

        for(auto e : p)
            tar_hash[e - 'a']++;

        int left = 0, right = 0, len = p.size(), sz = s.size();
        while(right < sz)
        {
            cmp_hash[s[right++] - 'a']++;
            if(right - left  > len)
                cmp_hash[s[left++] - 'a']--;
            
            if(right - left  == len)
            {
                int cir = 0;
                while(cir < 26)
                {
                    if(tar_hash[cir] != cmp_hash[cir])
                    break;
                    cir++;
                }
                if(cir == 26)
                ret.push_back(left);
            }
        }
        return ret;  
    }
};
```

不过这份代码还需要优化优化，两个哈希表的比对看起来太浪费时间了，虽然这里哈希表的元素固定，是26个，但如果元素长度不固定，肯定是不能直接比较的，所以接下来我们就来优化两个哈希表的比对机制。

我们的优化机制是引入一个计数器变量，用它来统计子字符串中的有效字符个数。什么叫有效字符？直观的说就是那些可以在异位词中出现的字符，比如说`p`中根本没有`d`，那如果`right`向后迭代过程中遇到了`d`，那这`count`自然不会对这'd'计数，另一种场景是`p`中只出现两个`a`，那在`right`遇到第一个`a`时，它自然被视为有效，所以`count`会加一，然后`right`又迭代了几次，超出长度了，当`left`丢弃`a`时，由于子字符串只有一个`a`，所以它丢弃的就是有效字符，所以`count`要减一。又过了几轮之后，子字符串已经有两个`a`了，所以此时`count`为2，接着`right`又遇到一个`a`，这是第三个`a`了，而异位词中就两个`a`，所以本次`a`就被视为无效字符，`count`不需要在加一。

这样就可以大大化简两个哈希表的比对机制，因为肯定经过一定迭代之后，子字符串长度是先大于要求一个单位，接着又正好等于要求的，所以只要`count`与要求长度相等就意味着这个子字符串是异位词，至于前期子字符串的长度小于要求时，由于遍历过的子字符串个数小于长度，所以`count`一定不等于要求长度。用代码来说，在`right`扩大子字符串长度后，如果这个新加入的字符是有效字符，则`count`加一，而在`left`丢弃字符前，将要被丢弃的字符是有效字符，则`count`减一。如果子字符串中新加入/将丢弃字符的哈希表对应位值小于等于目标哈希表的对应位值，则可视为有效字符。

````cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int tar_hash[26] = {0};
        int cmp_hash[26] = {0};
        vector<int> ret;

        for (auto e : p)
            tar_hash[e - 'a']++;

        int left = 0, right = 0, count = 0, len = p.size(), sz = s.size();
        while (right < sz) {
            cmp_hash[s[right++] - 'a']++;
            if(cmp_hash[s[right - 1] - 'a'] <= tar_hash[s[right - 1] - 'a'])
            count++;

            if (right - left > len)
            {
                if(cmp_hash[s[left] - 'a'] <= tar_hash[s[left] - 'a'])
                count--;
                cmp_hash[s[left++] - 'a']--;
            }
            
            if(count == len)
                ret.push_back(left);
        }
        return ret;
    }
};
````


# end