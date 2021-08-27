/*
 * @lc app=leetcode.cn id=72 lang=c
 *
 * [72] 编辑距离
 */

// @lc code=start

// 动态规划
int minDistance(char* word1, char* word2) {
  int len1 = strlen(word1);
  int len2 = strlen(word2);
  if (len1 * len2 == 0) {
    return len1 + len2;
  }

  // dp[i][j]表示以下标i-1为结尾的字符串word1，和以下标j-1为结尾的字符串word2，最近编辑距离为dp[i][j]。
  int dp[len1 + 1][len2 + 1];
  for (int i = 0; i <= len1; ++i) {
    // dp[i][0]：以下标i-1为结尾的字符串word1，和空字符串word2，最近编辑距离为dp[i][0]。
    // 那么dp[i][0]就应该是i，对word1⾥的元素全部做删除操作，即：dp[i][0]=i;
    dp[i][0] = i;
  }
  for (int i = 0; i <= len2; ++i) {
    dp[0][i] = i;
  }

  // 可以看出dp[i][j]都是根据左上⽅、正上⽅、正左⽅推出来的。
  // 所以遍历的时候⼀定是从上到下，从左到右，这样保证dp[i][j]可以根据之前计算出来的数值进⾏计算。
  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        // 当word1[i-1]与word2[j-1]相同的时候，不用任何编辑，即：
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        // 当word1[i-1]与word2[j-1]不相同的时候，此时需要编辑，增删换。有三种情况：
        // 操作⼀：word1增加⼀个元素，使其word1[i-1]与word2[j-1]相同，那么就是以下标i-2为结尾的word1与i-1为结尾的word2的最近编辑距离加上⼀个增加元素的操作。
        //        即dp[i][j] = dp[i - 1][j] + 1;
        // 操作⼆：word2添加⼀个元素，使其word1[i-1]与word2[j-1]相同，那么就是以下标i-1为结尾的word1与j-2为结尾的word2的最近编辑距离加上⼀个增加元素的操作。
        //        即dp[i][j]=dp[i][j-1] + 1;
        // 只有添加元素，删除元素去哪了。word2添加⼀个元素，相当于word1删除⼀个元素。
        // 操作三：替换元素，word1替换word1[i-1]，使其与word2[j-1]相同，此时不⽤增加元素，那么以下标i-2为结尾的word1与j-2为结尾的word2的最近编辑距离加上⼀个替换元素的操作。
        //        即dp[i][j] = dp[i-1][j-1]+1;
        dp[i][j] = fmin(dp[i - 1][j - 1], fmin(dp[i - 1][j], dp[i][j - 1])) + 1;
      }
    }
  }

  return dp[len1][len2];
}

// @lc code=end
