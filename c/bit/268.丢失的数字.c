// 排序解法的时间复杂度是O(NlogN)，HashSet的解法时间复杂度是O(N)，但是还需要O(N) 的空间复杂度存储HashSet。

// 位运算
// 时间复杂度：O(N)
// 空间复杂度：O(1)
int missingNumber(int* nums, int numsSize) {
  int i;
  int sum = 0;

  for (i = 0; i < numsSize; ++i) {
    sum ^= i ^ nums[i];
  }
  sum ^= i;

  return sum;
}

// 等差公式求和
int missingNumber(int* nums, int numsSize) {
  // 公式：(首项 + 末项) * 项数 / 2
  int expect = (0 + numsSize) * (numsSize + 1) / 2;  // 考虑过整型溢出

  int sum = 0;
  for (int i = 0; i < numsSize; ++i) sum += nums[i];
  return expect - sum;
}

// 边增加边减
int missingNumber(int* nums, int numsSize) {
  int n = numsSize;
  int res = 0;
  res += n - 0;
  for (int i = 0; i < n; i++) res += i - nums[i];
  return res;
}