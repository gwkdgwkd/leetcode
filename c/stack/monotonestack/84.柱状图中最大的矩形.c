/*
给定n个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为1。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

示例1:
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为10

示例2：
输入： heights = [2,4]
输出：4

提示：
1 <= heights.length <=105
0 <= heights[i] <= 104
*/

// 剑指OfferII039直方图最大矩形面积

// 双指针，超时
int largestRectangleArea(int* heights, int heightsSize) {
  int sum = 0;
  for (int i = 0; i < heightsSize; ++i) {
    int l = i;
    int r = i;
    for (; r < heightsSize; ++r) {
      if (heights[r] < heights[i]) break;
    }
    for (; l >= 0; --l) {
      if (heights[l] < heights[i]) break;
    }
    sum = fmax(sum, (r - l - 1) * heights[i]);
  }
  return sum;
}

// 动态规划，是吗？
int largestRectangleArea(int* heights, int heightsSize) {
  int l[heightsSize];  // 记录每个柱子左边第一个小于该柱子的下标
  l[0] = -1;           // 注意这里初始化，防止下面while死循环
  for (int i = 1; i < heightsSize; ++i) {
    int t = i - 1;
    // 这里不是用if，而是不断向左寻找的过程
    while (t >= 0 && heights[t] >= heights[i]) t = l[t];
    l[i] = t;
  }

  int r[heightsSize];  // 记录每个柱子右边第一个小于该柱子的下标
  r[heightsSize - 1] = heightsSize;  // 注意这里初始化，防止下面while死循环
  for (int i = heightsSize - 2; i >= 0; i--) {
    int t = i + 1;
    // 这里不是用if，而是不断向右寻找的过程
    while (t < heightsSize && heights[t] >= heights[i]) t = r[t];
    r[i] = t;
  }

  int result = 0;
  for (int i = 0; i < heightsSize; i++) {
    int sum = heights[i] * (r[i] - l[i] - 1);
    result = fmax(sum, result);
  }
  return result;
}

// 单调栈
// 时间复杂度：O(N)
// 空间复杂度：O(N)
int largestRectangleArea(int* heights, int heightsSize) {
  int stack[heightsSize + 2];
  int top = 0;

  int data[heightsSize + 2];  // 哨兵，简化代码
  data[0] = data[heightsSize + 1] = 0;
  for (int i = 1; i <= heightsSize; ++i) {
    data[i] = heights[i - 1];  // 前后都多加个0
  }

  // top：1对应heights[0],对应data[1]
  stack[top] = 0;
  int ret = 0;
  for (int i = 1; i < heightsSize + 2; ++i) {
    while (top > 0 && data[i] <= data[stack[top]]) {
      ret = fmax(ret, data[stack[top]] * (i - stack[top - 1] - 1));
      top--;
    }
    stack[++top] = i;
  }

  return ret;
}
