/*
给你一个整数数组nums，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组是数组中的一个连续部分。

示例1：
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为6。

示例2：
输入：nums = [1]
输出：1

示例3：
输入：nums = [5,4,-1,7,8]
输出：23

提示：
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

进阶：如果你已经实现复杂度为O(n)的解法，尝试使用更为精妙的分治法求解。
*/

// 剑指Offer42连续子数组的最大和
// 面试题1617连续数列

// 时间复杂度：O(N)
// 空间复杂度：O(N)
int maxSubArray(int* nums, int numsSize) {
  // dp[i]：包括下标i之前的最⼤连续⼦序列和为dp[i]
  int dp[numsSize];
  memset(dp, 0, sizeof(dp));
  int max = dp[0] = nums[0];

  for (int i = 1; i < numsSize; ++i) {
    // dp[i]只有两个⽅向可以推出来：
    //  dp[i-1]+nums[i]，即：nums[i]加⼊当前连续⼦序列和
    //  nums[i]，即：从头开始计算当前连续⼦序列和
    dp[i] = fmax(dp[i - 1] + nums[i], nums[i]);
    max = fmax(max, dp[i]);
  }

  return max;
}

// 官方题解
// 时间复杂度：O(N)
// 空间复杂度：O(1)
int maxSubArray(int* nums, int numsSize) {
  int pre = 0, maxAns = nums[0];
  for (int i = 0; i < numsSize; i++) {
    pre = fmax(pre + nums[i], nums[i]);
    maxAns = fmax(maxAns, pre);
  }
  return maxAns;
}

// 贪心算法
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int maxSubArray(int* nums, int numsSize) {
  int max = INT_MIN;
  int count = 0;

  for (int i = 0; i < numsSize; ++i) {
    count += nums[i];
    if (count > max) {
      max = count;
    }
    if (count < 0) {
      count = 0;
    }
  }
  return max;
}

// 暴力解法，超时
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
int maxSubArray(int* nums, int numsSize) {
  int max = INT_MIN;
  int count = 0;

  for (int i = 0; i < numsSize; ++i) {
    count = 0;
    for (int j = i; j < numsSize; ++j) {
      count += nums[j];
      if (count > max) {
        max = count;
      }
    }
  }
  return max;
}

// 分治
struct Status {
  int lSum, rSum, mSum, iSum;
};
struct Status pushUp(struct Status l, struct Status r) {
  int iSum = l.iSum + r.iSum;
  int lSum = fmax(l.lSum, l.iSum + r.lSum);
  int rSum = fmax(r.rSum, r.iSum + l.rSum);
  int mSum = fmax(fmax(l.mSum, r.mSum), l.rSum + r.lSum);
  return (struct Status){lSum, rSum, mSum, iSum};
};
struct Status get(int* a, int l, int r) {
  if (l == r) {
    return (struct Status){a[l], a[l], a[l], a[l]};
  }
  int m = (l + r) >> 1;
  struct Status lSub = get(a, l, m);
  struct Status rSub = get(a, m + 1, r);
  return pushUp(lSub, rSub);
}
int maxSubArray(int* nums, int numsSize) {
  return get(nums, 0, numsSize - 1).mSum;
}

class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];

    int max = nums[0];
    for (int i = 1; i < n; ++i) {
      dp[i] = std::max(nums[i], dp[i - 1] + nums[i]);
      max = std::max(max, dp[i]);
    }

    return max;
  }
};