// 一个数和它本身做异或运算结果为0，即a^a=0；一个数和0做异或运算的结果为它本身，即a^0=a。
int singleNumber(int* nums, int numsSize) {
  int res = 0;
  for (int i = 0; i < numsSize; ++i) {
    res ^= nums[i];
  }

  return res;
}