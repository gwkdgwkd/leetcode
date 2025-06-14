/*
n个孩子站成一排。给一个整数数组ratings表示每个孩子的评分。
你需要按照以下要求，给这些孩子分发糖果：
每个孩子至少分配到1个糖果，相邻两个孩子评分更高的孩子会获得更多的糖果。
请你给每个孩子分发糖果，计算并返回需要准备的最少糖果数目。

示例1：
输入：ratings = [1,0,2]
输出：5
解释：你可以分别给第一个、第二个、第三个孩子分发2、1、2颗糖果。

示例2：
输入：ratings = [1,2,2]
输出：4
解释：你可以分别给第一个、第二个、第三个孩子分发1、2、1颗糖果。
     第三个孩子只得到1颗糖果，这满足题面中的两个条件。

提示：
n == ratings.length
1 <= n <= 2 * 10^4
0 <= ratings[i] <= 2 * 10^4
*/

// 贪心算法
int candy(int* ratings, int ratingsSize) {
  // 用了两次贪心的策略：
  // 一次是从左到右遍历，只比较右边孩子评分比左边大的情况。
  // 一次是从右到左遍历，只比较左边孩子评分比右边大的情况。
  // 这样从局部最优推出了全局最优，即相邻的孩子中，评分高的孩子获得更多的糖果。
  int candy[ratingsSize];
  for (int i = 0; i < ratingsSize; ++i) {
    candy[i] = 1;
  }
  // 从前向后
  for (int i = 1; i < ratingsSize; i++) {
    if (ratings[i] > ratings[i - 1]) candy[i] = candy[i - 1] + 1;
  }
  // 从后向前
  for (int i = ratingsSize - 2; i >= 0; i--) {
    if (ratings[i] > ratings[i + 1]) {
      candy[i] = fmax(candy[i], candy[i + 1] + 1);
    }
  }
  // 统计结果
  int result = 0;
  for (int i = 0; i < ratingsSize; i++) result += candy[i];
  return result;
}

class Solution {
 public:
  int candy(vector<int>& ratings) {
    int n = ratings.size();

    vector<int> candy(n, 1);
    for (int i = 1; i < n; ++i) {
      if (ratings[i] > ratings[i - 1]) {
        candy[i] = candy[i - 1] + 1;
      }
    }

    for (int i = n - 2; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) {
        candy[i] = max(candy[i], candy[i + 1] + 1);
      }
    }

    return accumulate(candy.begin(), candy.end(), 0);
  }
};

class Solution {
 public:
  int candy(vector<int>& ratings) {
    int n = ratings.size();

    int ans = n;  // 先给每人分一个
    for (int i = 0; i < n; i++) {
      int start = i > 0 && ratings[i - 1] < ratings[i] ? i - 1 : i;
      // 找严格递增段
      while (i + 1 < n && ratings[i] < ratings[i + 1]) {
        i++;
      }

      int top = i;  // 峰顶
      // 找严格递减段
      while (i + 1 < n && ratings[i] > ratings[i + 1]) {
        i++;
      }

      int inc = top - start;  // start到top严格递增
      int dec = i - top;      // top到i严格递减
      ans += (inc * (inc - 1) + dec * (dec - 1)) / 2 + max(inc, dec);
    }

    return ans;
  }
};