#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int keys_hash[128] = { 0 };
        int kinds_size = 0;
        for (const auto& e : t) {
            if (keys_hash[e] == 0)
                kinds_size++;

            keys_hash[e]++;
        }

        int left = 0, right = 0, count = 0, target_size = s.size();
        vector<int> pre_storage;
        pre_storage.resize(2, INT_MAX);
        int target_hash[128] = { 0 };
        while (right < target_size) {
            const char& in = s[right++];
            target_hash[in]++;

            if (keys_hash[in] != 0 && target_hash[in] == keys_hash[in])
                count++;

            while (count == kinds_size) {
                if (pre_storage[1] > right - left) {
                    pre_storage[0] = left;
                    pre_storage[1] = right - left;
                }

                const char& out = s[left++];
                if (keys_hash[out] != 0 && target_hash[out] == keys_hash[out])
                    count--;
                target_hash[out]--;
            }
        }

        if (pre_storage[1] == INT_MAX)
            return string();
        else
            return s.substr(pre_storage[0], pre_storage[1]);
    }
};

int main()
{
    string s = "aa";
    string t = "aa";
    Solution().minWindow(s, t);
    return 0;
}