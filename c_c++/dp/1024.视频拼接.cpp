/*
你将会获得一系列视频片段，这些片段来自于一项持续时长为time秒的体育赛事。
这些片段可能有所重叠，也可能长度不一。
使用数组clips描述所有的视频片段，其中clips[i] = [starti, endi]
表示：某个视频片段开始于starti并于endi结束。
甚至可以对这些片段自由地再剪辑：
例如，片段[0, 7] 可以剪切成[0, 1] + [1, 3] + [3, 7]三部分。
我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0,time]）。
返回所需片段的最小数目，如果无法完成该任务，则返回-1。

示例1：
输入：clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
输出：3
解释：
选中[0,2], [8,10], [1,9]这三个片段。
然后，按下面的方案重制比赛片段：
将[1,9]再剪辑为[1,2] + [2,8] + [8,9]。
现在手上的片段为[0,2] + [2,8] + [8,10]，而这些覆盖了整场比赛[0, 10]。

示例2：
输入：clips = [[0,1],[1,2]], time = 5
输出：-1
解释：
无法只用[0,1]和[1,2]覆盖[0,5]的整个过程。

示例3：
输入：clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],
             [1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], time = 9
输出：3
解释：
选取片段[0,4], [4,7]和[6,9]。

提示：
1 <= clips.length <= 100
0 <= starti <= endi <= 100
1 <= time <= 100
*/

// 动态规划，官方题解
int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
  int dp[time + 1];  // dp[i]表示从时间0到i所需要的最少视频
  memset(dp, 0x3f, sizeof(dp));  // 默认为比较大的值
  dp[0] = 0;

  for (int i = 1; i <= time; ++i) {
    for (int j = 0; j < clipsSize; ++j) {
      if (clips[j][0] < i && i <= clips[j][1]) {
        dp[i] = fmin(dp[i], dp[clips[j][0]] + 1);
      }
    }
  }

  return dp[time] == 0x3f3f3f3f ? -1 : dp[time];
}

int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
  int maxn[time + 1];
  memset(maxn, 0, sizeof(maxn));
  for (int i = 0; i < clipsSize; ++i) {
    if (clips[i][0] < time) {
      maxn[clips[i][0]] = fmax(maxn[clips[i][0]], clips[i][1]);
    }
  }

  int ret = 0, last = 0, pre = 0;
  for (int i = 0; i < time; ++i) {
    last = fmax(maxn[i], last);
    if (i == last) {
      return -1;
    }
    if (i == pre) {
      ++ret;
      pre = last;
    }
  }

  return ret;
}

// 贪心算法
// int cmp(const void* a, const void* b) {
//   if (((*(int**)a))[0] == ((*(int**)b))[0]) {
//     return ((*(int**)b))[1] - ((*(int**)a))[1];
//   }
//   return ((*(int**)a))[0] - ((*(int**)b))[0];
// }
int cmp(const void* a, const void* b) {
  if ((*((int**)a))[0] == (*((int**)b))[0]) {
    return (*((int**)b))[1] - (*((int**)a))[1];
  }
  return (*((int**)a))[0] - (*((int**)b))[0];
}
int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
  if (clipsSize == 0 || time == 0) return 0;

  qsort(clips, clipsSize, sizeof(int*), cmp);

  int res = 0;
  int curEnd = 0, nextEnd = 0;
  int i = 0;
  while (i < clipsSize && clips[i][0] <= curEnd) {
    while (i < clipsSize && clips[i][0] <= curEnd) {
      nextEnd = fmax(nextEnd, clips[i][1]);
      i++;
    }
    res++;
    curEnd = nextEnd;
    if (curEnd >= time) {
      return res;
    }
  }
  return -1;
}

class Solution {
 public:
  int videoStitching(vector<vector<int>>& clips, int time) {
    vector<int> dp(time + 1, INT_MAX - 1);
    dp[0] = 0;
    for (int i = 1; i <= time; i++) {
      for (auto& it : clips) {
        if (it[0] < i && i <= it[1]) {
          dp[i] = min(dp[i], dp[it[0]] + 1);
        }
      }
    }
    return dp[time] == INT_MAX - 1 ? -1 : dp[time];
  }
};
