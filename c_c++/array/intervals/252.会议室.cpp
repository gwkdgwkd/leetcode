/*
给定一个会议时间安排的数组，
每个会议时间都会包括开始和结束的时间[[s1,e1],[s2,e2],...](si<ei)，
请你判断一个人是否能够参加这里面的全部会议。

示例1：
输入：[[0,30],[5,10],[15,20]]
输出：false

示例2：
输入：[[7,10],[2,4]]
输出：true
*/

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
  qsort(end, n, sizeof(int), cmp);

  // 扫描过程中的计数器
  int count = 0;
  // 双指针技巧
  int res = 0, i = 0, j = 0;
  while (i < n && j < n) {
    if (begin[i] < end[j]) {
      count++;
      i++;
    } else {
      count--;
      j++;
    }
    // 记录扫描过程中的最大值
    res = fmax(res, count);
  }

  return res;
}

class Solution {
 public:
  bool canAttendMeetings(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(),
         [](auto a, auto b) { return a[0] < b[0]; });
    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i - 1][1] > intervals[i][0]) {
        return false;
      }
    }

    return true;
  }
};