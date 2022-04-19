/*
在字符串s中找出第一个只出现一次的字符。
如果没有，返回一个单空格。
s只包含小写字母。

示例1:
输入：s = "abaccdeff"
输出：'b'

示例2:
输入：s = ""
输出：' '

限制：0 <= s 的长度 <= 50000
*/

char firstUniqChar(char* s) {
  int hash[26];
  memset(hash, 0, sizeof(hash));

  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    hash[s[i] - 'a']++;
  }

  for (int i = 0; i < len; ++i) {
    if (hash[s[i] - 'a'] == 1) {
      return s[i];
    }
  }

  return ' ';
}