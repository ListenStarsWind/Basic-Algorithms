#include<string>

using namespace std;

class Solution {
public:
    string modifyString(string s) {
        size_t len = s.size();
        for (size_t i = 0; i < len; i++) 
        {
            if (s[i] == '?') 
            {
                for (char ch = 'a'; ch <= 'z'; ch++) 
                {
                    if ((i == 0 || ch != s[i - 1]) &&
                        (i == len - 1 || ch != s[i + 1])) {
                        s[i] = ch;
                        break;
                    }
                }
            }
        }
        return s;
    }
};

int main()
{
	Solution().modifyString("j?qg??b");
	return 0;
}