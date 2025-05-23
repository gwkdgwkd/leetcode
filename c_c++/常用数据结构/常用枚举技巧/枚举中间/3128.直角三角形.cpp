/*
给一个二维boolean矩阵grid。
如果grid的3个元素的集合中，一个元素与另一个元素在同一行，
并且与第三个元素在同一列，则该集合是一个直角三角形。
3个元素不必彼此相邻。
请返回使用grid中的3个元素可以构建的直角三角形数目，且满足3个元素值都为1。

示例 1：
输入：grid = [[0,1,0],[0,1,1],[0,1,0]]
输出：2
解释：有2个值为1的直角三角形。

示例2：
输入：grid = [[1,0,0,0],[0,1,0,1],[1,0,0,0]]
输出：0
解释：没有值为1的直角三角形。

示例3：
输入：grid = [[1,0,1],[1,0,0],[1,0,0]]
输出：2
解释：有两个值为1的直角三角形。


提示：
1 <= grid.length <= 1000
1 <= grid[i].length <= 1000
0 <= grid[i][j] <= 1
*/

class Solution {
 public:
  long long numberOfRightTriangles(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<int> row_sum(n, -1);
    vector<int> col_sum(m, -1);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        col_sum[j] += grid[i][j];
        row_sum[i] += grid[i][j];
      }
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == 1) {
          ans += row_sum[i] * col_sum[j];
        }
      }
    }
    return ans;
  }
};

class Solution {
 public:
  long long numberOfRightTriangles(vector<vector<int>>& grid) {
    int n = grid[0].size();
    vector<int> col_sum(n, -1);  // 提前减一
    for (auto& row : grid) {
      for (int j = 0; j < n; j++) {
        col_sum[j] += row[j];
      }
    }

    long long ans = 0;
    for (auto& row : grid) {
      int row_sum = reduce(row.begin(), row.end()) - 1;  // 提前减一
      for (int j = 0; j < row.size(); j++) {
        if (row[j] == 1) {
          ans += row_sum * col_sum[j];
        }
      }
    }
    return ans;
  }
};
