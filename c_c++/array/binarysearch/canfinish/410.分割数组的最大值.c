/*
给定一个非负整数数组nums和一个整数m，你需要将这个数组分成m个非空的连续子数组。
设计一个算法使得这m个子数组各自和的最大值最小。

示例1：
输入：nums = [7,2,5,10,8], m = 2
输出：18
解释：
一共有四种方法将nums分割为2个子数组。
其中最好的方式是将其分为[7,2,5]和[10,8] 。
因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。

示例2：
输入：nums = [1,2,3,4,5], m = 2
输出：9

示例3：
输入：nums = [1,4,4], m = 3
输出：4

提示：
1 <= nums.length <= 1000
0 <= nums[i] <= 10^6
1 <= m <= min(50, nums.length)
*/

// 动态规划，将数组分割为m段，求……是动态规划题目常见的问法。
// 时间复杂度：O(n^2×m)，n是数组的长度，m子数组的个数。
//           总状态数为O(n×m)，状态转移时间复杂度O(n)，所以总时间复杂度为O(n^2×m)。
// 空间复杂度：O(n×m)，为动态规划数组的开销。
int splitArray(int* nums, int numsSize, int m) {
  // dp[i][j]表示将数组的前i个数分割为j段所能得到的最大连续子数组和的最小值
  int dp[numsSize + 1][m + 1];
  memset(dp, 0x3f, sizeof(dp));
  int pre[numsSize + 1];  // 前缀和
  memset(pre, 0, sizeof(pre));
  for (int i = 0; i < numsSize; ++i) {
    pre[i + 1] = pre[i] + nums[i];
  }

  dp[0][0] = 0;
  for (int i = 1; i <= numsSize; ++i) {
    for (int j = 1; j <= fmin(i, m); ++j) {
      for (int k = 0; k < i; ++k) {
        // dp[k][j-1]：i中前k个元素分j-1组
        // pre[i]-pre[k]：k+1到i的元素当作1组的和
        dp[i][j] = fmin(dp[i][j], fmax(dp[k][j - 1], pre[i] - pre[k]));
      }
    }
  }

  return dp[numsSize][m];
}

// 二分查找+贪心，使……最大值尽可能小是二分搜索题目常见的问法
bool check(int* nums, int numsSize, int m, int minsum) {
  int cnt = 1;
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    if (sum + nums[i] > minsum) {
      cnt++;
      sum = nums[i];
    } else {
      sum += nums[i];
    }
  }

  return cnt <= m;
}
int splitArray(int* nums, int numsSize, int m) {
  int left = nums[0];
  int right = 0;
  for (int i = 0; i < numsSize; ++i) {
    right += nums[i];
    left = fmax(left, nums[i]);
  }

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (check(nums, numsSize, m, mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
}