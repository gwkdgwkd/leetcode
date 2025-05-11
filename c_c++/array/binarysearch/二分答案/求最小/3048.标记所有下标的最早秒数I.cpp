/*
给两个下标从1开始的整数数组nums和changeIndices，数组的长度分别为n和m。
一开始，nums中所有下标都是未标记的，标记nums中所有下标。
从第1秒到第m秒（包括第m秒），对于每一秒s，可以执行以下操作之一：
选择范围[1, n]中的一个下标i，并且将nums[i]减少1。
如果nums[changeIndices[s]]等于0，标记下标changeIndices[s]。
什么也不做。
请返回范围[1, m]中的一个整数，表示最优操作下，标记nums中所有下标的最早秒数 ，
如果无法标记所有下标，返回-1。

示例1：
输入：nums = [2,2,0], changeIndices = [2,2,2,2,3,2,2,1]
输出：8
解释：这个例子中，我们总共有8秒。按照以下操作标记所有下标：
     第1秒：选择下标1，将nums[1]减少1。nums变为[1,2,0]。
     第2秒：选择下标1，将nums[1]减少1。nums变为[0,2,0]。
     第3秒：选择下标2，将nums[2]减少1。nums变为[0,1,0]。
     第4秒：选择下标2，将nums[2]减少1。nums变为[0,0,0]。
     第5秒，标​​​​​记changeIndices[5]，也就是标记下标3，因为nums[3]等于0。
     第6秒，标​​​​​记changeIndices[6]，也就是标记下标2，因为nums[2]等于0。
     第7秒，什么也不做。
     第8秒，标记changeIndices[8]，也就是标记下标1，因为nums[1]等于0。
     现在所有下标已被标记。
     最早可以在第8秒标记所有下标。
     所以答案是8。

示例2：
输入：nums = [1,3], changeIndices = [1,1,1,2,1,1,1]
输出：6
解释：这个例子中，我们总共有 7 秒。按照以下操作标记所有下标：
     第1秒：选择下标2，将nums[2]减少1。nums变为[1,2]。
     第2秒：选择下标2，将nums[2]减少1。nums变为[1,1]。
     第3秒：选择下标2，将nums[2]减少1。nums变为[1,0]。
     第4秒：标​​​​​记changeIndices[4]，也就是标记下标2，因为nums[2]等于0。
     第5秒：选择下标1，将nums[1]减少1。nums变为[0,0]。
     第6秒：标​​​​​记changeIndices[6]，也就是标记下标1，因为nums[1]等于0。
     现在所有下标已被标记。
     最早可以在第6秒标记所有下标。
     所以答案是6。

示例3：
输入：nums = [0,1], changeIndices = [2,2,2]
输出：-1
解释：这个例子中，无法标记所有下标，因为下标1不在changeIndices中。
     所以答案是-1。


提示：
1 <= n == nums.length <= 2000
0 <= nums[i] <= 10^9
1 <= m == changeIndices.length <= 2000
1 <= changeIndices[i] <= n
*/

/*
题意有点抽象，形象地解释一下：
有n门课程需要考试，第i门课程需要用nums[i]天复习。同一天只能复习一门课程。
在第i天，你可以选择参加第changeIndices[i]门课程的考试。考试这一天不能复习。
搞定所有课程的复习+考试，至少要多少天？
*/

// 二分答案+正向遍历
class Solution {
 public:
  int earliestSecondToMarkIndices(vector<int> &nums,
                                  vector<int> &changeIndices) {
    int n = nums.size(), m = changeIndices.size();
    if (n > m) return -1;

    vector<int> last_t(n);
    auto check = [&](int mx) -> bool {
      ranges::fill(last_t, -1);
      for (int t = 0; t < mx; t++) {
        last_t[changeIndices[t] - 1] = t;
      }
      if (ranges::find(last_t, -1) != last_t.end()) {  // 有课程没有考试时间
        return false;
      }

      int cnt = 0;
      for (int i = 0; i < mx; i++) {
        int idx = changeIndices[i] - 1;
        if (i == last_t[idx]) {   // 考试
          if (nums[idx] > cnt) {  // 没时间复习
            return false;
          }
          cnt -= nums[idx];  // 复习这门课程
        } else {
          cnt++;  // 留着后面用
        }
      }
      return true;
    };

    int left = n - 1, right = m + 1;
    while (left + 1 < right) {
      int mid = (left + right) / 2;
      (check(mid) ? right : left) = mid;
    }
    return right > m ? -1 : right;
  }
};

// 二分答案+逆向遍历
class Solution {
 public:
  int earliestSecondToMarkIndices(vector<int> &nums,
                                  vector<int> &changeIndices) {
    int n = nums.size(), m = changeIndices.size();
    if (n > m) return -1;

    vector<int> done(n);  // 避免反复创建和初始化数组
    auto check = [&](int mx) -> bool {
      int exam = n, study = 0;
      for (int i = mx - 1; i >= 0 && study <= i + 1;
           i--) {  // 要复习的天数不能太多
        int idx = changeIndices[i] - 1;
        if (done[idx] != mx) {
          done[idx] = mx;
          exam--;              // 考试
          study += nums[idx];  // 需要复习的天数
        } else if (study) {
          study--;  // 复习
        }
      }
      return exam == 0 && study == 0;  // 考完了并且复习完了
    };

    int left = n - 1, right = m + 1;
    while (left + 1 < right) {
      int mid = (left + right) / 2;
      (check(mid) ? right : left) = mid;
    }
    return right > m ? -1 : right;
  }
};