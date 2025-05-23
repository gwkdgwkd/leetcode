/*
给一个整数数组nums和一个整数k，判断数组中是否存在两个不同的索引i和j，
满足nums[i]==nums[j]且abs(i - j)<=k。
如果存在，返回true；否则，返回false。

示例1：
输入：nums = [1,2,3,1], k = 3
输出：true

示例2：
输入：nums = [1,0,1,1], k = 1
输出：true

示例3：
输入：nums = [1,2,3,1,2,3], k = 2
输出：false


提示：
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
0 <= k <= 10^5
*/

// 枚举右，维护左
class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++i) {
      int x = nums[i];
      // if (last.contains(x) && i - m[x] <= k) {
      if (m.find(x) != m.end() && i - m[x] <= k) {
        return true;
      }
      m[x] = i;
    }
    return false;
  }
};

// 定长滑动窗口
class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_set<int> st;
    for (int i = 0; i < nums.size(); i++) {
      if (!st.insert(nums[i]).second) {  // st中有nums[i]
        return true;
      }
      if (i >= k) {
        st.erase(nums[i - k]);
      }
    }
    return false;
  }
};
