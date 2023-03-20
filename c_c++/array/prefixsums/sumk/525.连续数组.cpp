/*
给定一个二进制数组nums，找到含有相同数量的0和1的最长连续子数组，并返回该子数组的长度。

示例1：
输入：nums = [0,1]
输出：2
说明：[0, 1]是具有相同数量0和1的最长连续子数组。

示例2：
输入：nums = [0,1,0]
输出：2
说明：[0, 1](或[1, 0])是具有相同数量0和1的最长连续子数组。

提示：
1 <= nums.length <= 10^5
nums[i]不是0就是1
*/

// 剑指OfferII011.0和1个数相同的子数组

struct HashTable {
  int key, val;
  UT_hash_handle hh;
};
int findMaxLength(int* nums, int numsSize) {
  int maxLength = 0;
  struct HashTable* hashTable = NULL;
  struct HashTable* tmp = malloc(sizeof(struct HashTable));
  tmp->key = 0, tmp->val = -1;
  HASH_ADD_INT(hashTable, key, tmp);
  int counter = 0;
  int n = numsSize;
  for (int i = 0; i < n; i++) {
    int num = nums[i];
    if (num == 1) {
      counter++;
    } else {
      counter--;
    }
    HASH_FIND_INT(hashTable, &counter, tmp);
    if (tmp != NULL) {
      int prevIndex = tmp->val;
      maxLength = fmax(maxLength, i - prevIndex);
    } else {
      tmp = malloc(sizeof(struct HashTable));
      tmp->key = counter, tmp->val = i;
      HASH_ADD_INT(hashTable, key, tmp);
    }
  }
  return maxLength;
}

class Solution {
 public:
  int findMaxLength(vector<int>& nums) {
    // key保存[0...i-1]的元素和，value保存下标i
    unordered_map<int, int> hash;
    int n = nums.size();

    int sum = 0;
    hash[sum] = -1;  // 保证找到第一个解时，i-hash[sum]表示正确
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      // 把0当成-1，求和为0最长连续子数组：
      sum += (nums[i] == 1 ? 1 : -1);
      if (hash.find(sum) != hash.end()) {
        // 有和当前sum一样的index，也就是说，
        // 0到hash[sum]的元素和，与0到当前索引i的元素和一样，
        // 意味着，hash[sum]到i之间的元素和为0，找到一个解：
        ans = max(ans, i - hash[sum]);
      } else {
        hash[sum] = i;
      }
    }

    return ans;
  }
};