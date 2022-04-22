/*
一个整型数组nums里除两个数字之外，其他数字都出现了两次。
请写程序找出这两个只出现一次的数字。
要求时间复杂度是O(n)，空间复杂度是O(1)。

示例1：
输入：nums = [4,1,4,6]
输出：[1,6] 或 [6,1]

示例2：
输入：nums = [1,2,10,4,1,4,3,3]
输出：[2,10]或[10,2]

限制：2 <= nums.length <= 10000
*/

int* singleNumbers(int* nums, int numsSize, int* returnSize) {
  long xor = 0;
  for (int i = 0; i < numsSize; ++i) {
    xor ^= nums[i];
  }

  int* res = (int*)calloc(2, sizeof(int));
  *returnSize = 2;

  long mask = xor&(-xor);
  for (int i = 0; i < numsSize; ++i) {
    if ((nums[i] & mask) == mask) {
      res[0] ^= nums[i];
    } else {
      res[1] ^= nums[i];
    }
  }

  return res;
}