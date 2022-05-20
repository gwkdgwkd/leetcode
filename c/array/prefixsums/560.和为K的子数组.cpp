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

class Solution {
 public:
  int subarraySum(vector<int> &nums, int k) {
    unordered_map<int, int> hash;
    hash[0] = 1;
    int presum = 0;
    int res = 0;
    for (auto &num : nums) {
      presum += num;
      int diff = presum - k;
      auto it = hash.find(diff);
      if (it != hash.end()) {
        res += it->second;
      }
      it = hash.find(presum);
      if (it != hash.end()) {
        it->second++;
      } else {
        hash[presum] = 1;
      }
    }

    return res;
  }
};