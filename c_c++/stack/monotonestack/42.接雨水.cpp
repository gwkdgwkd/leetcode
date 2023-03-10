/*
给定n个非负整数表示每个宽度为1的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例1：
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组[0,1,0,2,1,0,1,3,2,1,2,1]表示的高度图，可以接6个单位的雨水。

示例2：
输入：height = [4,2,0,3,2,5]
输出：9

提示：
n == height.length
1 <= n <= 2 * 10^4
*/

// 面试题1721直方图的水量

// 双指针，超时
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
int trap(int* height, int heightSize) {
  int ret = 0;

  for (int i = 0; i < heightSize; ++i) {
    int r = height[i];
    int l = height[i];
    // 使用了双指针来遍历，每到一个柱子都向两边遍历一遍，这其实是有重复计算的。
    for (int j = i + 1; j < heightSize; ++j) {
      if (height[j] > r) {
        r = height[j];
      }
    }
    for (int j = i - 1; j >= 0; --j) {
      if (height[j] > l) {
        l = height[j];
      }
    }

    ret += (fmin(l, r) - height[i]);
  }

  return ret;
}

// 动态规划
int trap(int* height, int heightSize) {
  if (heightSize <= 2) return 0;

  int l[heightSize];
  int r[heightSize];
  l[0] = height[0];
  for (int i = 1; i < heightSize; ++i) {
    l[i] = fmax(l[i - 1], height[i]);
  }
  r[heightSize - 1] = height[heightSize - 1];
  for (int i = heightSize - 2; i >= 0; --i) {
    r[i] = fmax(r[i + 1], height[i]);
  }

  int ret = 0;
  for (int i = 0; i < heightSize; ++i) {
    ret += fmin(l[i], r[i]) - height[i];
  }

  return ret;
}

// 单调栈
int trap(int* height, int heightSize) {
  int n = heightSize;
  if (n == 0) {
    return 0;
  }
  int ans = 0;
  int stk[n], top = 0;
  for (int i = 0; i < n; ++i) {
    while (top && height[i] > height[stk[top - 1]]) {  // 单调递减
      int stk_top = stk[--top];
      if (!top) {
        break;
      }
      // 栈顶和栈顶的下一个元素以及要入栈的三个元素来接水！
      int left = stk[top - 1];
      // 雨水的宽度是：凹槽右边的下标-凹槽左边的下标-1（因为只求中间宽度）：
      int currWidth = i - left - 1;
      // 雨水高度是：min(凹槽左边高度,凹槽右边高度)-凹槽底部高度：
      int currHeight = fmin(height[left], height[i]) - height[stk_top];
      // 当前凹槽雨水的体积就是：
      ans += currWidth * currHeight;
    }
    stk[top++] = i;
  }
  return ans;
}

class Solution {
 public:
  int trap(vector<int>& height) {
    int ans = 0;
    stack<int> stk;
    int n = height.size();
    for (int i = 0; i < n; ++i) {
      while (!stk.empty() && height[i] > height[stk.top()]) {
        int top = stk.top();
        stk.pop();
        if (stk.empty()) {
          break;
        }
        int left = stk.top();
        int currWidth = i - left - 1;
        int currHeight = min(height[left], height[i]) - height[top];
        ans += currWidth * currHeight;
      }
      stk.push(i);
    }
    return ans;
  }
};