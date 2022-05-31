/*
堆箱子。给你一堆n个箱子，箱子宽wi、深di、高hi。
箱子不能翻转，将箱子堆起来时，下面箱子的宽度、高度和深度必须大于上面的箱子。
实现一种方法，搭出最高的一堆箱子。
箱堆的高度为每个箱子高度的总和。
输入使用数组[wi, di, hi]表示每个箱子。

示例1:
输入：box = [[1, 1, 1], [2, 2, 2], [3, 3, 3]]
输出：6

示例2:
输入：box = [[1, 1, 1], [2, 3, 4], [2, 6, 7], [3, 4, 5]]
输出：10

提示:箱子的数目不大于3000个。
*/

int cmp(int **a1, int **b1) {
  int *a = *a1;
  int *b = *b1;
  int w1 = a[0];
  int d1 = a[1];
  int h1 = a[2];
  int w2 = b[0];
  int d2 = b[1];
  int h2 = b[2];
  if (w1 <= w2 && d1 <= d2 && h1 <= h2) {
    return -1;
  } else {
    return h1 - h2;
  }
}
int pileBox(int **box, int boxSize, int *boxColSize) {
  if (boxSize == 0) {
    return 0;
  }
  int i, j, t;
  qsort(box, boxSize, sizeof(int *), cmp);
  // for (i = 0; i < boxSize; i++) {
  //     printf("%d %d %d\n", box[i][0], box[i][1], box[i][2]);
  // }
  int dp[boxSize];
  int max = 0;
  for (i = 0; i < boxSize; i++) {
    dp[i] = box[i][2];
    for (j = 0; j < i; j++) {
      if (box[i][0] > box[j][0] && box[i][1] > box[j][1] &&
          box[i][2] > box[j][2]) {
        t = dp[j] + box[i][2];
        dp[i] = dp[i] > t ? dp[i] : t;
      }
    }
    max = max > dp[i] ? max : dp[i];
  }
  return max;
}

class Solution {
 public:
  int pileBox(vector<vector<int>> &box) {
    sort(box.begin(), box.end());
    int n = box.size();
    vector<int> dp(n);
    int max = 0;
    for (int i = 0; i < n; ++i) {
      dp[i] = box[i][2];
      max = std::max(max, dp[i]);
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (box[i][0] > box[j][0] && box[i][1] > box[j][1] &&
            box[i][2] > box[j][2]) {
          dp[i] = std::max(dp[i], dp[j] + box[i][2]);
          max = std::max(max, dp[i]);
        }
      }
    }

    return max;
  }
};

class Solution {
 public:
  int pileBox(vector<vector<int>> &box) {
    sort(box.begin(), box.end());
    int n = box.size();
    vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
      dp[i] = box[i][2];
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (box[i][0] > box[j][0] && box[i][1] > box[j][1] &&
            box[i][2] > box[j][2]) {
          dp[i] = max(dp[i], dp[j] + box[i][2]);
        }
      }
    }

    return *max_element(dp.begin(), dp.end());
  }
};