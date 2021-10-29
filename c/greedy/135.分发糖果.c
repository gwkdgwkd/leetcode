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