#include<vector>

using namespace std;


class Solution {
public:
	void duplicateZeros(vector<int>& arr) {
		
	}
};

int main()
{
	int arr[] = {1,0,2,3,0,4,5,0};
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	vector<int> v;
	size_t i = 0;
	for (i = 0; i < sz; i++)
	{
		v.push_back(arr[i]);
	}



	return 0;
}