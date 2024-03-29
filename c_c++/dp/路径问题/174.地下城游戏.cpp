/*
一些恶魔抓住了公主（P）并将她关在了地下城的右下角，地下城是由MxN个房间组成的二维网格。
我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。
骑士的初始健康点数为一个正整数，如果他的健康点数在某一时刻降至0或以下，他会立即死亡。
有些房间由恶魔守卫，因此骑士在进入时会失去健康点数，若值为负整数，则表示骑士将损失健康点数；
其他房间要么是空的（房间里的值为0），要么包含增加骑士健康点数的魔法球，若房间里的值为正整数，
则表示骑士将增加健康点数，为了尽快到达公主，骑士决定每次只向右或向下移动一步。

编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。
例如，考虑到如下布局的地下城，如果骑士遵循最佳路径右->右->下->下，
则骑士的初始健康点数至少为7。
-2(K) -3 	  3
-5 	  -10 	1
10 	  30 	  -5(P)

说明：
骑士的健康点数没有上限。
任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，
包括骑士进入的左上角房间以及公主被监禁的右下角房间。
*/

// 动态规划
int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize) {
  int n = dungeonSize, m = dungeonColSize[0];
  // p[i][j]表示从坐标(i,j)到终点所需的最小初始值：
  int dp[n + 1][m + 1];
  memset(dp, 0x3f, sizeof(dp));
  dp[n][m - 1] = dp[n - 1][m] = 1;
  // 从下到上，从右到左遍历
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      int minn = fmin(dp[i + 1][j], dp[i][j + 1]);
      // 初始值还必须大于等于1：
      dp[i][j] = fmax(minn - dungeon[i][j], 1);
    }
  }

  // -2, -3,  3
  // -5, -10, 1
  // 10, 30,  -5
  // for (int i = 0; i < m; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // 7  5  2
  // 6  11 5
  // 1  1  6

  return dp[0][0];
}

class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = dungeon.size();
    int n = dungeon[0].size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
    dp[m][n - 1] = dp[m - 1][n] = 1;

    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        dp[i][j] = max(min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j], 1);
      }
    }

    return dp[0][0];
  }
};