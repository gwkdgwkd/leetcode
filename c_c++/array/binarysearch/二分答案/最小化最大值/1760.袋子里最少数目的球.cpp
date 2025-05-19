/*
给一个整数数组nums，其中nums[i]表示第i个袋子里球的数目。
同时给你一个整数maxOperations。
可以进行如下操作至多maxOperations次：
选择任意一个袋子，并将袋子里的球分到2个新的袋子中，每个袋子里都有正整数个球。
比方说，一个袋子里有5个球，可以把它们分到两个新袋子里，分别有1个和4个球，或者分别有2个和3个球。
开销是单个袋子里球数目的最大值，想要最小化开销。
请返回进行上述操作后的最小开销。

示例1：
输入：nums = [9], maxOperations = 2
输出：3
解释：将装有9个球的袋子分成装有6个和3个球的袋子。[9] -> [6,3]。
     将装有6个球的袋子分成装有3个和3个球的袋子。[6,3] -> [3,3,3]。
     装有最多球的袋子里装有3个球，所以开销为3并返回3。

示例2：
输入：nums = [2,4,8,2], maxOperations = 4
输出：2
解释：将装有8个球的袋子分成装有4个和4个球的袋子。[2,4,8,2]->[2,4,4,4,2]。
     将装有4个球的袋子分成装有2个和2个球的袋子。[2,4,4,4,2]->[2,2,2,4,4,2]。
     将装有4个球的袋子分成装有2个和2个球的袋子。[2,2,2,4,4,2]->[2,2,2,2,2,4,2]。
     将装有4个球的袋子分成装有2个和2个球的袋子。[2,2,2,2,2,4,2]->[3,2,2,2,2,2,2,2]。
     装有最多球的袋子里装有2个球，所以开销为2并返回2。

示例3：
输入：nums = [7,17], maxOperations = 2
输出：7


提示：
1 <= nums.length <= 10^5
1 <= maxOperations, nums[i] <= 10^9
*/

class Solution {
 public:
  int minimumSize(vector<int>& nums, int maxOperations) {
    auto check = [&](int m) {
      int cnt = 0;
      for (int i = 0; i < nums.size(); ++i) {
        // 当nums[i]≤m时，无需进行操作；
        // 当m<nums[i]≤2m时，需要进行1次操作；
        // 当my<nums[i]≤3m时，需要进行2次操作；
        // ...
        cnt += (nums[i] - 1) / m;  // 向下取整
        if (cnt > maxOperations) {
          return false;
        }
      }

      return true;
    };

    int left = 1;
    int right = *max_element(nums.begin(), nums.end());
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

class Solution {
 public:
  int minimumSize(vector<int>& nums, int maxOperations) {
    auto check = [&](int m) -> bool {
      long long cnt = 0;
      for (int x : nums) {
        cnt += (x - 1) / m;
      }
      return cnt <= maxOperations;
    };

    int left = 0;                   // 循环不变量check(left) == false
    int right = ranges::max(nums);  // 循环不变量check(right) == true
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      (check(mid) ? right : left) = mid;
    }
    return right;
  }
};
