/*
几乎每一个人都用乘法表。但是你能在乘法表中快速找到第k小的数字吗？
乘法表是大小为mxn的一个整数矩阵，其中mat[i][j]==i*j（下标从1开始）。
给你三个整数m、n和k，请在大小为mxn的乘法表中，找出并返回第k小的数字。

示例1：
输入：m = 3, n = 3, k = 5
输出：3
解释：第5小的数字是3。

示例2：
输入：m = 2, n = 3, k = 6
输出：6
解释：第6小的数字是6。


提示：
1 <= m, n <= 3 * 10^4
1 <= k <= m * n
*/

// 暴力，内存超限
class Solution {
 public:
  int findKthNumber(int m, int n, int k) {
    vector<int> a(m * n);
    int index = 0;
    int i = 1;
    int j = 1;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        a[index++] = i * j;
      }
    }
    sort(a.begin(), a.end());

    return a[k - 1];
  }
};

/*
第K小/大问题
例如数组[1,1,1,2,2]，其中第1小、第2小和第3小的数都是1，第4小和第5小的数都是2。
第k小等价于：求最小的x，满足≤x的数至少有k个。
第k大等价于：求最大的x，满足≥x的数至少有k个。
*/
class Solution {
 public:
  int findKthNumber(int m, int n, int k) {
    auto check = [&](int num) {
      int cnt = 0;
      for (int i = 1; i <= m; ++i) {
        cnt += min(num / i, n);
      }
      return cnt >= k;
    };
    int left = 1;
    int right = m * n;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};