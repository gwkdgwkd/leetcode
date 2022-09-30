/*
给你一个整数n，找出从1到n各个整数的Fizz Buzz表示，
并用字符串数组answer（下标从1开始）返回结果，其中：
answer[i] == "FizzBuzz" 如果i同时是3和5的倍数。
answer[i] == "Fizz" 如果i是3的倍数。
answer[i] == "Buzz" 如果i是5的倍数。
answer[i] == i （以字符串形式）如果上述条件全不满足。

示例1：
输入：n = 3
输出：["1","2","Fizz"]

示例2：
输入：n = 5
输出：["1","2","Fizz","4","Buzz"]

示例 3：
输入：n = 15
输出：["1","2","Fizz","4","Buzz","Fizz","7","8","Fizz",
      "Buzz","11","Fizz","13","14","FizzBuzz"]

提示：1 <= n <= 10^4
*/

char *g_35 = "FizzBuzz";
char *g_3 = "Fizz";
char *g_5 = "Buzz";
char **fizzBuzz(int n, int *returnSize) {
  char **result = (char **)malloc(sizeof(char *) * n);
  for (int i = 1; i <= n; i++) {
    if (i % 3 == 0 && i % 5 == 0) {
      result[i - 1] = g_35;
    } else if (i % 3 == 0) {
      result[i - 1] = g_3;
    } else if (i % 5 == 0) {
      result[i - 1] = g_5;
    } else {
      result[i - 1] = (char *)malloc(sizeof(char) * 8);
      sprintf(result[i - 1], "%d", i);
    }
  }
  *returnSize = n;
  return result;
}

class Solution {
 public:
  vector<string> fizzBuzz(int n) {
    vector<string> answer;
    for (int i = 1; i <= n; i++) {
      string curr;
      if (i % 3 == 0) {
        curr　+= "Fizz";
      }
      if (i % 5 == 0) {
        curr += "Buzz";
      }
      if (curr.size() == 0) {
        curr += to_string(i);
      }
      answer.emplace_back(curr);
    }
    return answer;
  }
};