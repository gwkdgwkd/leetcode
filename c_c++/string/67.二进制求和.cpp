/*
给你两个二进制字符串，返回它们的和（用二进制表示）。
输入为非空字符串且只包含数字1和0。

示例1:
输入: a = "11", b = "1"
输出: "100"

示例2:
输入: a = "1010", b = "1011"
输出: "10101"

提示：
每个字符串仅由字符'0'或'1'组成。
1 <= a.length, b.length <= 10^4
字符串如果不是"0"，就都不含前导零。
*/

// 剑指OfferII002二进制加法

char *addBinary(char *a, char *b) {
  int len1 = strlen(a);
  int len2 = strlen(b);

  int len = fmax(len1, len2) + 1;
  char *res = (char *)malloc(sizeof(char) * (len + 1));

  int i = len1 - 1;
  int j = len2 - 1;
  int k = 0;
  int flag = 0;
  while (i >= 0 || j >= 0) {
    int sum = flag;
    if (i >= 0) sum += a[i--] - '0';
    if (j >= 0) sum += b[j--] - '0';
    res[k++] = sum % 2 + '0';
    flag = sum / 2;
  }
  if (flag) res[k++] = '1';
  res[k] = 0;

  for (int l = 0, r = k - 1; l < r; ++l, --r) {
    char tmp = res[l];
    res[l] = res[r];
    res[r] = tmp;
  }

  return res;
}

class Solution {
 public:
  string addBinary(string a, string b) {
    string ans;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int n = max(a.size(), b.size());
    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
      carry += i < a.size() ? (a.at(i) == '1') : 0;
      carry += i < b.size() ? (b.at(i) == '1') : 0;
      ans.push_back((carry % 2) ? '1' : '0');
      carry /= 2;
    }

    if (carry) {
      ans.push_back('1');
    }
    reverse(ans.begin(), ans.end());

    return ans;
  }
};