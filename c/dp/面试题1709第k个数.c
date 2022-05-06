/*
有些数的素因子只有3，5，7，请设计一个算法找出第k个数。
注意，不是必须有这些素因子，而是必须不包含其他的素因子。
例如，前几个数按顺序应该是1，3，5，7，9，15，21。

示例1:
输入: k = 5
输出: 9
*/

// 类似丑数
int getKthMagicNumber(int k) {
  int* nums = (int*)calloc(k, sizeof(int));
  nums[0] = 1;  // 这就有点动态规划的意思了
  int i;
  int i3 = 0;
  int i5 = 0;
  int i7 = 0;
  for (i = 1; i < k; i++) {  // 注意这里的i从1开始索引
    nums[i] = fmin(fmin(nums[i3] * 3, nums[i5] * 5), nums[i7] * 7);
    // 这里不能用if-else，是因为有可能出现即是3的倍数也是5的倍数的
    if (nums[i] == nums[i3] * 3) {
      i3++;
    }
    if (nums[i] == nums[i5] * 5) {
      i5++;
    }
    if (nums[i] == nums[i7] * 7) {
      i7++;
    }
  }
  return nums[k - 1];
}