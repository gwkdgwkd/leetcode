/*
给你一个整数数组nums和两个整数k和t。
请你判断是否存在两个不同下标i和j，
使得abs(nums[i] - nums[j]) <= t，同时又满足abs(i - j) <= k。
如果存在则返回true，不存在返回false。

示例1：
输入：nums = [1,2,3,1], k = 3, t = 0
输出：true

示例2：
输入：nums = [1,0,1,1], k = 1, t = 2
输出：true

示例3：
输入：nums = [1,5,9,1,5,9], k = 2, t = 3
输出：false

提示：
0 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^4
0 <= t <= 2^31 - 1
*/

// 剑指OfferII057值和下标之差都在给定的范围内

typedef struct {
  int value;
  int index;
} Data;
int Compare(void *a, void *b) {
  Data *aa = (Data *)a;
  Data *bb = (Data *)b;
  return aa->value > bb->value;
}
bool containsNearbyAlmostDuplicate(int *nums, int numsSize, int k, int t) {
  Data *temp = (Data *)calloc(numsSize, sizeof(Data));
  for (int i = 0; i < numsSize; i++) {
    temp[i].value = nums[i];
    temp[i].index = i;
  }
  qsort(temp, numsSize, sizeof(Data), Compare);

  for (int i = 0; i < numsSize; i++) {
    for (int j = i + 1; j < numsSize; j++) {
      if ((long)temp[j].value - temp[i].value > t) {
        break;
      }
      if (fabs(temp[j].index - temp[i].index) <= k) {
        return true;
      }
    }
  }

  return false;
}