int* findErrorNums(int* nums, int numsSize, int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;
  int dup = -1;
  for (int i = 0; i < numsSize; i++) {
    int index = abs(nums[i]) - 1;  // 索引应该从0开始
    if (nums[index] < 0)
      dup = abs(nums[i]);
    else
      nums[index] *= -1;
  }
  res[0] = dup;

  int missing = -1;
  for (int i = 0; i < numsSize; i++)
    if (nums[i] > 0) missing = i + 1;  // 将索引转换成元素
  res[1] = missing;

  return res;
}

// 位运算
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;

  int n = numsSize;
  int xorVal = 0;
  // 1.经过下面两个循环体后，xorVal保存重复整数与丢失整数的异或运算结果
  for (int i = 1; i <= n; i++) {
    xorVal ^= i;
  }
  for (int i = 0; i < n; ++i) {
    xorVal ^= nums[i];
  }
  // 2.确定mask的值，为分组做准备
  int mask = 1;
  while ((xorVal & mask) == 0) {
    mask <<= 1;
  }
  // 3.进行分组之间的异或运算，求出两个目标整数的值
  int a = 0, b = 0;
  for (int i = 1; i <= n; i++) {
    if ((i & mask) == 0) {
      a ^= i;
    } else {
      b ^= i;
    }
  }
  for (int i = 0; i < n; ++i) {
    if ((nums[i] & mask) == 0) {
      a ^= nums[i];
    } else {
      b ^= nums[i];
    }
  }
  // 4.区分出重复整数和丢失整数
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (nums[i] == a) {
      count++;
    }
  }
  if (count == 2) {
    res[0] = a;
    res[1] = b;
    return res;
  }
  res[0] = b;
  res[1] = a;
  return res;
}