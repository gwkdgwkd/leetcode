/*
一位老师正在出由n道判断题构成的考试，每道题的答案为true（'T'）或者false（'F'）。
老师想增加学生对自己做出答案的不确定性，方法是最大化有连续相同结果的题数。
也就是连续出现true或者连续出现false。
给一个字符串answerKey，其中answerKey[i]是第i个问题的正确结果。
除此以外，还给一个整数k，表示你能进行以下操作的最多次数：
每次操作中，将问题的正确答案改为'T'或者'F'，也就是将answerKey[i]改为'T'或者'F'。
请返回在不超过k次操作的情况下，最大连续'T'或者'F'的数目。

示例1：
输入：answerKey = "TTFF", k = 2
输出：4
解释：可以将两个'F'都变为'T'，得到answerKey = "TTTT"。
     总共有四个连续的'T'。

示例2：
输入：answerKey = "TFFT", k = 1
输出：3
解释：可以将最前面的'T'换成'F'，得到answerKey = "FFFT"。
     或者，可以将第二个'T'换成'F'，得到answerKey = "TFFF"。
     两种情况下，都有三个连续的'F'。

示例3：
输入：answerKey = "TTFTTFTT", k = 1
输出：5
解释：可以将第一个'F'换成'T'，得到answerKey = "TTTTTFTT"。
     或者我们可以将第二个'F'换成'T'，得到answerKey = "TTFTTTTT"。
     两种情况下，都有五个连续的'T'。


提示：
n == answerKey.length
1 <= n <= 5 * 10^4
answerKey[i]要么是'T'，要么是'F'
1 <= k <= n
*/

class Solution {
 public:
  int maxConsecutiveAnswers(string answerKey, int k) {
    int n = answerKey.size();
    auto check = [&](char c) -> int {
      int left = 0;
      int right = 0;
      int ans = 0;
      int cnt = 0;
      while (right < n) {
        if (answerKey[right++] == c) {
          ++cnt;
        }
        while (cnt > k) {
          if (answerKey[left++] == c) {
            --cnt;
          }
        }
        ans = max(ans, right - left);
      }
      return ans;
    };
    int t = check('T');
    int f = check('F');
    return max(t, f);
  }
};

class Solution {
  // 时间复杂度：O(n)，其中n是answerKey的长度。
  // 虽然写了个二重循环，但是内层循环中对left加一的总执行次数不会超过n次，
  // 所以总的时间复杂度为O(n)。
  // 空间复杂度：O(1)。
 public:
  int maxConsecutiveAnswers(string answerKey, int k) {
    int ans = 0, left = 0, cnt[2]{};
    for (int right = 0; right < answerKey.length(); right++) {
      cnt[answerKey[right] >> 1 & 1]++;
      while (cnt[0] > k && cnt[1] > k) {
        cnt[answerKey[left++] >> 1 & 1]--;
      }
      ans = max(ans, right - left + 1);
    }
    return ans;
  }
};
