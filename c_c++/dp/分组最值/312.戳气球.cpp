/*
有n个气球，编号为0到n - 1，每个气球上都标有一个数字，这些数字存在数组nums中。
现在要求你戳破所有的气球。
戳破第i个气球，你可以获得nums[i - 1] * nums[i] * nums[i + 1]枚硬币。
这里的i - 1和i + 1代表和i相邻的两个气球的序号。
如果i - 1或i + 1超出了数组的边界，那么就当它是一个数字为1的气球。
求所能获得硬币的最大数量。

示例1：
输入：nums = [3,1,5,8]
输出：167
解释：
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

示例2：
输入：nums = [1,5]
输出：10

提示：
n == nums.length
1 <= n <= 300
0 <= nums[i] <= 100
*/

// 动态规划
int maxCoins(int* nums, int numsSize) {
  // dp[i][j]表示填满开区间(i,j)能得到的最多硬币数，不包括i和j
  int dp[numsSize + 2][numsSize + 2];
  memset(dp, 0, sizeof(dp));
  int value[numsSize + 2];
  value[0] = value[numsSize + 1] = 1;
  for (int i = 1; i <= numsSize; ++i) {
    value[i] = nums[i - 1];
  }

  // 区间：(i...k...j)，k是最后被戳破的气球
  for (int i = numsSize - 1; i >= 0; i--) {
    for (int j = i + 2; j <= numsSize + 1; j++) {
      for (int k = i + 1; k < j; k++) {
        int sum = value[i] * value[k] * value[j];  // 戳k时，获取的硬币
        sum += dp[i][k] + dp[k][j];  // 区间(i,k)和区间(k,j)总共的硬币和
        dp[i][j] = fmax(dp[i][j], sum);
      }
    }
  }
  return dp[0][numsSize + 1];
}

class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    int n = nums.size();
    vector<int> value(n + 2);
    value[0] = value[n + 1] = 1;
    for (int i = 1; i <= n; ++i) {
      value[i] = nums[i - 1];
    }

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int i = n - 1; i >= 0; --i) {
      for (int j = i + 2; j <= n + 1; ++j) {
        for (int k = i + 1; k < j; ++k) {
          int sum = dp[i][k] + value[i] * value[k] * value[j] + dp[k][j];
          dp[i][j] = max(dp[i][j], sum);
        }
      }
    }

    return dp[0][n + 1];
  }
};