/*
编写一个高效的算法来搜索mxn矩阵matrix中的一个目标值target。
该矩阵具有以下特性：
每行的元素从左到右升序排列。
每列的元素从上到下升序排列。

示例1：
输入：matrix =
[[1,4,7,11,15],
[2,5,8,12,19],
[3,6,9,16,22],
[10,13,14,17,24],
[18,21,23,26,30]],
target = 5 输出：true

示例2：
输入：matrix =
[[1,4,7,11,15],
[2,5,8,12,19],
[3,6,9,16,22],
[10,13,14,17,24],
[18,21,23,26,30]],
target = 20 输出：false

提示：
m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-10^9 <= matrix[i][j] <= 10^9
每行的所有元素从左到右升序排列
每列的所有元素从上到下升序排列
-10^9 <= target <= 10^9
*/

// 剑指Offer04二维数组中的查找

// Z型查找
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize,
                  int target) {
  int m = matrixSize, n = matrixColSize[0];
  int x = 0, y = n - 1;
  while (x < m && y >= 0) {
    if (matrix[x][y] > target) {
      --y;
    } else if (matrix[x][y] < target) {
      ++x;
    } else {
      return true;
    }
  }
  return false;
}

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();

    int i = 0;
    int j = n - 1;
    while (i < m && j >= 0) {
      if (matrix[i][j] > target) {
        --j;
      } else if (matrix[i][j] < target) {
        ++i;
      } else {
        return true;
      }
    }

    return false;
  }
};

// 面试题1009排序矩阵查找
class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if (m == 0) {  // C的程序可以不用判断，C++要判断
      return false;
    }
    int n = matrix[0].size();

    int i = 0;
    int j = n - 1;
    while (i < m && j >= 0) {
      if (matrix[i][j] > target) {
        --j;
      } else if (matrix[i][j] < target) {
        ++i;
      } else {
        return true;
      }
    }

    return false;
  }
};