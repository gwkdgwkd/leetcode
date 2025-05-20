/*
给一个满足下述两条属性的m x n整数矩阵：
每行中的整数从左到右按非严格递增顺序排列。
每行的第一个整数大于前一行的最后一个整数。
给你一个整数target，如果target在矩阵中，返回true；否则，返回false。

示例1：
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true

示例2：
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false


提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-10^4 <= matrix[i][j], target <= 10^4
*/

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int left = 0;
    int right = n * m - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      int i = mid / m;
      int j = mid % m;
      if (matrix[i][j] < target) {
        left = mid + 1;
      } else if (matrix[i][j] > target) {
        right = mid - 1;
      } else {
        return true;
      }
    }

    return false;
  }
};
