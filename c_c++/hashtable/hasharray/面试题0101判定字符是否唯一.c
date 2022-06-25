/*
实现一个算法，确定一个字符串s的所有字符是否全都不同。

示例1：
输入: s = "leetcode"
输出: false

示例2：
输入: s = "abc"
输出: true

限制：
0 <= len(s) <= 100
如果你不使用额外的数据结构，会很加分。
*/

bool isUnique(char* astr) {
  int len = strlen(astr);

  char hash[256] = {0};

  for (int i = 0; i < len; ++i) {
    if (hash[astr[i]]++ == 1) {
      return false;
    }
  }

  return true;
}

// 位运算，假设字符种类不超过32个
bool isUnique(char* astr) {
  int len = strlen(astr);
  int check = 0;

  for (int i = 0; i < len; ++i) {
    if (check & (1 << (astr[i] - 'a'))) return false;
    check |= (1 << (astr[i] - 'a'));
  }

  return true;
}