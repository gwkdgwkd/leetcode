/*
给一个整数数组nums和两个整数k和t，请判断是否存在两个不同下标i和j，
使得abs(nums[i]-nums[j])<=t，同时又满足abs(i-j)<=k。
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

// 用桶分组
class Solution {
  // 分桶原则：
  // 1.同一个桶中的任两个元素之差的绝对值小于等于t；
  // 2.相邻桶中的某两个元素之差的绝对值可能小于等于t，通过计算判断是否真的小于等于t；
  // 3.不同相邻的桶中的元素之差的绝对值不可能满足小于等于t。
 public:
  long getID(long x, long t) {
    if (x >= 0) {
      // 如果x元素大于等于零,直接分桶：
      return x / (t + 1);  // t可以等于0，所以使用t+1
    } else {
      // 如果x元素小于零,偏移后再分桶：
      return (x + 1) / (t + 1) - 1;
    }
    return 0;
  }
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
    int n = nums.size();
    // 用unordered_map来实现桶，其底层实现是一个哈希表：
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++) {
      long x = nums[i];  // 当前元素
      // 给当前元素生成id：
      int id = getID(x, t);
      // 前面的i-(k+1)是超出了范围的桶，把它提前删除，以免影响判断：
      if (i - (k + 1) >= 0) {
        // 把下标不满足判断范围的桶删除了：
        m.erase(getID(nums[i - (k + 1)], t));
      }
      // 看看当前元素属于的桶中有没有元素：
      if (m.find(id) != m.end()) {
        return true;
      }
      // 看看前面相邻桶有没有符合条件的：
      if (m.find(id - 1) != m.end() && abs(m[id - 1] - x) <= t) {
        return true;
      }
      // 看看后面相邻桶有没有符合条件的：
      if (m.find(id + 1) != m.end() && abs(m[id + 1] - x) <= t) {
        return true;
      }
      // 分桶,把这个元素放入其属于的桶：
      m[id] = x;
    }
    return false;
  }
};

// 滑动窗口 + 有序集合
class Solution {
 public:
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
    int n = nums.size();
    set<int> rec;
    for (int i = 0; i < n; i++) {
      auto iter = rec.lower_bound(max(nums[i], INT_MIN + t) - t);
      if (iter != rec.end() && *iter <= min(nums[i], INT_MAX - t) + t) {
        return true;
      }
      rec.insert(nums[i]);
      if (i >= k) {
        rec.erase(nums[i - k]);
      }
    }
    return false;
  }
};
