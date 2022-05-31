/*
找出所有相加之和为n的k个数的组合，且满足下列条件：
只使用数字1到9，每个数字最多使用一次。
返回所有可能的有效组合的列表。
该列表不能包含相同的组合两次，组合可以以任何顺序返回。

示例1:
输入: k = 3, n = 7
输出: [[1,2,4]]
解释:
1 + 2 + 4 = 7
没有其他符合的组合了。

示例2:
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
解释:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
没有其他符合的组合了。

示例3:
输入: k = 4, n = 1
输出: []
解释: 不存在有效的组合。
在[1,9]范围内使用4个不同的数字，我们可以得到的最小和是1+2+3+4 = 10，
因为10 > 1，没有有效的组合。

提示:
2 <= k <= 9
1 <= n <= 60
*/

// 回溯算法
int **result;
int resultSize;
int *path;
int pathSize;
void backtracking(int k, int n, int startIndex) {
  if (n < 0) {
    return;
  }
  if (pathSize == k) {
    if (0 == n) {
      result[resultSize] = (int *)malloc(sizeof(int) * k);
      for (int i = 0; i < k; ++i) {
        result[resultSize][i] = path[i];
      }
      resultSize++;
      return;
    }
    return;
  }

  // for(int i = startIndex; i <= 9; ++i) {
  for (int i = startIndex; i <= 9 - (k - pathSize) + 1 && n >= i; ++i) {
    path[pathSize++] = i;
    // printf("%*d[%d %d %d]\n", pathSize * 2, i, n, k, startIndex);
    backtracking(k, n - i, i + 1);
    pathSize--;
  }
  // 3 7
  //  1[7 3 1]
  //    2[6 3 2]
  //      3[4 3 3]
  //      4[4 3 3]
  //    3[6 3 2]
  //    4[6 3 2]
  //    5[6 3 2]
  //    6[6 3 2]
  //  2[7 3 1]
  //    3[5 3 3]
  //    4[5 3 3]
  //    5[5 3 3]
  //  3[7 3 1]
  //    4[4 3 4]
  //  4[7 3 1]
  //  5[7 3 1]
  //  6[7 3 1]
  //  7[7 3 1]

  return;
}
int **combinationSum3(int k, int n, int *returnSize, int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 2001);
  path = (int *)malloc(sizeof(int) * k);
  resultSize = pathSize = 0;
  backtracking(k, n, 1);
  *returnSize = resultSize;
  *returnColumnSizes = malloc(sizeof(int) * resultSize);
  for (int i = 0; i < resultSize; i++) {
    (*returnColumnSizes)[i] = k;
  }

  return result;
}

class Solution {
  vector<vector<int>> ans;
  vector<int> path;
  void backtracking(int k, int target, int start) {
    if (target < 0) {
      return;
    }
    if (path.size() == k) {
      if (target == 0) {
        ans.emplace_back(path);
      }
      return;
    }

    for (int i = start; i <= 9 - (k - path.size()) + 1 && target >= i; ++i) {
      path.emplace_back(i);
      backtracking(k, target - i, i + 1);
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> combinationSum3(int k, int n) {
    backtracking(k, n, 1);
    return ans;
  }
};