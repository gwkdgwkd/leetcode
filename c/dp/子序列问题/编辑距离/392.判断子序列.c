/*
 * @lc app=leetcode.cn id=392 lang=c
 *
 * [392] 判断子序列
 */

// @lc code=start

// 编辑距离的⼊⻔题⽬，因为从题意中我们也可以发现，只需要计算删除的情况，不⽤考虑增加和替换的情况。

// 动态规划
bool isSubsequence(char* s, char* t) {
  int l1 = strlen(s);
  int l2 = strlen(t);
  // dp[i][j]表示以下标i-1为结尾的字符串s，和以下标j-1为结尾的字符串t，相同⼦序列的⻓度为dp[i][j]。
  int dp[l1 + 1][l2 + 1];
  // dp[i][j]都是依赖于dp[i-1][j-1] 和 dp[i][j-1]，所以dp[0][0]和dp[i][0]是⼀定要初始化的。
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= l1; ++i) {
    for (int j = 1; j <= l2; ++j) {
      if (s[i - 1] == t[j - 1]) {
        // 找到了⼀个相同的字符，相同⼦序列⻓度⾃然要在dp[i-1][j-1]的基础上加1
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        // 此时相当于t要删除元素，t如果把当前元素t[j-1]删除，那么dp[i][j] 的数值就是看s[i-1]与t[j-2]的⽐较结果了，即：
        dp[i][j] = dp[i][j - 1];
      }
    }
  }

  // for (int i = 0; i <= l1; ++i) {
  //   for (int j = 0; j <= l2; ++j) {
  //     printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // "abc" "ahbgdc"
  // 0 0 0 0 0 0 0
  // 0 1 1 1 1 1 1
  // 0 0 0 2 2 2 2
  // 0 0 0 0 0 0 3

  return dp[l1][l2] == l1;
}

// 时间复杂度：O(n*m)
// 空间复杂度：O(n*m)

// 双指针
bool isSubsequence(char* s, char* t) {
  int m = strlen(s);
  int n = strlen(t);

  int i = 0, j = 0;
  while (i < m && j < n) {
    if (s[i] == t[j]) {
      ++i;
    }
    ++j;
  }

  return i == m;
}

// 时间复杂度：O(m+n)
// 空间复杂度：O(1)

// @lc code=end
