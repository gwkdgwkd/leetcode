/*
一个2D网格中的峰值是指那些严格大于其相邻格子(上、下、左、右)的元素。
给一个从0开始编号的mxn矩阵mat，其中任意两个相邻格子的值都不相同。
找出任意一个峰值mat[i][j]并返回其位置[i,j]。
可以假设整个矩阵周边环绕着一圈值为-1的格子。
要求必须写出时间复杂度为O(mlog(n))或O(nlog(m))的算法

示例1：
输入：mat = [[1,4],[3,2]]
输出：[0,1]
解释：3和4都是峰值，所以[1,0]和[0,1]都是可接受的答案。

示例2：
输入：mat = [[10,20,15],[21,30,14],[7,16,32]]
输出：[1,1]
解释：30和32都是峰值，所以[1,1]和[2,2]都是可接受的答案。


提示：
m == mat.length
n == mat[i].length
1 <= m, n <= 500
1 <= mat[i][j] <= 10^5
任意两个相邻元素均不相等。
*/

class Solution {
  int indexOfMax(vector<int>& a) { return ranges::max_element(a) - a.begin(); }

 public:
  vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int left = 0, right = mat.size() - 2;
    while (left <= right) {
      int i = left + (right - left) / 2;
      // 可以二分包含峰顶的行号i：
      // 1.如果mat[i]的最大值比它下面的相邻数字小，则存在一个峰顶，其行号大于i。
      //   缩小二分范围，更新二分区间左端点left。
      // 2.如果mat[i]的最大值比它下面的相邻数字大，则存在一个峰顶，其行号小于或等于i。
      //   缩小二分范围，更新二分区间右端点right。
      int j = indexOfMax(mat[i]);
      if (mat[i][j] > mat[i + 1][j]) {
        right = i - 1;  // 峰顶行号<=i
      } else {
        left = i + 1;  // 峰顶行号>i
      }
    }
    return {left, indexOfMax(mat[left])};
  }
};

class Solution {
  int indexOfMax(vector<int>& a) { return ranges::max_element(a) - a.begin(); }

 public:
  vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int left = 0, right = mat.size() - 1;
    while (left < right) {
      int i = left + (right - left) / 2;
      int j = indexOfMax(mat[i]);
      if (mat[i][j] > mat[i + 1][j]) {
        right = i;  // 峰顶行号<=i
      } else {
        left = i + 1;  // 峰顶行号>i
      }
    }
    return {left, indexOfMax(mat[left])};
  }
};

class Solution {
  int indexOfMax(vector<int>& a) { return ranges::max_element(a) - a.begin(); }

 public:
  vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int left = -1, right = mat.size() - 1;
    while (left + 1 < right) {
      int i = left + (right - left) / 2;
      int j = indexOfMax(mat[i]);
      (mat[i][j] > mat[i + 1][j] ? right : left) = i;
    }
    return {right, indexOfMax(mat[right])};
  }
};