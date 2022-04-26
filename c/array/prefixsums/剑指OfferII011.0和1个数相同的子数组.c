/*
给定一个二进制数组nums, 找到含有相同数量的0和1的最长连续子数组，并返回该子数组的长度。

示例1：
输入: nums = [0,1]
输出: 2
说明: [0, 1]是具有相同数量0和1的最长连续子数组。

示例2：
输入: nums = [0,1,0]
输出: 2
说明: [0, 1](或[1, 0])是具有相同数量0和1的最长连续子数组。

提示：
1 <= nums.length <= 105
nums[i]不是0就是1

注意：本题与525题相同
*/

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