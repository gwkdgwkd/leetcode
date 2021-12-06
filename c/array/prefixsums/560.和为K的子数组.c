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