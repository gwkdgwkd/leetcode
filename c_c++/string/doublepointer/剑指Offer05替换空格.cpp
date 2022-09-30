/*
请实现一个函数，把字符串s中的每个空格替换成"%20"。

示例1：
输入：s = "We are happy."
输出："We%20are%20happy."

限制：0 <= s的长度 <= 10000
*/

char* replaceSpace(char* s) {
  int count = 0;
  int len = strlen(s);

  for (int i = 0; i < len; ++i) {
    if (s[i] == ' ') {
      ++count;
    }
  }

  int newlen = len + 2 * count;
  char* res = (char*)malloc(sizeof(char) * (newlen + 1));
  res[newlen] = 0;

  int slow = len - 1;
  int fast = newlen - 1;
  while (slow >= 0) {
    if (s[slow] == ' ') {
      res[fast--] = '0';
      res[fast--] = '2';
      res[fast--] = '%';
      slow--;
    } else {
      res[fast--] = s[slow--];
    }
  }

  // int index = 0;
  // for (int i = 0; i < len; ++i) {
  //   if (s[i] == ' ') {
  //     memcpy(res + index, "%20", sizeof(char) * 3);
  //     index += 3;
  //   } else {
  //     res[index++] = s[i];
  //   }
  // }

  return res;
}

// 面试题0103URL化
// URL化。编写一种方法，将字符串中的空格全部替换为%20。
// 假定该字符串尾部有足够的空间存放新增字符，并且知道字符串的真实长度。
char* replaceSpaces(char* S, int length) {
  int count = 0;
  for (int i = 0; i < length; ++i) {
    if (S[i] == ' ') {
      ++count;
    }
  }

  int right = length + 2 * count;
  S[right--] = 0;
  int left = length - 1;
  while (left >= 0) {
    if (S[left] == ' ') {
      S[right--] = '0';
      S[right--] = '2';
      S[right--] = '%';
      --left;
    } else {
      S[right--] = S[left--];
    }
  }

  return S;
}

class Solution {
 public:
  string replaceSpace(string s) {
    string ans;
    for (const auto& c : s) {
      if (c == ' ') {
        ans.push_back('%');
        ans.push_back('2');
        ans.push_back('0');
      } else {
        ans.push_back(c);
      }
    }

    return ans;
  }
};
