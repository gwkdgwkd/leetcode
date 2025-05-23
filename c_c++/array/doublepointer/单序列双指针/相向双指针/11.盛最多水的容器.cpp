/*
给定一个长度为n的整数数组height。
有n条垂线，第i条线的两个端点是(i, 0)和(i, height[i])。
找出其中的两条线，使得它们与x轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。
说明：你不能倾斜容器。

示例1：
输入：[1,8,6,2,5,4,8,3,7]
输出：49
解释：在此情况下，容器能够容纳水的最大值为49。

示例2：
输入：height = [1,1]
输出：1

提示：
n == height.length
2 <= n <= 10^5
0 <= height[i] <= 10^4
*/

// 暴力法，超时
int maxArea(int* height, int heightSize) {
  int max = 0;
  for (int i = 0; i < heightSize - 1; ++i) {
    for (int j = i + 1; j < heightSize; ++j) {
      int h = fmin(height[i], height[j]);
      int w = j - i;
      max = fmax(max, h * w);
    }
  }

  return max;
}

// 双指针，O(n)
// 为什么移动短的下标是正确的？
// 开始时，高是第一个柱子和最后一个柱子较小的，宽（最大）是数组长度减一
// 假设第一个柱子比最后一个柱子小，然后移动大的柱子，
// 此时宽是变小的，右边柱子无论移动到哪里，高的值为第一个柱子，
// 意味着移动高的柱子面积不会再变大，所以需要移动第一个柱子，也就是小的柱子。
int maxArea(int* height, int heightSize) {
  int left = 0;
  int right = heightSize - 1;
  int max = 0;
  while (left < right) {
    int h = fmin(height[left], height[right]);
    int w = right - left;
    max = fmax(max, h * w);
    if (height[left] <= height[right]) {
      ++left;
    } else {
      --right;
    }
  }

  return max;
}

class Solution {
  // 设两指针i,j，指向的水槽板高度分别为h[i],h[j]，此状态下水槽面积为S(i,j)。
  // 由于可容纳水的高度由两板中的短板决定，因此可得如下面积公式：
  // S(i,j)=min(h[i],h[j])×(j−i)
  // 在每个状态下，无论长板或短板向中间收窄一格，都会导致水槽底边宽度−1变短：
  // 若向内移动短板，水槽的短板min(h[i],h[j])可能变大，因此下个水槽的面积可能增大。
  // 若向内移动长板，水槽的短板min(h[i],h[j])不变或变小，因此下个水槽的面积一定变小。
  // 因此，初始化双指针分列水槽左右两端，循环每轮将短板向内移动一格，
  // 并更新面积最大值，直到两指针相遇时跳出，即可获得最大面积。

 public:
  int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;

    int res = 0;
    while (left < right) {
      int h = fmin(height[left], height[right]);
      int w = right - left;

      res = max(res, h * w);
      height[left] > height[right] ? --right : ++left;
    }

    return res;
  }
};

class Solution {
 public:
  int maxArea(vector<int>& height) {
    int ans = 0, left = 0, right = height.size() - 1;
    while (left < right) {
      int area = (right - left) * min(height[left], height[right]);
      ans = max(ans, area);
      height[left] < height[right] ? left++ : right--;
    }
    return ans;
  }
};