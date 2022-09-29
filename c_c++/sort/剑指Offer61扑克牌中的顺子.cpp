/*
从若干副扑克牌中随机抽5张牌，
判断是不是一个顺子，即这5张牌是不是连续的。
2～10为数字本身，A为1，J为11，Q为12，K为13，
而大、小王为0，可以看成任意数字。
A不能视为14。

示例1:
输入: [1,2,3,4,5]
输出: True

示例2:
输入: [0,0,1,2,5]
输出: True

限制：
数组长度为5
数组的数取值为[0, 13]
*/

// 排序
int cmp(int* a, int* b) { return *a - *b; }
bool isStraight(int* nums, int numsSize) {
  qsort(nums, numsSize, sizeof(int), cmp);

  int count = 0;
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] == 0) {
      ++count;
      continue;
    }
    if (i > 0 && nums[i] == nums[i - 1]) {
      return false;
    }
  }

  return nums[numsSize - 1] - nums[count] < 5;
}

// 哈希表
bool isStraight(int* nums, int numsSize) {
  int hash[14];
  memset(hash, 0, sizeof(hash));
  int max = 0;
  int min = 14;
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] == 0) {
      continue;
    }
    hash[nums[i]]++;
    if (i > 0 && hash[nums[i]] > 1) {
      return false;
    }
    max = fmax(max, nums[i]);
    min = fmin(min, nums[i]);
  }

  return max - min < 5;
}

class Solution {
 public:
  bool isStraight(vector<int>& nums) {
    int hash[14] = {0};
    int mx = 0;
    int mn = 14;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        continue;
      }
      hash[nums[i]]++;
      if (i > 0 && hash[nums[i]] > 1) {
        return false;
      }
      mx = max(mx, nums[i]);
      mn = min(mn, nums[i]);
    }

    return mx - mn < 5;
  }
};