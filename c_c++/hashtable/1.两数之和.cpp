/*
给定一个整数数组nums和一个整数目标值target，找出和为目标值target的那两个整数，
并返回它们的数组下标，可以假设每种输入只会对应一个答案。
但是，数组中同一个元素在答案里不能重复出现，可以按任意顺序返回答案。

示例1：
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为nums[0] + nums[1] == 9，返回[0, 1] 。

示例2：
输入：nums = [3,2,4], target = 6
输出：[1,2]

示例3：
输入：nums = [3,3], target = 6
输出：[0,1]


提示：
2 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
只会存在一个有效答案

进阶：可以想出一个时间复杂度小于O(n^2)的算法吗？
*/

// 哈希表
// 时间复杂度：O(N)
// 空间复杂度：O(N)
// 一般情况下，会首先把数组排序再考虑双指针技巧。
// HashMap或者HashSet也可以帮助处理无序数组相关的简单问题。
struct hashTable {
  int key;
  int val;
  UT_hash_handle hh;
};
struct hashTable* hashtable;
struct hashTable* find(int ikey) {
  struct hashTable* tmp;
  HASH_FIND_INT(hashtable, &ikey, tmp);
  return tmp;
}
void insert(int ikey, int ival) {
  struct hashTable* it = find(ikey);
  if (it == NULL) {
    struct hashTable* tmp = malloc(sizeof(struct hashTable));
    tmp->key = ikey, tmp->val = ival;
    HASH_ADD_INT(hashtable, key, tmp);
  } else {
    it->val = ival;
  }
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  hashtable = NULL;
  for (int i = 0; i < numsSize; i++) {
    struct hashTable* it = find(target - nums[i]);
    if (it != NULL) {
      int* ret = malloc(sizeof(int) * 2);
      ret[0] = it->val, ret[1] = i;
      *returnSize = 2;
      return ret;
    }
    insert(nums[i], i);
  }
  *returnSize = 0;
  return NULL;
}

// 暴力法
// 时间复杂度：O(N^2)
// 空间复杂度：O(1)
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  int i, j;

  for (i = 0; i < numsSize - 1; i++) {
    for (j = i + 1; j < numsSize; j++) {
      if (nums[i] + nums[j] == target) {
        int* p = (int*)malloc(sizeof(int) * 2);
        p[0] = i;
        p[1] = j;
        *returnSize = 2;
        return p;
      }
    }
  }
  return NULL;
}

/*
对于双变量问题，例如两数之和i​+j​=t，可以枚举右边的j​，转换成单变量问题，
也就是在j​左边查找是否有i​=t−j​，这可以用哈希表维护。
把这个技巧叫做枚举右，维护左。
*/
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    unordered_map<int, int> hash;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
      auto it = hash.find(target - nums[i]);
      if (it != hash.end()) {
        return {it->second, i};
      } else {
        hash.insert({nums[i], i});
      }
    }

    return {};
  }
};
