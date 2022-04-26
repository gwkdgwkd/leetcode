/*
给定一个整数数组和一个整数k，请找到该数组中和为k的连续子数组的个数。

示例1：
输入:nums = [1,1,1], k = 2
输出: 2
解释: 此题[1,1]与[1,1]为两种不同的情况

示例2：
输入:nums = [1,2,3], k = 3
输出: 2

提示:
1 <= nums.length <= 2 * 10^4
-1000 <= nums[i] <= 1000
-10^7 <= k <= 10^7

注意：本题与560题相同
*/

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