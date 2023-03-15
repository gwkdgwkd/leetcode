/*
给定两个以字符串表示的非负整数num1和num2，返回它们的乘积表示的字符串。
注意：不能使用任何内置的BigInteger库或直接将输入转换为整数。

示例1：
输入：num1 = "2", num2 = "3"
输出："6"

示例2：
输入：num1 = "123", num2 = "456"
输出："56088"

提示：
1 <= num1.length, num2.length <= 200
num1和num2只能由数字组成。
num1和num2都不包含任何前导零，除了数字0本身。
*/

char *multiply(char *num1, char *num2) {
  int l1 = strlen(num1);
  int l2 = strlen(num2);
  char *res = (char *)calloc(l1 + l2 + 1, sizeof(char));

  for (int i = l2 - 1; i >= 0; --i) {
    for (int j = l1 - 1; j >= 0; --j) {
      int mul = (num2[i] - '0') * (num1[j] - '0');
      int p1 = i + j;
      int p2 = i + j + 1;
      int sum = (res[p2] == 0 ? 0 : (res[p2] - '0')) + mul;
      if (res[p1]) {
        res[p1] = res[p1] - '0' + sum / 10 + '0';
      } else {
        res[p1] = sum / 10 + '0';
      }
      res[p2] = sum % 10 + '0';
    }
  }
  int index = 0;
  while (res[index]) {
    if (res[index] != '0') {
      break;
    }
    ++index;
  }
  if (strlen(res) == index) {  // 乘积为0
    res[0] = '0';
    res[1] = 0;
  } else {  // 去掉前缀0
    memmove(res, res + index, strlen(res) - index);
    res[strlen(res) - index] = 0;
  }

  return res;
}

// 由于num1和num2的乘积的最大长度为m+n，因此创建长度为m+n的数组ansArr用于存储乘积。
// 对于任意0≤i<m和0≤j<n，num1[i]×num2[j]的结果位于ansArr[i+j+1]，
// 如果ansArr[i+j+1]≥10，则将进位部分加到ansArr[i+j]。
// 最后，将数组ansArr转成字符串，如果最高位是0则舍弃最高位。
class Solution {
 public:
  string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") {
      return "0";
    }
    int m = num1.size(), n = num2.size();
    auto ansArr = vector<int>(m + n);
    for (int i = m - 1; i >= 0; i--) {
      int x = num1[i] - '0';
      for (int j = n - 1; j >= 0; j--) {
        int y = num2[j] - '0';
        ansArr[i + j + 1] += x * y;
      }
    }
    for (int i = m + n - 1; i > 0; i--) {
      ansArr[i - 1] += ansArr[i] / 10;
      ansArr[i] %= 10;
    }
    int index = ansArr[0] == 0 ? 1 : 0;
    string ans;
    while (index < m + n) {
      ans.push_back(ansArr[index] + '0');
      index++;
    }

    return ans;
  }
};