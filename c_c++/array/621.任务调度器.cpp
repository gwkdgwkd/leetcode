/*
给你一个用字符数组tasks表示的CPU需要执行的任务列表。
其中每个字母表示一种不同种类的任务。
任务可以以任意顺序执行，并且每个任务都可以在1个单位时间内执行完。
在任何一个单位时间，CPU可以完成一个任务，或者处于待命状态。
然而，两个相同种类的任务之间必须有长度为整数n的冷却时间，
因此至少有连续n个单位时间内CPU在执行不同的任务，或者在待命状态。
你需要计算完成所有任务所需要的最短时间。

示例1：
输入：tasks = ["A","A","A","B","B","B"], n = 2
输出：8
解释：A -> B -> (待命) -> A -> B -> (待命) -> A -> B
     在本示例中，两个相同类型任务之间必须间隔长度为n = 2的冷却时间，
     而执行一个任务只需要一个单位时间，所以中间出现了（待命）状态。

示例2：
输入：tasks = ["A","A","A","B","B","B"], n = 0
输出：6
解释：在这种情况下，任何大小为6的排列都可以满足要求，因为n = 0
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
诸如此类

示例3：
输入：tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
输出：16
解释：一种可能的解决方案是：
     A -> B -> C -> A -> D -> E -> A -> F -> G -> A ->
     (待命) -> (待命) -> A -> (待命) -> (待命) -> A

提示：
1 <= task.length <= 10^4
tasks[i]是大写英文字母
n的取值范围为[0, 100]
*/

// 模拟
// 按照时间顺序，依次给每一个时间单位分配任务
int leastInterval(char* tasks, int tasksSize, int n) {
  int freq[26];
  memset(freq, 0, sizeof(freq));
  for (int i = 0; i < tasksSize; ++i) {
    ++freq[tasks[i] - 'A'];
  }

  // 任务总数
  int m = 0;
  int nextValid[26], rest[26];
  for (int i = 0; i < 26; ++i) {
    if (freq[i] > 0) {
      nextValid[m] = 1;
      rest[m++] = freq[i];
    }
  }

  int time = 0;
  for (int i = 0; i < tasksSize; ++i) {
    ++time;
    int minNextValid = INT_MAX;
    for (int j = 0; j < m; ++j) {
      if (rest[j]) {
        minNextValid = fmin(minNextValid, nextValid[j]);
      }
    }
    time = fmax(time, minNextValid);
    int best = -1;
    for (int j = 0; j < m; ++j) {
      if (rest[j] && nextValid[j] <= time) {
        if (best == -1 || rest[j] > rest[best]) {
          best = j;
        }
      }
    }
    nextValid[best] = time + n + 1;
    --rest[best];
  }

  return time;
}

class Solution {
 public:
  int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char ch : tasks) {
      ++freq[ch];
    }

    // 任务总数
    int m = freq.size();
    vector<int> nextValid, rest;
    for (auto [_, v] : freq) {
      nextValid.push_back(1);
      rest.push_back(v);
    }

    int time = 0;
    for (int i = 0; i < tasks.size(); ++i) {
      ++time;
      int minNextValid = INT_MAX;
      for (int j = 0; j < m; ++j) {
        if (rest[j]) {
          minNextValid = min(minNextValid, nextValid[j]);
        }
      }
      time = max(time, minNextValid);
      int best = -1;
      for (int j = 0; j < m; ++j) {
        if (rest[j] && nextValid[j] <= time) {
          if (best == -1 || rest[j] > rest[best]) {
            best = j;
          }
        }
      }
      nextValid[best] = time + n + 1;
      --rest[best];
    }

    return time;
  }
};

// 构造
int leastInterval(char* tasks, int tasksSize, int n) {
  int freq[26];
  memset(freq, 0, sizeof(freq));
  for (int i = 0; i < tasksSize; ++i) {
    ++freq[tasks[i] - 'A'];
  }

  // 最多的执行次数，数组任务出现的最多次数
  int maxExec = 0;
  for (int i = 0; i < 26; i++) {
    maxExec = fmax(maxExec, freq[i]);
  }
  // 出现最多次数的任务个数
  int maxCount = 0;
  for (int i = 0; i < 26; i++) {
    if (maxExec == freq[i]) {
      maxCount++;
    }
  }

  return fmax((maxExec - 1) * (n + 1) + maxCount, tasksSize);
}

class Solution {
 public:
  int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char ch : tasks) {
      ++freq[ch];
    }

    // 最多的执行次数
    int maxExec =
        max_element(freq.begin(), freq.end(), [](const auto& u, const auto& v) {
          return u.second < v.second;
        })->second;
    // 具有最多执行次数的任务数量
    int maxCount = accumulate(
        freq.begin(), freq.end(), 0,
        [=](int acc, const auto& u) { return acc + (u.second == maxExec); });

    return max((maxExec - 1) * (n + 1) + maxCount,
               static_cast<int>(tasks.size()));
  }
};
