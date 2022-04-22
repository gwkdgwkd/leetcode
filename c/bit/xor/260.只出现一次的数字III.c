/*
给定一个整数数组nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。
找出只出现一次的那两个元素。
你可以按任意顺序返回答案。

进阶：你的算法应该具有线性时间复杂度。你能否仅使用常数空间复杂度来实现？

示例1：
输入：nums = [1,2,1,3,2,5]
输出：[3,5]
解释：[5, 3]也是有效的答案。

示例2：
输入：nums = [-1,0]
输出：[-1,0]

示例3：
输入：nums = [0,1]
输出：[1,0]

提示：
2 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
除两个只出现一次的整数外，nums中的其他数字都出现两次
*/

int* singleNumber(int* nums, int numsSize, int* returnSize) {
  // 1.把所有的元素进行异或操作，最终得到一个异或值
  //   因为是不同的两个数字，所以这个值必定不为0
  long xor = 0;
  for (int i = 0; i < numsSize; ++i) {
    xor ^= nums[i];
  }

  *returnSize = 2;
  int* res = (int*)malloc(sizeof(int) * 2);
  memset(res, 0, sizeof(int) * 2);

  // 2.取异或值最后一个二进制位为1的数字作为mask，如果是1则表示两个数字在这一位上不同
  long mask = xor&(-xor);

  for (int i = 0; i < numsSize; ++i) {
    // 3.通过与这个mask进行与操作，如果为0的分为一个数组，为1的分为另一个数组
    //   这样就把问题降低成了：“有一个数组每个数字都出现两次，有一个数字只出现了一次，求出该数字”
    if ((nums[i] & mask) == mask) {
      res[0] ^= nums[i];
    } else {
      res[1] ^= nums[i];
    }
  }
  return res;
}