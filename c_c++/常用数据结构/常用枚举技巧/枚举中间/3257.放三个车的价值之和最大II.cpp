/*
给一个mxn的二维整数数组board，它表示一个国际象棋棋盘，
其中board[i][j]表示格子(i,j)的价值。
处于同一行或者同一列车会互相攻击。
需要在棋盘上放三个车，确保它们两两之间都无法互相攻击。
请返回满足上述条件下，三个车所在格子值之和最大为多少。

示例1：
输入：board = [[-3,1,1,1],[-3,1,-3,1],[-3,2,1,1]]
输出：4
解释：我们可以将车分别放在格子(0,2)，(1,3)和(2,1)处，价值之和为1+1+2=4。

示例2：
输入：board = [[1,2,3],[4,5,6],[7,8,9]]
输出：15
解释：我们可以将车分别放在格子(0,0)，(1,1)和(2,2)处，价值之和为1+5+9=15。

示例3：
输入：board = [[1,1,1],[1,1,1],[1,1,1]]
输出：3
解释：我们可以将车分别放在格子(0,2)，(1,1)和(2 0)处，价值之和为1+1+1=3。


提示：
3 <= m == board.length <= 500
3 <= n == board[i].length <= 500
-10^9 <= board[i][j] <= 10^9
*/

class Solution {
 public:
  long long maximumValueSum(vector<vector<int>>& board) {
    array<pair<int, int>, 3> p;  // 最大、次大、第三大
    ranges::fill(p, pair(INT_MIN, -1));

    auto update = [&](vector<int>& row) {
      for (int j = 0; j < row.size(); j++) {
        int x = row[j];
        if (x > p[0].first) {
          if (p[0].second != j) {    // 如果相等，仅更新最大
            if (p[1].second != j) {  // 如果相等，仅更新最大和次大
              p[2] = p[1];
            }
            p[1] = p[0];
          }
          p[0] = {x, j};
        } else if (x > p[1].first && j != p[0].second) {
          if (p[1].second != j) {  // 如果相等，仅更新次大
            p[2] = p[1];
          }
          p[1] = {x, j};
        } else if (x > p[2].first && j != p[0].second && j != p[1].second) {
          p[2] = {x, j};
        }
      }
    };

    int m = board.size(), n = board[0].size();
    vector<array<pair<int, int>, 3>> suf(m);
    for (int i = m - 1; i > 1; i--) {
      update(board[i]);
      suf[i] = p;
    }

    long long ans = LLONG_MIN;
    ranges::fill(p, pair(INT_MIN, -1));  // 重置，计算pre
    for (int i = 1; i < m - 1; i++) {
      update(board[i - 1]);
      for (int j2 = 0; j2 < n; j2++) {               // 第二个车
        for (auto& [x, j1] : p) {                    // 第一个车
          for (auto& [z, j3] : suf[i + 1]) {         // 第三个车
            if (j1 != j2 && j1 != j3 && j2 != j3) {  // 没有同列的车
              ans = max(ans, (long long)x + board[i][j2] + z);
              break;
            }
          }
        }
      }
    }
    return ans;
  }
};

// 费用流做法
