# [teemo-attacking](https://leetcode.cn/problems/teemo-attacking)

![image-20250103212551630](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103212551819.png)

## overview

直接来看示例.

示例一, 当艾希在第一秒受到攻击之后, 在第一秒和第二秒这两秒里都会处于中毒状态,且在这两秒里没有受到新的攻击,所以中毒时间不会重置,第四秒又收到攻击,所以总的中毒时长就是四秒.

示例二,当艾希在第一秒受到攻击之后,在第一秒和第二秒这两秒内都处于中毒状态, 在第二秒,艾希再次受到了攻击,所以中毒时间重置,在第二秒和第三秒这两秒里将会继续中毒, 所以总的中毒时间就是三秒.

## solution

直接找个例子模拟一下过程即可.  比如 现在有数组`[1, 4, 5, 6, 12, 19]`,`duration = 3`,  我们看相邻元素的时间间隔, 比如 `1  4`相隔3,  大于等于`duration`,所以计时器加`duration`, 而对于`4   5`来说, 间隔时间小于`duration`, 所以计时器就加上`5 - 4`, 之后再加上`6 - 5`, 再加上`duration`,`19`后面没有元素,但还是要计时的, 所以要再加上`duration`.

这就是思路, 代码直接模拟即可.

## code

```cpp
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        size_t size = timeSeries.size();
        int time = duration;
        for(size_t i = 0; i < size-1; i++)
        {
            int len = timeSeries[i+1] - timeSeries[i];
            if(len >= duration)
                time += duration;
            else
                time += len;
        }
        return time;
    }
}; 
```

# end