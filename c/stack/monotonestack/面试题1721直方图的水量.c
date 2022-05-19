/*
给定一个直方图(也称柱状图)，假设有人从上面源源不断地倒水，
最后直方图能存多少水量?直方图的宽度为 1。
上面是由数组[0,1,0,2,1,0,1,3,2,1,2,1]表示的直方图，
在这种情况下，可以接6个单位的水（蓝色部分表示水）。

示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/

// 单调栈
int trap(int* height, int heightSize) {
  int n = heightSize;
  if (n == 0) {
    return 0;
  }
  int ans = 0;
  int stk[n], top = 0;
  for (int i = 0; i < n; ++i) {
    while (top && height[i] > height[stk[top - 1]]) {
      int stk_top = stk[--top];
      if (!top) {
        break;
      }
      int left = stk[top - 1];
      int currWidth = i - left - 1;
      int currHeight = fmin(height[left], height[i]) - height[stk_top];
      ans += currWidth * currHeight;
    }
    stk[top++] = i;
  }
  return ans;
}

// 双指针
int trap(int* height, int heightSize) {
  int ans = 0;
  int left = 0, right = heightSize - 1;
  int leftMax = 0, rightMax = 0;
  while (left < right) {
    leftMax = fmax(leftMax, height[left]);
    rightMax = fmax(rightMax, height[right]);
    if (height[left] < height[right]) {
      ans += leftMax - height[left];
      ++left;
    } else {
      ans += rightMax - height[right];
      --right;
    }
  }
  return ans;
}

// 动态规划
int trap(int* height, int heightSize) {
  int n = heightSize;
  if (n == 0) {
    return 0;
  }
  int leftMax[n];
  memset(leftMax, 0, sizeof(leftMax));
  leftMax[0] = height[0];
  for (int i = 1; i < n; ++i) {
    leftMax[i] = fmax(leftMax[i - 1], height[i]);
  }

  int rightMax[n];
  memset(rightMax, 0, sizeof(rightMax));
  rightMax[n - 1] = height[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    rightMax[i] = fmax(rightMax[i + 1], height[i]);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += fmin(leftMax[i], rightMax[i]) - height[i];
  }
  return ans;
}