/*
给定一个数组nums和滑动窗口的大小k，请找出所有滑动窗口里的最大值。

示例:
输入: nums = [1,3,-1,-3,5,3,6,7],和k = 3
输出: [3,3,5,5,6,7] 
解释: 
  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

提示：
你可以假设k总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。

注意：本题与239题相同
*/

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  *returnSize = 0;
  if (numsSize == 0) {
    return NULL;
  }

  int* res = (int*)malloc(sizeof(int) * (numsSize - k + 1));
  int queue[numsSize];
  int head = 0;
  int tail = 0;

  for (int i = 0; i < numsSize; ++i) {
    while (head < tail && queue[head] <= i - k) {
      ++head;
    }

    while (head < tail && nums[queue[tail - 1]] <= nums[i]) {
      --tail;
    }
    queue[tail++] = i;
    if (i >= k - 1) {
      res[(*returnSize)++] = nums[queue[head]];
    }
  }

  return res;
}