/*
给你两个单词word1和word2，请返回将word1转换成word2所使用的最少操作数。
你可以对一个单词进行如下三种操作：
插入一个字符
删除一个字符
替换一个字符

示例1：
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将'h'替换为'r')
rorse -> rose (删除'r')
rose -> ros (删除'e')

示例2：
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除't')
inention -> enention (将'i'替换为'e')
enention -> exention (将'n'替换为'x')
exention -> exection (将'n'替换为'c')
exection -> execution (插入'u')

提示：
0 <= word1.length, word2.length <= 500
word1和word2由小写英文字母组成
*/

// 动态规划
int minDistance(char* word1, char* word2) {
  int m = strlen(word1);
  int n = strlen(word2);
  // if (m * n == 0) {  // 不检查也能返回正确结果
  //   return m + n;
  // }

  // dp[i][j]表示以下标i-1为结尾的字符串word1，和以下标j-1为结尾的字符串word2，最近编辑距离为dp[i][j]
  int dp[m + 1][n + 1];
  dp[0][0] = 0;
  for (int i = 1; i <= m; ++i) {
    // dp[i][0]：以下标i-1为结尾的字符串word1，和空字符串word2，最近编辑距离为dp[i][0]。
    // 那么dp[i][0]就应该是i，对word1⾥的元素全部做删除操作，即：dp[i][0]=i;
    dp[i][0] = i;
  }
  for (int j = 1; j <= n; ++j) {
    dp[0][j] = j;
  }

  // 可以看出dp[i][j]都是根据左上⽅、正上⽅、正左⽅推出来的。
  // 所以遍历的时候⼀定是从上到下，从左到右，这样保证dp[i][j]可以根据之前计算出来的数值进⾏计算。
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        // 当word1[i-1]与word2[j-1]相同的时候，不用任何编辑，即：
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        // 当word1[i-1]与word2[j-1]不相同的时候，此时需要编辑，增删换，有三种情况：
        // 1.word1增加⼀个元素，使其word1[i-1]与word2[j-1]相同，
        //   那么就是以下标i-2为结尾的word1与i-1为结尾的word2的最近编辑距离加上⼀个增加元素的操作。
        //   即dp[i][j] = dp[i-1][j] + 1;
        // 2.word2添加⼀个元素，使其word1[i-1]与word2[j-1]相同，
        //   那么就是以下标i-1为结尾的word1与j-2为结尾的word2的最近编辑距离加上⼀个增加元素的操作。
        //   即dp[i][j]=dp[i][j-1] + 1;
        //   只有添加元素，删除元素去哪了。word2添加⼀个元素，相当于word1删除⼀个元素。
        // 3.替换元素，word1替换word1[i-1]，使其与word2[j-1]相同，此时不⽤增加元素，
        //   那么以下标i-2为结尾的word1与j-2为结尾的word2的最近编辑距离加上⼀个替换元素的操作。
        //   即dp[i][j] = dp[i-1][j-1]+1;
        dp[i][j] = fmin(dp[i - 1][j - 1], fmin(dp[i - 1][j], dp[i][j - 1])) + 1;
      }
    }
  }

  return dp[m][n];
}
