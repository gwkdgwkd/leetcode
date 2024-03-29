/*
给你一个整数数组nums，返回数组answer，
其中answer[i]等于nums中除nums[i]之外其余各元素的乘积。
题目数据保证数组nums之中任意元素的全部前缀和后缀的乘积都在32位整数范围内。
请不要使用除法，且在O(n)时间复杂度内完成此题。

示例1：
输入：nums = [1,2,3,4]
输出：[24,12,8,6]

示例2：
输入：nums = [-1,1,0,-3,3]
输出：[0,0,9,0,0]

提示：
2 <= nums.length <= 10^5
-30 <= nums[i] <= 30
保证数组nums之中任意元素的全部前缀元素和后缀的乘积都在32位整数范围内

进阶：你可以在O(1)的额外空间复杂度内完成这个题目吗？
出于对空间复杂度分析的目的，输出数组不被视为额外空间。
*/

// 剑指Offer66构建乘积数组
// a.length <= 100000

// 前缀和
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
  // for 剑指Offer66
  // *returnSize = aSize;
  // if (aSize == 0) {
  //   return NULL;
  // }

  int left[numsSize];   // left[i]表示nums[0...i-1]元素的乘积
  int right[numsSize];  // right[i]表示nums[i+1...numsSize-1]元素的乘积
  left[0] = right[numsSize - 1] = 1;
  for (int i = 1; i < numsSize; ++i) {
    left[i] = left[i - 1] * nums[i - 1];
  }
  for (int i = numsSize - 2; i >= 0; --i) {
    right[i] = right[i + 1] * nums[i + 1];
  }

  int* ret = (int*)malloc(sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; ++i) {
    ret[i] = left[i] * right[i];
  }
  *returnSize = numsSize;

  return ret;
}

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();

    int left[n];  // left[i]为元素i左侧所有元素的乘积
    left[0] = 1;  // 对于索引为0的元素，因为左侧没有元素，所以left[0]=1
    for (int i = 0; i < n - 1; ++i) {
      left[i + 1] = left[i] * nums[i];
    }

    int right[n];  // right[i]为元素i右侧所有元素的乘积
    right[n - 1] = 0;  // 对于索引为n-1的元素，右侧没有元素，所以right[n-1]=1
    for (int i = n - 1; i > 0; --i) {
      right[i - 1] = right[i] * nums[i];
    }

    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
      res[i] = left[i] * right[i];
    }

    return res;
  }
};