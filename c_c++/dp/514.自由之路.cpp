/*
电子游戏辐射4中，
任务通向自由要求玩家到达名为Freedom Trail Ring的金属表盘，
并使用表盘拼写特定关键词才能开门。
给定一个字符串ring，表示刻在外环上的编码；
给定另一个字符串key，表示需要拼写的关键词。
您需要算出能够拼写关键词中所有字符的最少步数。
最初，ring的第一个字符与12:00方向对齐。
您需要顺时针或逆时针旋转ring以使key的一个字符在12:00方向对齐，
然后按下中心按钮，以此逐个拼写完key中的所有字符。
旋转ring拼出key字符key[i]的阶段中：
您可以将ring顺时针或逆时针旋转一个位置，计为1步。
旋转的最终目的是将字符串ring的一个字符与12:00方向对齐，
并且这个字符必须等于字符key[i]。
如果字符key[i]已经对齐到12:00方向，
您需要按下中心按钮进行拼写，这也将算作1步。
按完之后，您可以开始拼写key的下一个字符（下一阶段）, 直至完成所有拼写。

示例1：
输入: ring = "godding", key = "gd"
输出: 4
解释:
对于key的第一个字符'g'，已经在正确的位置, 只需要1步来拼写这个字符。
对于key的第二个字符'd'，
需要逆时针旋转ring"godding"2步使它变成"ddinggo"。
当然, 还需要1步进行拼写，因此最终的输出是4。

示例2:
输入: ring = "godding", key = "godding"
输出: 13

提示：
1 <= ring.length, key.length <= 100
ring和key只包含小写英文字母
保证字符串key一定可以由字符串ring旋转拼出
*/

// 官方题解
// 时间复杂度：O(mn^2)
// 空间复杂度：O(mn)
int findRotateSteps(char* ring, char* key) {
  int n = strlen(ring), m = strlen(key);
  // pos保存ring中各个字母出现的位置，
  // posSize保存ring中各个字母出现的次数：
  int pos[26][n], posSize[26];
  memset(posSize, 0, sizeof(posSize));
  for (int i = 0; i < n; ++i) {
    int x = ring[i] - 'a';
    pos[x][posSize[x]++] = i;
  }
  int dp[m][n];
  memset(dp, 0x3f3f3f3f, sizeof(dp));
  // 设置key中第一个字母在ring中移动到12点需要的步数
  for (int i = 0; i < posSize[key[0] - 'a']; i++) {
    int x = pos[key[0] - 'a'][i];
    dp[0][x] = fmin(x, n - x) + 1;
  }
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j < posSize[key[i] - 'a']; ++j) {
      int x = pos[key[i] - 'a'][j];
      for (int k = 0; k < posSize[key[i - 1] - 'a']; ++k) {
        int y = pos[key[i - 1] - 'a'][k];
        dp[i][x] =
            fmin(dp[i][x], dp[i - 1][y] + fmin(abs(x - y), n - abs(x - y)) + 1);
      }
    }
  }
  int ret = dp[m - 1][0];
  for (int i = 1; i < n; ++i) {
    ret = fmin(ret, dp[m - 1][i]);
  }
  return ret;
}

class Solution {
 public:
  int findRotateSteps(string ring, string key) {
    int m = key.size();
    int n = ring.size();

    vector<vector<int>> pos(26);
    for (int i = 0; i < n; ++i) {
      pos[ring[i] - 'a'].emplace_back(i);
    }

    vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
    for (int i = 0, c = key[0] - 'a'; i < pos[c].size(); ++i) {
      int x = pos[c][i];
      dp[0][x] = min(x, n - x) + 1;
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < pos[key[i] - 'a'].size(); ++j) {
        int x = pos[key[i] - 'a'][j];
        for (int k = 0; k < pos[key[i - 1] - 'a'].size(); ++k) {
          int y = pos[key[i - 1] - 'a'][k];
          dp[i][x] =
              min(dp[i][x], dp[i - 1][y] + min(abs(x - y), n - abs(x - y)) + 1);
        }
      }
    }

    int ret = dp[m - 1][0];
    for (int i = 1; i < n; ++i) {
      ret = min(ret, dp[m - 1][i]);
    }
    return ret;
  }
};
