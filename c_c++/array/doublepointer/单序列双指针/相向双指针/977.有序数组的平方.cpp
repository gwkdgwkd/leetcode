/*
给一个按非递减顺序排序的整数数组nums，
返回每个数字的平方组成的新数组，要求也按非递减顺序排序。

示例1：
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为[16,1,0,9,100]
排序后，数组变为[0,1,9,16,100]

示例2：
输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]

提示：
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums已按非递减顺序排序

进阶：请设计时间复杂度为O(n)的算法解决本问题
*/

// 双指针，时间复杂度为O(n)
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
  int left = 0;
  int right = numsSize - 1;

  *returnSize = numsSize;
  int* ans = (int*)malloc(sizeof(int) * numsSize);
  int i = numsSize - 1;

  while (left <= right) {
    int t1 = nums[left] * nums[left];
    int t2 = nums[right] * nums[right];
    if (t1 > t2) {
      ans[i--] = t1;
      ++left;
    } else {
      ans[i--] = t2;
      --right;
    }
  }

  return ans;
}

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& nums) {
    int len = nums.size();
    int left = 0;
    int right = len - 1;

    vector<int> res(len);
    int i = len - 1;
    while (left <= right) {
      int t1 = nums[left] * nums[left];
      int t2 = nums[right] * nums[right];
      if (t1 > t2) {
        res[i--] = t1;
        ++left;
      } else {
        res[i--] = t2;
        --right;
      }
    }

    return res;
  }
};
