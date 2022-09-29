/*
给你一个整数数组nums。
如果任一值在数组中出现至少两次，返回true；
如果数组中每个元素互不相同，返回false。

示例1：
输入：nums = [1,2,3,1]
输出：true

示例2：
输入：nums = [1,2,3,4]
输出：false

示例3：
输入：nums = [1,1,1,3,3,4,3,2,4,2]
输出：true

提示：
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
*/

// 暴力法，超时
bool containsDuplicate(int* nums, int numsSize) {
  for (int i = 0; i < numsSize - 1; ++i) {
    for (int j = i + 1; j < numsSize; ++j) {
      if (nums[i] == nums[j]) {
        return true;
      }
    }
  }

  return false;
}

// 排序
int cmp(int* a, int* b) { return *a - *b; }
bool containsDuplicate(int* nums, int numsSize) {
  qsort(nums, numsSize, sizeof(int), cmp);
  for (int i = 1; i < numsSize; ++i) {
    if (nums[i] == nums[i - 1]) {
      return true;
    }
  }

  return false;
}

// 哈希表
class Solution {
 public:
  bool containsDuplicate(vector<int>& nums) {
    unordered_set s(nums.begin(), nums.end());
    return nums.size() > s.size();
  }
};

class Solution {
 public:
  bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> s;
    for (int x : nums) {
      if (s.find(x) != s.end()) {
        return true;
      }
      s.insert(x);
    }
    return false;
  }
};