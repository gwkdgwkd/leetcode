/*
把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。
输入n，打印出s的所有可能的值出现的概率。
你需要用一个浮点数数组返回答案，
其中第i个元素代表这n个骰子所能掷出的点数集合中第i小的那个的概率。

示例1:
输入: 1
输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]

示例2:
输入: 2
输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,
      0.13889,0.11111,0.08333,0.05556,0.02778]

限制：1 <= n <= 11
*/

double* dicesProbability(int n, int* returnSize) {
  // 6 * 11 = 66
  int dp[12][67] = {0};

  for (int i = 1; i <= 6; i++) {
    dp[1][i] = 1;  // [i][j] i:骰子数目 点数个数
  }

  for (int i = 2; i <= n; i++) {
    for (int j = i; j <= i * 6; j++) {
      for (int add = 1; add <= 6; add++) {
        if (j - add <= 0) break;
        dp[i][j] += dp[i - 1][j - add];
      }
    }
  }

  float base = 1 / pow(6, n);

  *returnSize = 6 * n - n + 1;
  double* ret = (double*)calloc(*returnSize, sizeof(double));

  for (int i = 0; i < *returnSize; i++) {
    ret[i] = dp[n][i + n] * base;
  }

  return ret;
}

class Solution {
 public:
  vector<double> dicesProbability(int n) {
    // 首先用数组的第一维来表示阶段，也就是投掷完了几枚骰子。
    // 然后用第二维来表示投掷完这些骰子后，可能出现的点数。
    // 数组的值就表示，该阶段各个点数出现的次数。
    // 所以状态表示就是这样的：
    // dp[i][j]，表示投掷完i枚骰子后，点数j的出现次数。
    vector<vector<int>> dp(n + 1, vector<int>(n * 6 + 1, 0));
    for (int j = 1; j <= 6; ++j) {  // 只有一个骰子
      dp[1][j] = 1;
    }

    for (int i = 2; i <= n; ++i) {
      for (int j = i; j <= n * 6; ++j) {
        // 每个取值时，比如4这个取值，可能是上一次是1这次是3，
        // 也可能上次2这次2，也可能上次3这次1，所以要1-6都遍历一次
        for (int add = 1; add <= 6; ++add) {
          if (j - add <= 0) break;
          dp[i][j] += dp[i - 1][j - add];
        }
      }
    }

    float base = 1 / pow(6, n);  // 所有可能出现的次数：pow(6, n)

    vector<double> ans(6 * n - n + 1);
    for (int i = 0; i < ans.size(); ++i) {  // 每个数出现的次数除以总数
      ans[i] = dp[n][i + n] * base;
    }

    return ans;
  }
};