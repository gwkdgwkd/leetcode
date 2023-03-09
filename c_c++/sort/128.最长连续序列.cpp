/*
给定一个未排序的整数数组nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
请设计并实现时间复杂度为O(n)的算法解决此问题。

示例1：
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是[1, 2, 3, 4]。它的长度为4。

示例2：
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9

提示：
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
*/

// 剑指OfferII119最长连续序列

// 排序，比O(n)复杂度高
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
int longestConsecutive(int *nums, int numsSize) {
  if (!numsSize) {
    return 0;
  }
  qsort(nums, numsSize, sizeof(int), cmp);
  int max = 1;
  int temp = 1;
  for (int i = 1; i < numsSize; ++i) {
    if (nums[i] == nums[i - 1] + 1) {
      ++temp;
    } else if (nums[i] == nums[i - 1]) {
      continue;
    } else {
      temp = 1;
    }
    max = max > temp ? max : temp;
  }
  return max;
}

// 哈希表 + 并查集
// 是O(n)吗？比排序还慢
typedef struct a {
  int val;
  int idx;
  UT_hash_handle hh;
} Node;
Node *g_map;
int *g_set;
int *MakeSet(int n) {
  int *set = calloc(n, sizeof(int));
  for (int i = 0; i < n; i++) {
    set[i] = i;
  }
  return set;
}
int *MakeHash(int *nums, int numsSize, int *returnSize) {
  Node *s = NULL;
  int *newNums = calloc(numsSize, sizeof(int));
  int cnt = 0;
  for (int i = 0; i < numsSize; i++) {
    HASH_FIND_INT(g_map, &nums[i], s);
    if (s == NULL) {
      // 去掉原数组中重复项，如果已经在hash表中，则不再保存
      newNums[cnt++] = nums[i];
      s = calloc(1, sizeof(Node));
      s->val = nums[i];
      s->idx = cnt - 1;  // 保存新数组newNums中的索引
      HASH_ADD_INT(g_map, val, s);
    }
  }
  *returnSize = cnt;
  return newNums;
}
int Find(int a) {
  int m = a;
  while (g_set[m] != m) {
    g_set[m] = g_set[g_set[m]];
    m = g_set[m];
  }
  return m;
}
void Merge(int a, int b) { g_set[Find(a)] = Find(b); }
int longestConsecutive(int *nums, int numsSize) {
  if ((nums == NULL) || (numsSize == 0)) {
    return 0;
  }
  g_map = NULL;
  int cnt = 0;
  int *newNums = MakeHash(nums, numsSize, &cnt);
  g_set = MakeSet(cnt);
  Node *s = NULL;
  for (int i = 0; i < cnt; i++) {
    int tmp;
    if (newNums[i] > INT_MIN) {  // 每个数，查找hash表中是否存在前一项
      tmp = newNums[i] - 1;
      HASH_FIND_INT(g_map, &tmp, s);
      if (s != NULL) {
        Merge(s->idx, i);
      }
    }
    if (newNums[i] < INT_MAX) {  // 每个数，查找hash表中是否存在后一项
      tmp = newNums[i] + 1;
      HASH_FIND_INT(g_map, &tmp, s);
      if (s != NULL) {
        Merge(s->idx, i);
      }
    }
  }
  int *count = calloc(cnt, sizeof(int));
  // 统计最终有多少个集合，每个集合有多少个元素
  for (int j = 0; j < cnt; j++) {
    count[Find(j)]++;
  }
  int max = 0;
  for (int k = 0; k < cnt; k++) {  // 找到最大集合的元素个数就是解
    if (count[k] > max) {
      max = count[k];
    }
  }
  Node *tmp;
  HASH_ITER(hh, g_map, s, tmp) {
    HASH_DEL(g_map, s);
    free(s);
  }
  free(newNums);
  return max;
}

class Solution {
 public:
  int longestConsecutive(vector<int> &nums) {
    unordered_set<int> num_set(nums.begin(), nums.end());
    int longestStreak = 0;

    for (const int &num : num_set) {
      if (!num_set.count(num - 1)) {
        int currentNum = num;
        int currentStreak = 1;

        while (num_set.count(currentNum + 1)) {
          currentNum += 1;
          currentStreak += 1;
        }

        longestStreak = max(longestStreak, currentStreak);
      }
    }

    return longestStreak;
  }
};