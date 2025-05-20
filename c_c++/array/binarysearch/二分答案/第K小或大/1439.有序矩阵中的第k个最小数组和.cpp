/*
给一个m*n的矩阵mat，以及一个整数k，矩阵中的每一行都以非递减的顺序排列。
可以从每一行中选出1个元素形成一个数组。返回所有可能数组中的第k个最小数组和。

示例1：

输入：mat = [[1,3,11],[2,4,6]], k = 5
输出：7
解释：从每一行中选出一个元素，前k个和最小的数组分别是：
     [1,2], [1,4], [3,2], [3,4], [1,6]。其中第5个的和是7。

示例2：
输入：mat = [[1,3,11],[2,4,6]], k = 9
输出：17

示例 3：
输入：mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
输出：9
解释：从每一行中选出一个元素，前k个和最小的数组分别是：
     [1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]。
     其中第7个的和是9。

示例4：
输入：mat = [[1,1,10],[2,2,9]], k = 7
输出：12


提示：
m == mat.length
n == mat.length[i]
1 <= m, n <= 40
1 <= k <= min(200, n ^ m)
1 <= mat[i][j] <= 5000
mat[i]是一个非递减数组
*/

class Solution {
 public:
  vector<vector<int>> temp;
  int m, n;
  int kthSmallest(vector<vector<int>>& mat, int k) {
    temp = mat;
    m = mat.size(), n = mat[0].size();
    int left = 0, right = 0;
    for (int i = 0; i < m; i++) left += mat[i][0], right += mat[i].back();
    int init = left;
    while (left < right) {
      int mid = (left + right) >> 1;
      int num = 1;
      dfs(mid, 0, init, num, k);
      if (num >= k)
        right = mid;
      else
        left = mid + 1;
    }

    return left;
  }

  void dfs(int mid, int index, int sum, int& num, int k) {
    if (sum > mid || index == m || num > k) return;
    dfs(mid, index + 1, sum, num, k);
    for (int i = 1; i < n; i++) {
      if (sum + temp[index][i] - temp[index][0] <= mid) {
        num++;
        dfs(mid, index + 1, sum + temp[index][i] - temp[index][0], num, k);
      } else {
        break;
      }
    }
  }
};