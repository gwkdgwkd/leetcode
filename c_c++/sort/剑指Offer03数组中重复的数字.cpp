/*
找出数组中重复的数字，在一个长度为n的数组nums里的所有数字都在0～n-1的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
请找出数组中任意一个重复的数字。

示例1：
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2或3

限制：
2 <= n <= 100000
*/

// 排序
int cmp(int *a, int *b) { return *a - *b; }
int findRepeatNumber(int *nums, int numsSize) {
  qsort(nums, numsSize, sizeof(int), cmp);
  for (int i = 1; i < numsSize; ++i) {
    if (nums[i] == nums[i - 1]) {
      return nums[i];
    }
  }

  return 0;
}

// 哈希表
int findRepeatNumber(int *nums, int numsSize) {
  int hash[numsSize];
  memset(hash, 0, sizeof(hash));

  for (int i = 0; i < numsSize; ++i) {
    hash[nums[i]]++;
    if (hash[nums[i]] > 1) {
      return nums[i];
    }
  }

  return 0;
}

class Solution {
 public:
  int findRepeatNumber(vector<int> &nums) {
    unordered_set<int> s;
    for (const auto &num : nums) {
      if (s.count(num)) {
        return num;
      }
      s.insert(num);
    }
    return 0;
  }
};