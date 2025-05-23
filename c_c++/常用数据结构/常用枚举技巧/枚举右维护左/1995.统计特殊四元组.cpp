/*
给一个下标从0开始的整数数组nums，返回满足下述条件的不同四元组(a, b, c,
d)的数目： nums[a] + nums[b] + nums[c] == nums[d]，且a < b < c < d

示例1：
输入：nums = [1,2,3,6]
输出：1
解释：满足要求的唯一一个四元组是(0, 1, 2, 3)因为1 + 2 + 3 == 6。

示例2：
输入：nums = [3,3,6,4,5]
输出：0
解释：[3,3,6,4,5]中不存在满足要求的四元组。

示例3：
输入：nums = [1,1,1,3,5]
输出：4
解释：满足要求的4个四元组如下：
     (0, 1, 2, 3): 1 + 1 + 1 == 3
     (0, 1, 3, 4): 1 + 1 + 3 == 5
     (0, 2, 3, 4): 1 + 1 + 3 == 5
     (1, 2, 3, 4): 1 + 1 + 3 == 5


提示：
4 <= nums.length <= 50
1 <= nums[i] <= 100
*/

// 暴力
class Solution {
 public:
  int countQuadruplets(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    for (int a = 0; a < n; ++a) {
      for (int b = a + 1; b < n; ++b) {
        for (int c = b + 1; c < n; ++c) {
          for (int d = c + 1; d < n; ++d) {
            if (nums[a] + nums[b] + nums[c] == nums[d]) {
              ++ans;
            }
          }
        }
      }
    }
    return ans;
  }
};

// 使用哈希表存储nums[d]
class Solution {
 public:
  int countQuadruplets(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    unordered_map<int, int> cnt;
    for (int c = n - 2; c >= 2; --c) {
      ++cnt[nums[c + 1]];
      for (int a = 0; a < c; ++a) {
        for (int b = a + 1; b < c; ++b) {
          if (int sum = nums[a] + nums[b] + nums[c]; cnt.count(sum)) {
            ans += cnt[sum];
          }
        }
      }
    }
    return ans;
  }
};

// 使用哈希表存储nums[d]−nums[c]
class Solution {
 public:
  int countQuadruplets(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    unordered_map<int, int> cnt;
    for (int b = n - 3; b >= 1; --b) {
      for (int d = b + 2; d < n; ++d) {
        ++cnt[nums[d] - nums[b + 1]];
      }
      for (int a = 0; a < b; ++a) {
        if (int sum = nums[a] + nums[b]; cnt.count(sum)) {
          ans += cnt[sum];
        }
      }
    }
    return ans;
  }
};