/*
给一个整数数组nums和一个整数k。
每一步操作中，需要从数组中选出和为k的两个整数，并将它们移出数组。
返回可以对数组执行的最大操作数。

示例1：
输入：nums = [1,2,3,4], k = 5
输出：2
解释：开始时nums = [1,2,3,4]：
     移出1和4，之后nums = [2,3]
     移出2和3，之后nums = []
     不再有和为5的数对，因此最多执行2次操作。

示例2：
输入：nums = [3,1,3,4,3], k = 6
输出：1
解释：开始时 nums = [3,1,3,4,3]：
     移出前两个3，之后nums = [1,4,3]
     不再有和为6的数对，因此最多执行1次操作。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= 10^9
*/

class Solution {
 public:
  int maxOperations(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> cnt;
    int ans = 0;
    for (auto num : nums) {
      int t = k - num;
      if (cnt.find(t) != cnt.end()) {
        ++ans;
        if (--cnt[t] == 0) {
          cnt.erase(t);
        };
      } else {
        cnt[num]++;
      }
    }
    return ans;
  }
};

class Solution {
 public:
  int maxOperations(vector<int>& nums, int k) {
    int ans = 0;
    unordered_map<int, int> cnt;
    for (int x : nums) {
      auto it = cnt.find(k - x);
      if (it != cnt.end() && it->second) {
        it->second--;
        ans++;
      } else {
        cnt[x]++;
      }
    }
    return ans;
  }
};
