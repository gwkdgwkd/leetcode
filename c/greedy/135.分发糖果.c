/*
n个孩子站成一排。给你一个整数数组ratings表示每个孩子的评分。
你需要按照以下要求，给这些孩子分发糖果：
每个孩子至少分配到1个糖果。
相邻两个孩子评分更高的孩子会获得更多的糖果。
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
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104
*/

// 贪心算法
int candy(int* ratings, int ratingsSize) {
  // 用了两次贪心的策略：
  // 一次是从左到右遍历，只比较右边孩子评分比左边大的情况。
  // 一次是从右到左遍历，只比较左边孩子评分比右边大的情况。
  // 这样从局部最优推出了全局最优，即：相邻的孩子中，评分高的孩子获得更多的糖果
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