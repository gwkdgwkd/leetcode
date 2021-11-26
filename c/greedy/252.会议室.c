// 求最多有几个重叠区间

// 基于差分数组的思路
void cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }
int minMeetingRooms(int** meetings, int meetingsSize, int* meetingsColSize) {
  int n = meetingsSize;
  int begin[n];
  int end[n];
  for (int i = 0; i < n; i++) {
    begin[i] = meetings[i][0];
    end[i] = meetings[i][1];
  }
  qsort(begin, n, sizeof(int), cmp);
  qsort(begin, n, sizeof(int), cmp);

  // 扫描过程中的计数器
  int count = 0;
  // 双指针技巧
  int res = 0, i = 0, j = 0;
  while (i < n && j < n) {
    if (begin[i] < end[j]) {  // 扫描到一个红点
      count++;
      i++;
    } else {  // 扫描到一个绿点
      count--;
      j++;
    }
    // 记录扫描过程中的最大值
    res = fmax(res, count);
  }

  return res;
}