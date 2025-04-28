/*
有k个非递减排列的整数列表。
找到一个最小区间，使得k个列表中的每个列表至少有一个数包含在其中。
定义如果b-a < d-c或者在b-a == d-c时a < c，则区间[a,b]比[c,d]小。

示例1：
输入：nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
输出：[20,24]
解释：列表1：[4, 10, 15, 24, 26]，24在区间 [20,24]中。
     列表2：[0, 9, 12, 20]，20在区间[20,24]中。
     列表3：[5, 18, 22, 30]，22在区间[20,24]中。

示例2：
输入：nums = [[1,2,3],[1,2,3],[1,2,3]]
输出：[1,1]


提示：
nums.length == k
1 <= k <= 3500
1 <= nums[i].length <= 50
-10^5 <= nums[i][j] <= 10^5
nums[i]按非递减顺序排列
*/

class Solution {
 public:
  vector<int> smallestRange(vector<vector<int>>& nums) {
    vector<pair<int, int>> pairs;
    for (int i = 0; i < nums.size(); i++) {
      for (int x : nums[i]) {
        pairs.emplace_back(x, i);
      }
    }
    // 看上去std::sort比ranges::sort更快
    sort(pairs.begin(), pairs.end());

    int ans_l = pairs[0].first;
    int ans_r = pairs.back().first;
    int empty = nums.size();
    vector<int> cnt(empty);
    int left = 0;
    for (auto [r, i] : pairs) {
      if (cnt[i] == 0) {  // 包含nums[i]的数字
        empty--;
      }
      cnt[i]++;
      while (empty == 0) {  // 每个列表都至少包含一个数
        auto [l, i] = pairs[left];
        if (r - l < ans_r - ans_l) {
          ans_l = l;
          ans_r = r;
        }
        cnt[i]--;
        if (cnt[i] == 0) {  // 不包含nums[i]的数字
          empty++;
        }
        left++;
      }
    }
    return {ans_l, ans_r};
  }
};