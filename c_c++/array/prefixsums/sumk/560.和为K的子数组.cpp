/*
给你一个整数数组nums和一个整数k，请你统计并返回该数组中和为k的子数组的个数。

示例1：
输入：nums = [1,1,1], k = 2
输出：2

示例2：
输入：nums = [1,2,3], k = 3
输出：2

提示：
1 <= nums.length <= 2 * 10^4
-1000 <= nums[i] <= 1000
-10^7 <= k <= 10^7
*/

// 剑指OfferII010和为k的子数组

#include "uthash.h"
// 前缀和+哈希表
typedef struct hashNode {
  int prefixSum;
  int cnt;
  UT_hash_handle hh;
} HashNode;
int subarraySum(int *nums, int numsSize, int k) {
  if (nums == NULL) {
    return 0;
  }

  int retCnt = 0;
  HashNode *hashSet = NULL;
  int prefixSum = 0;
  // 插入初始点(0,0)
  HashNode *tmpNode = (HashNode *)malloc(sizeof(HashNode));
  tmpNode->prefixSum = prefixSum;
  tmpNode->cnt = 1;
  HASH_ADD_INT(hashSet, prefixSum, tmpNode);

  for (int i = 0; i < numsSize; i++) {
    prefixSum += nums[i];
    // 查询是否存在
    int value = prefixSum - k;
    HASH_FIND_INT(hashSet, &value, tmpNode);
    if (tmpNode != NULL) {
      retCnt += tmpNode->cnt;
    }

    // 插入当前的节点
    HASH_FIND_INT(hashSet, &prefixSum, tmpNode);
    if (tmpNode != NULL) {
      tmpNode->cnt++;
    } else {
      tmpNode = (HashNode *)malloc(sizeof(HashNode));
      tmpNode->prefixSum = prefixSum;
      tmpNode->cnt = 1;
      HASH_ADD_INT(hashSet, prefixSum, tmpNode);
    }
  }
  return retCnt;
}

// 暴力法，超时
class Solution {
 public:
  int subarraySum(vector<int> &nums, int k) {
    int len = nums.size();
    int sum = 0;
    int count = 0;
    for (int i = 0; i < len; ++i) {
      for (int j = i; j < len; ++j) {
        sum += nums[j];
        if (sum == k) {
          count++;
        }
      }

      sum = 0;
    }
    return count;
  }
};

// 前缀和，也超时
class Solution {
 public:
  int subarraySum(vector<int> &nums, int k) {
    int n = nums.size();
    vector<int> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i] + nums[i];
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        if (k == pre[j + 1] - pre[i]) {
          ++count;
        }
      }
    }

    return count;
  }
};

// 前缀和+哈希
class Solution {
 public:
  int subarraySum(vector<int> &nums, int k) {
    // 事实上，不需要去计算出具体是哪两项的前缀和之差等于k，
    // 只需要知道等于k的前缀和之差出现的次数count，所以可以在遍历数组过程中，
    // 先去计算以nums[i]结尾的前缀和pre，然后再去判断之前有没有存储pre-k这种前缀和，
    // 如果有，那么pre-k到pre这中间的元素和就是k了。
    unordered_map<int, int> hash;
    hash[0] = 1;

    int pre = 0;
    int count = 0;
    for (int &num : nums) {
      pre += num;
      if (hash.find(pre - k) != hash.end()) {
        count += hash[pre - k];
      }
      hash[pre]++;
    }

    return count;
  }
};