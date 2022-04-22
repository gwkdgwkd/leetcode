/*
给你一个整数数组nums，除某个元素仅出现一次外，其余每个元素都恰出现三次。
请你找出并返回那个只出现了一次的元素。

示例1：
输入：nums = [2,2,3,2]
输出：3

示例2：
输入：nums = [0,1,0,1,0,1,99]
输出：99

提示：
1 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
nums中，除某个元素仅出现一次外，其余每个元素都恰出现三次

进阶：你的算法应该具有线性时间复杂度。你可以不使用额外空间来实现吗？
*/

// 依次确定每一个二进制位
// 答案的第i个二进制位就是数组中所有元素的第i个二进制位之和除以3的余数。
int singleNumber(int* nums, int numsSize) {
  int ans = 0;
  for (int i = 0; i < 32; ++i) {
    int total = 0;
    for (int j = 0; j < numsSize; ++j) {
      // 把所有元素的的第i位相加
      total += ((nums[j] >> i) & 1);
    }
    if (total % 3) {  // 余数不为零，表示答案的第i位为1
      ans |= (1u << i);
    }
  }
  return ans;
}

// 数字电路的思路
int singleNumber(int* nums, int numsSize) {
  // int one = 0, two = 0, temp = 0;
  // for (int i = 0; i < numsSize; ++i) {
  //     temp = (two & nums[i]) | (one & ~nums[i]);
  //     two = (~one & ~two & nums[i]) | (two & ~nums[i]);
  //     one = temp;
  // }
  // return two;

  // int one = 0, two = 0, three = 0;
  // for (int i = 0; i < numsSize; ++i) {
  //   // 二进制某位出现1次时twos = 0，出现2, 3次时twos = 1；
  //   two |= one & nums[i];
  //   // 二进制某位出现2次时ones = 0，出现1, 3次时ones = 1；
  //   one ^= nums[i];
  //   // 二进制某位出现3次时（即twos = ones = 1时）three = 1，其余即出现1, 2次时three = 0；
  //   three = one & two;
  //   // 将二进制下出现3次的位置零，实现`三进制下不考虑进位的加法`；
  //   one &= ~three;
  //   two &= ~three;
  // }
  // return one;

  int one = 0, two = 0;
  for (int i = 0; i < numsSize; ++i) {
    // 1.当num=1时，只当one=two=0时将one置1，代表出现3N+1次；
    //   其余置0，根据two值分别代表出现3N次和3N+2次；
    // 2.当num=0时，one不变。
    one = one ^ nums[i] & ~two;

    // 1.当num=1时，只当one=two=0时将two置1，代表出现3N+2次；
    //   其余置0，根据one值分别代表出现3N次和3N+1次；
    // 2.当num=0时，twos不变。
    two = two ^ nums[i] & ~one;
  }
  return one;
}