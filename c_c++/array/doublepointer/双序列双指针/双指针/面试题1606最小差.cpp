/*
给定两个整数数组a和b，计算具有最小差绝对值的一对数值（每个数组中取一个值），并返回该对数值的差。

示例：
输入：{1, 3, 15, 11, 2}, {23, 127, 235, 19, 8}
输出：3，即数值对(11, 8)

提示：
1 <= a.length, b.length <= 100000
-2147483648 <= a[i], b[i] <= 2147483647
正确结果在区间[0,2147483647]内
*/

// 二分查找
int comp(const void *i, const void *j) { return (*((int *)i) > (*(int *)j)); }
long long minVal(long long a, long long b, long long c) {
  long long ret = (b < c) ? (c - b) : (b - c);
  return (a < ret) ? a : ret;
}
int smallestDifference(int *a, int aSize, int *b, int bSize) {
  long long min = 4294967295;
  qsort(b, bSize, sizeof(int), comp);

  int i, j;
  for (i = 0; i < aSize; i++) {
    int l = 0;
    int r = bSize - 1;
    int mid;
    while (l < r) {
      mid = (r - l) / 2 + l;
      if (a[i] < b[mid]) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    min = minVal(min, a[i], b[l]);
    if (l - 1 >= 0 && l - 1 < bSize) {
      min = minVal(min, a[i], b[l - 1]);
    }
    if (l + 1 >= 0 && l + 1 < bSize) {
      min = minVal(min, a[i], b[l + 1]);
    }
  }
  return min;
}

// 双指针
class Solution {
 public:
  int smallestDifference(vector<int> &a, vector<int> &b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long res = LONG_MAX;

    int na = a.size();
    int nb = b.size();
    int ia = 0;
    int ib = 0;

    while (ia < na && ib < nb) {
      if (a[ia] == b[ib]) {
        return 0;
      } else {
        res = min(res, abs((long)a[ia] - (long)b[ib]));
        a[ia] > b[ib] ? ++ib : ++ia;
      }
    }

    return res;
  }
};