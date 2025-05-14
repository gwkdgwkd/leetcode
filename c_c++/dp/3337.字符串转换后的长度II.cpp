/*
给一个由小写英文字母组成的字符串s，一个整数t表示要执行的转换次数，
以及一个长度为26的数组nums。每次转换需要根据以下规则替换字符串s中的每个字符：
将s[i]替换为字母表中后续的nums[s[i]-'a']个连续字符。
例如，如果s[i] = 'a'且nums[0] =
3，则字符'a'转换为它后面的3个连续字符，结果为"bcd"。
如果转换超过了'z'，则回绕到字母表的开头。
例如，如果s[i] = 'y'且nums[24] =
3，则字符'y'转换为它后面的3个连续字符，结果为"zab"。
返回恰好执行t次转换后得到的字符串的长度。
由于答案可能非常大，返回其对10^9 + 7取余的结果。

示例1：
输入：s = "abcyy", t = 2, nums =
     [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
输出：7
解释：第一次转换(t = 1) 'a'变为'b'因为nums[0] == 1 'b'变为'c'因为nums[1] == 1
        'c'变为'd'因为nums[2] == 1
        'y'变为'z'因为nums[24] == 1
        'y'变为'z'因为nums[24] == 1
        第一次转换后的字符串为: "bcdzz"
     第二次转换 (t = 2)
        'b'变为'c'因为nums[1] == 1
        'c'变为'd'因为nums[2] == 1
        'd'变为'e'因为nums[3] == 1
        'z'变为'ab'因为nums[25] == 2
        'z'变为'ab'因为nums[25] == 2
        第二次转换后的字符串为: "cdeabab"
     字符串最终长度：字符串为"cdeabab"，长度为7个字符。

示例2：
输入：s = "azbk", t = 1,
     nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
输出：8
解释：第一次转换 (t = 1)
        'a' 变为 'bc' 因为 nums[0] == 2
        'z' 变为 'ab' 因为 nums[25] == 2
        'b' 变为 'cd' 因为 nums[1] == 2
        'k' 变为 'lm' 因为 nums[10] == 2
        第一次转换后的字符串为:"bcabcdlm"
     字符串最终长度：字符串为"bcabcdlm"，长度为8个字符。


提示：
1 <= s.length <= 10^5
s仅由小写英文字母组成。
1 <= t <= 109
nums.length == 26
1 <= nums[i] <= 25
*/

// 矩阵快速幂优化
class Solution {
  static constexpr int MOD = 1'000'000'007;
  static constexpr int SIZE = 26;

  using Matrix = array<array<int, SIZE>, SIZE>;

  // 返回矩阵a和矩阵b相乘的结果
  Matrix mul(Matrix& a, Matrix& b) {
    Matrix c{};
    for (int i = 0; i < SIZE; i++) {
      for (int k = 0; k < SIZE; k++) {
        if (a[i][k] == 0) {
          continue;
        }
        for (int j = 0; j < SIZE; j++) {
          c[i][j] = (c[i][j] + (long long)a[i][k] * b[k][j]) % MOD;
        }
      }
    }
    return c;
  }

  // 返回n个矩阵a相乘的结果
  Matrix pow(Matrix a, int n) {
    Matrix res = {};
    for (int i = 0; i < SIZE; i++) {
      res[i][i] = 1;  // 单位矩阵
    }
    while (n) {
      if (n & 1) {
        res = mul(res, a);
      }
      a = mul(a, a);
      n >>= 1;
    }
    return res;
  }

 public:
  int lengthAfterTransformations(string s, int t, vector<int>& nums) {
    Matrix m{};
    for (int i = 0; i < SIZE; i++) {
      for (int j = i + 1; j <= i + nums[i]; j++) {
        m[i][j % SIZE] = 1;
      }
    }
    Matrix mt = pow(m, t);

    int cnt[SIZE]{};
    for (char c : s) {
      cnt[c - 'a']++;
    }

    long long ans = 0;
    for (int i = 0; i < SIZE; i++) {
      // m第i行的和就是f[t][i]
      ans += reduce(mt[i].begin(), mt[i].end(), 0LL) * cnt[i];
    }
    return ans % MOD;
  }
};