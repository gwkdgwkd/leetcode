/*
给定一个非负整数numRows，生成「杨辉三角」的前numRows行。
在杨辉三角中，每个数是它左上方和右上方的数的和。

示例1:
输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

示例2:
输入: numRows = 1
输出: [[1]]

提示: 1 <= numRows <= 30
*/

int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
  int** ret = (int**)malloc(numRows * sizeof(int*));
  *returnSize = numRows;
  *returnColumnSizes = malloc(sizeof(int) * numRows);
  for (int i = 0; i < numRows; ++i) {
    ret[i] = (int*)malloc(sizeof(int) * (i + 1));
    (*returnColumnSizes)[i] = i + 1;
    ret[i][0] = ret[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
    }
  }

  return ret;
}

class Solution {
 public:
  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res;
    for (int i = 0; i < numRows; ++i) {
      vector<int> rows(i + 1);
      for (int j = 0; j <= i; ++j) {
        if (j == 0 || j == i) {
          rows[j] = 1;
          continue;
        }
        if (j > 0) {
          rows[j] = res[i - 1][j - 1] + res[i - 1][j];
        }
      }
      res.emplace_back(rows);
    }

    return res;
  }
};
