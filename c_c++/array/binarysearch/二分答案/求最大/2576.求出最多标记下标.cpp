/*
给一个下标从0开始的整数数组nums。
一开始，所有下标都没有被标记。可以执行以下操作任意次：
选择两个互不相同且未标记的下标i和j，满足2*nums[i]<=nums[j]，标记下标i和j。
请执行上述操作任意次，返回nums中最多可以标记的下标数目。

示例1：
输入：nums = [3,5,2,4]
输出：2
解释：第一次操作中，选择i=2和j=1，操作可以执行的原因是2*nums[2]<=nums[1]，
     标记下标2和1。
     没有其他更多可执行的操作，所以答案为2。

示例2：
输入：nums = [9,2,5,4]
输出：4
解释：第一次操作中，选择i=3和j=0，2*nums[3]<=nums[0]，标记下标3和0。
     第二次操作中，选择i=1和j=2，2*nums[1]<=nums[2]，标记下标1和2。
     没有其他更多可执行的操作，所以答案为4。

示例3：
输入：nums = [7,6,8]
输出：0
解释：没有任何可以执行的操作，所以答案为0。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
*/

class Solution {
 public:
  int maxNumOfMarkedIndices(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    auto check = [&nums](int cnt) {
      int n = nums.size();
      int sum = 0;
      int i = 0;
      int j = 1;
      while (i < n - 1 && j < n) {
        if (2 * nums[i] <= nums[j]) {
          sum += 2;
          ++i;
          ++j;
        } else {
          ++j;
        }
      }
      return sum >= cnt;
    };

    int left = 1;
    int right = nums.size();
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right % 2 ? right - 1 : right;
  }
};

class Solution {
 public:
  int maxNumOfMarkedIndices(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int l = 0, r = n / 2;
    auto check = [&](int m) {
      for (int i = 0; i < m; i++) {
        if (nums[i] * 2 > nums[n - m + i]) {
          return false;
        }
      }
      return true;
    };
    while (l < r) {
      int m = l + r + 1 >> 1;
      if (check(m)) {
        l = m;
      } else {
        r = m - 1;
      }
    }
    return l * 2;
  }
};

// 二分答案
class Solution {
 public:
  int maxNumOfMarkedIndices(vector<int>& nums) {
    ranges::sort(nums);
    auto check = [&](int k) -> bool {
      for (int i = 0; i < k; i++) {
        if (nums[i] * 2 > nums[nums.size() - k + i]) {
          return false;
        }
      }
      return true;
    };

    int left = 0, right = nums.size() / 2 + 1;  // 开区间
    while (left + 1 < right) {
      int mid = (left + right) / 2;
      (check(mid) ? left : right) = mid;
    }

    return left * 2;  // 最多匹配left对，有left*2个数
  }
};

// 同向双指针
class Solution {
 public:
  int maxNumOfMarkedIndices(vector<int>& nums) {
    ranges::sort(nums);
    int i = 0, n = nums.size();
    for (int j = (n + 1) / 2; j < n; j++) {
      if (nums[i] * 2 <= nums[j]) {  // 找到一个匹配
        i++;
      }
    }
    return i * 2;
  }
};
