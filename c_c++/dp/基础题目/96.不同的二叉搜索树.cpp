/*
给你一个整数n，求恰由n个节点组成且节点值从1到n互不相同的二叉搜索树有多少种？
返回满足题意的二叉搜索树的种数。

示例1：
输入：n = 3
输出：5

示例2：
输入：n = 1
输出：1

提示：1 <= n <= 19
*/

int **memo;
int count(int lo, int hi) {
  if (lo > hi) return 1;
  // 查备忘录
  if (memo[lo][hi] != 0) {
    return memo[lo][hi];
  }

  int res = 0;
  for (int mid = lo; mid <= hi; mid++) {
    int left = count(lo, mid - 1);
    int right = count(mid + 1, hi);
    res += left * right;
  }
  // 将结果存入备忘录
  memo[lo][hi] = res;
  return res;
}
int numTrees(int n) {
  // 备忘录的值初始化为0
  memo = (int **)malloc(sizeof(int *) * (n + 1));
  for (int i = 0; i < n + 1; ++i) {
    memo[i] = (int *)malloc(sizeof(int) * (n + 1));
    memset(memo[i], 0, sizeof(int) * (n + 1));
  }

  return count(1, n);
}

// 动态规划
int numTrees(int n) {
  // dp[i]：1到i为节点组成的⼆叉搜索树的个数为dp[i]。
  // dp[3]=元素1为根结点搜索树的数量+元素2为根结点搜索树的数量+元素3为根结点搜索树的数量
  // 元素1为根结点搜索树的数量=右⼦树有2个元素的搜索树数量*左⼦树有0个元素的搜索树数量
  // 元素2为根结点搜索树的数量=右⼦树有1个元素的搜索树数量*左⼦树有1个元素的搜索树数量
  // 元素3为根结点搜索树的数量=右⼦树有0个元素的搜索树数量*左⼦树有2个元素的搜索树数量
  // 有2个元素的搜索树数量就是dp[2]；
  // 有1个元素的搜索树数量就是dp[1]；
  // 有0个元素的搜索树数量就是dp[0]。
  // 所以dp[3]=dp[2]*dp[0]+dp[1]*dp[1]+dp[0]*dp[2]
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;  // 空节点也是⼀颗⼆叉树，也是⼀颗⼆叉搜索树，这是可以说得通的
  for (int i = 1; i <= n; i++) {
    // j相当于是头结点的元素，从1遍历到i为⽌：
    for (int j = 1; j <= i; j++) {
      // dp[i] += dp[以j为根结点左⼦树节点数量] * dp[以j为根结点右⼦树节点数量]
      dp[i] += dp[j - 1] * dp[i - j];
    }
  }
  return dp[n];
}

class Solution {
 public:
  int numTrees(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= i; ++j) {
        dp[i] += dp[j - 1] * dp[i - j];
      }
    }

    return dp[n];
  }
};