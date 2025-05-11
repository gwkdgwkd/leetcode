/*
给一个字符串num。
如果一个数字字符串的奇数位下标的数字之和与偶数位下标的数字之和相等，
那么我们称这个数字字符串是平衡的。
请返回num不同排列中，平衡字符串的数目。
由于答案可能很大，请你将答案对10^9 + 7取余后返回。
一个字符串的排列指的是将字符串中的字符打乱顺序后连接得到的字符串。

示例1：
输入：num = "123"
输出：2
解释：num的不同排列包括："123"，"132"，"213"，"231"，"312"和"321"。
     它们之中，"132"和"231"是平衡的。所以答案为2。

示例2：
输入：num = "112"
输出：1
解释：num的不同排列包括："112"，"121"和"211"。
     只有"121"是平衡的。所以答案为1。

示例3：
输入：num = "12345"
输出：0
解释：num的所有排列都是不平衡的。所以答案为0。


提示：
2 <= num.length <= 80
num中的字符只包含数字'0'到'9'。
*/

class Solution {
 public:
  constexpr static long long MOD = 1e9 + 7;

  int countBalancedPermutations(string num) {
    int tot = 0, n = num.size();
    vector<int> cnt(10);
    for (char ch : num) {
      int d = ch - '0';
      cnt[d]++;
      tot += d;
    }
    if (tot % 2 != 0) {
      return 0;
    }

    int target = tot / 2;
    int maxOdd = (n + 1) / 2;
    vector<vector<long long>> comb(maxOdd + 1, vector<long long>(maxOdd + 1));
    vector<vector<long long>> f(target + 1, vector<long long>(maxOdd + 1));
    for (int i = 0; i <= maxOdd; i++) {
      comb[i][i] = comb[i][0] = 1;
      for (int j = 1; j < i; j++) {
        comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
      }
    }

    f[0][0] = 1;
    int psum = 0, totSum = 0;
    for (int i = 0; i <= 9; i++) {
      // 前i个数字的数目之和
      psum += cnt[i];
      // 前i个数字的元素之和
      totSum += i * cnt[i];
      for (int oddCnt = min(psum, maxOdd);
           oddCnt >= max(0, psum - (n - maxOdd)); oddCnt--) {
        // 偶数位需要填充的位数
        int evenCnt = psum - oddCnt;
        for (int curr = min(totSum, target); curr >= max(0, totSum - target);
             curr--) {
          long long res = 0;
          for (int j = max(0, cnt[i] - evenCnt);
               j <= min(cnt[i], oddCnt) && i * j <= curr; j++) {
            /* 当前数字在奇数位填充 j 位，偶数位填充 cnt[i] - j 位 */
            long long ways = comb[oddCnt][j] * comb[evenCnt][cnt[i] - j] % MOD;
            res = (res + ways * f[curr - i * j][oddCnt - j] % MOD) % MOD;
          }
          f[curr][oddCnt] = res % MOD;
        }
      }
    }

    return f[target][maxOdd];
  }
};
