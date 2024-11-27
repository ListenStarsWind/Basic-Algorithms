# [substring-with-concatenation-of-all-words](https://leetcode.cn/problems/substring-with-concatenation-of-all-words)

## overview

![image-20241127085203412](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411270852597.png)

题目中其实只有两个重点：一是`words`中所有字符串的长度相等，这很关键，因为我们思路其中之一的核心思路就是这个；二是要理解串联子串的含义，`words`是包含一系列关键字符串的集合，而串联子串就是`words`中所有关键字符串以不同方式排列组合而形成的字符串。例如，如果`words = ["ab", "cd", "ef"]`，那么`"abcdef"`， `"abefcd"`，`"cdabef"`， `"cdefab"`，`"efabcd"`， 和 `"efcdab"` 都是串联子串，而`acdbef`就不是串联子串，因为其中存在`words`中不存在的关键字符串：`ac`，`db`。

对于示例一来说，从`s`下标0开始的`barfoo`就是一个串联子串，所以0是我们要返回的值之一，另一方面，从下标9开始的`foobar`也是一个串联子串，所以9也是我们要返回的值之一。

对于示例二来说，我们一个串联子串都找不到，所以就返回一个空容器。

## solution

这道题像是上一道题的加强版

![image-20241127091929685](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411270919049.png)

在上一题中，关键字集合`p`是由一个个关键字符所组成的，从逻辑上来说，单个字符可以理解成长度为一的字符串。所以在上一道题中，我们的`left`和`right`都是指向包含其自身的单个字符，而在本题中，`words`中的关键字符串可能不为一，但好在它们的长度都是一样的，假设`words`中的单个关键字符串的长度是`len`，则本题中`left`和`right`所指向的是包含自身及其向后`len`个长度的字符串，这会引发`left`和`right`迭代机制和边界条件的变化。

由于关键字符串的长度不为一，所以我们的哈希表也需要进行改变，所以这次我们不是直接用数组表示哈希表，而是用`unordered_map<string, int>`，逻辑上都是一样的，不需要太过担心。

另外还要考虑对齐问题，在上一题中，由于关键字符串的长度为一，所以其在处理对象中天然就是对齐的，不会说半个字符在这里，另外半个字符在那里的情况。在本题中，就需要考虑了，所以题目所给的三个示例似乎都没有强调这一点，比如现在有`s = "zabrffgc"`，而`words = ["ab", "rf"]`，那么`abrf`就是一个串联子串，所以1是我们要返回的值之一。该怎么解决呢？我粗略描述一下过程：最开始`left`和`right`都指向0，然后将`right`指向的子字符串`za`记录在检查对象哈希表中，然后`right += len`，就变成了2，`right`和`left`所维护的子字符串是否超过`words`中的关键子字符串个数？在这个例子中，`words`中的关键字个数是2，而`right`和`left`维护的子字符串是`za`，只有一个子字符串，所以`left`向后迭代舍弃子字符串；`right`和`left`维护的子字符合是串联子串吗？不是，那就进行下一轮循环；于是就将`right`指向的子字符串`br`记录在哈希表中，然后`right`向后迭代，变成4，`right`和`left`维护的子字符串`["za", "br"]`超过关键个数吗？没有；它们的合字符串`zabr`是串联子串吗？不是，于是进行下一轮循环；`right`指向的是`ff`，更新哈希并迭代变为6，`right`和`left`维护的子字符串`["za", "br", "ff"]`超过了关键个数，所以就要扔掉`left`指向的子字符串`za`，`left += len`，使之向后迭代，并更新哈希表，合字符串`brff`依旧不是合字符串，所以，进行下一轮循环，······当在某次循环中发现`right`大于或等于检查对象的长度了，或者说越界了，那就停止本次内层循环，然后进行下一轮外层循环，在第二次外层循环中，`right`和`left`都从1开始，······，当外层循环已经经过`len`长度的循环轮次时，外层循环也停止了，所以就能`return`了。

## code

```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        unordered_map<string, int> keys_hash;
        for (const auto& e : words)
            keys_hash[e]++;

        const int key_len = words[0].size(), keys_size = words.size(),
                  obj_len = s.size();
        int i = 0;
        for (; i < key_len; i++) {
            int left = i, right = left, count = 0;
            unordered_map<string, int> obj_hash;
            while (right < obj_len) {
                const string& in = s.substr(right, key_len);
                obj_hash[in]++;

                if (keys_hash.count(in) && obj_hash[in] <= keys_hash[in])
                    count++;

                right += key_len;

                if (right - left >= key_len * (keys_size + 1)) {
                    const string& out = s.substr(left, key_len);

                    if (keys_hash.count(out) && obj_hash[out] <= keys_hash[out])
                        count--;

                    obj_hash[out]--;

                    left += key_len;
                }

                if (count == keys_size)
                    ret.push_back(left);
            }
        }
        return ret;
    }
};
```

代码中有些细节可以注意一下，一是要注意计数器更新的位置，要在入子字符串后，丢子字符串前，另外还可以看到检查是否更新计数器的两个`if`条件中前面都有一个`keys_hash.count(str)`，这是为了稍微提高一些效率而考虑的，因为如果`keys_hash`中有不存在的`str`，它就会把`str`添加进来，前面的条件就是为了避免这个，如果`str`根本不在`keys_hasn`中，那就不要往后比了。


# end