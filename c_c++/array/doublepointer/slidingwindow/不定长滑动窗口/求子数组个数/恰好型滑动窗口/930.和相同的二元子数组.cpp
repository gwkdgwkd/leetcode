/*
给一个二元数组nums，和一个整数goal，请统计并返回有多少个和为goal的非空子数组。
子数组是数组的一段连续部分。

示例 1：
输入：nums = [1,0,1,0,1], goal = 2
输出：4
解释：有4个满足题目要求的子数组：[1,0,1]、[1,0,1,0]、[0,1,0,1]、[1,0,1]

示例2：
输入：nums = [0,0,0,0,0], goal = 0
输出：15


提示：
1 <= nums.length <= 3 * 10^4
nums[i]不是0就是1
0 <= goal <= nums.length
*/

/*
恰好型滑动窗口

例如，要计算有多少个元素和恰好等于k的子数组，可以把问题变成：
计算有多少个元素和≥k的子数组。
计算有多少个元素和>k，也就是≥k+1的子数组。
答案就是元素和≥k的子数组个数，减去元素和≥k+1的子数组个数。
这里把>转换成≥，从而可以把滑窗逻辑封装成一个函数f，
然后用f(k)-f(k+1)计算，无需编写两份滑窗代码。

总结：恰好可以拆分成两个至少，也就是两个越长越合法的滑窗问题。
     也可以把问题变成≤k减去≤k−1（两个至多），可根据题目选择合适的变形方式。
     也可以把两个滑动窗口合并起来，维护同一个右端点right和两个左端点left1​和left2​，
     这种写法叫做三指针滑动窗口。
*/

// 越长越合法写法
class Solution {
 public:
  int numSubarraysWithSum(vector<int>& nums, int goal) {
    int n = nums.size();
    auto count = [&](int g) -> int {
      int left = 0;
      int right = 0;
      int sum = 0;
      int ans = 0;

      while (right < n) {
        sum += nums[right++];
        while (sum >= g && left < right) {
          sum -= nums[left++];
        }
        ans += left;
      }
      return ans;
    };

    // 和为goal的非空子数组 = 和大于等于goal - 和大于等于goal+1
    return count(goal) - count(goal + 1);
  }
};
// 越短越合法写法
class Solution {
 public:
  int numSubarraysWithSum(vector<int>& nums, int goal) {
    int n = nums.size();
    auto count = [&](int g) -> int {
      int left = 0;
      int right = 0;
      int sum = 0;
      int ans = 0;

      while (right < n) {
        sum += nums[right++];
        while (sum > g && left < right) {
          sum -= nums[left++];
        }
        ans += right - left;
      }
      return ans;
    };

    // 和为goal的非空子数组 = 和小于等于goal - 和大于等于goal-1
    return count(goal) - count(goal - 1);
  }
};

// 三指针滑动窗口
class Solution {
 public:
  int numSubarraysWithSum(vector<int>& nums, int goal) {
    int n = nums.size();

    int left1 = 0, left2 = 0;
    int right = 0;
    int sum1 = 0, sum2 = 0;
    int ans = 0;
    while (right < n) {
      sum1 += nums[right];
      while (left1 <= right && sum1 >= goal) {
        sum1 -= nums[left1++];
      }
      sum2 += nums[right];
      while (left2 <= right && sum2 >= goal + 1) {
        sum2 -= nums[left2++];
      }
      ans += left1 - left2;
      ++right;
    }

    return ans;
  }
};
