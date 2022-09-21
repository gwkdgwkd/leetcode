/*
给定一个正整数n，将其拆分为k个正整数的和（k>=2），
并使这些整数的乘积最大化，返回你可以获得的最大乘积。

示例1:
输入: n = 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。

示例2:
输入: n = 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。

提示:2 <= n <= 58
*/

// 动态规划
int integerBreak(int n) {
  if (n < 2) {
    return 0;
  }

  // dp[i]表示将正整数i拆分成至少两个正整数的和之后，
  // 这些正整数的最大乘积。
  // 0不是正整数，1是最小的正整数，
  // 0和1都不能拆分，因此dp[0]=dp[1]=0：
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      // 有两种渠道得到dp[i]，把i分成j和i-j：
      //  dp[i - j] * j : i - j继续拆分
      //  (i - j) * j : i - j不继续拆分
      dp[i] = fmax(dp[i], fmax(dp[i - j] * j, (i - j) * j));
    }
  }

  return dp[n];
}

class Solution {
 public:
  int integerBreak(int n) {
    vector<int> dp(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
      for (int j = 1; j < i; ++j) {
        dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
      }
    }

    return dp[n];
  }
};

// 贪心
int integerBreak(int n) {
  if (n == 2) return 1;
  if (n == 3) return 2;
  if (n == 4) return 4;
  int result = 1;
  while (n > 4) {
    result *= 3;
    n -= 3;
  }
  result *= n;
  return result;
}

// 剑指Offer14-I剪绳子
// 给你一根长度为n的绳子，请把绳子剪成整数长度的m段，
// m、n都是整数，n>1并且m>1，每段绳子的长度记为k[0],k[1]...k[m-1]。
// 请问k[0]*k[1]*...*k[m-1]可能的最大乘积是多少？
// 例如，当绳子的长度是8时，把它剪成长度分别为2、3、3的三段，
// 此时得到的最大乘积是18。

// 剑指Offer14-II剪绳子II
// 给你一根长度为n的绳子，请把绳子剪成整数长度的m段，
// m、n都是整数，n>1并且m>1，每段绳子的长度记为k[0],k[1]...k[m - 1]。
// 请问k[0]*k[1]*...*k[m - 1]可能的最大乘积是多少？
// 例如，当绳子的长度是8时，把它剪成长度分别为2、3、3的三段，
// 此时得到的最大乘积是18。
// 答案需要取模1e9+7（1000000007），
// 如计算初始结果为：1000000008，请返回1

// 贪心
// 本题的特点是将绳子全部按照长度为3进行切割乘积结果是最大的
// 不过有几种情况需要注意：
// 1.在剩余长度等于4的时候，要取2 * 2，而不是3
// 2.在至少分出1段3的情况下，
//   剩余n = 2的时候要取2；
//   剩余n = 1的时候要取1
int cuttingRope(int n) {
  // 处理特殊情况
  if (n == 2) return 1;
  if (n == 3) return 2;
  if (n == 4) return 4;
  long ans = 1;
  int mod = 1000000007;
  // 当大于4的时候，先分出一段长度为3的，直到长度小于等于4，则不再分
  while (n > 4) {
    ans = ans * 3 % mod;
    n -= 3;
  }
  return (int)(ans * n % mod);
}
