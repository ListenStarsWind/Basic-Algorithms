#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

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

int main()
{
    string s = "barfoothefoobarman";
    vector<string> words = { "foo","bar" };
    Solution().findSubstring(s, words);
    return 0;
}