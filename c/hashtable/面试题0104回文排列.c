/*
给定一个字符串，编写一个函数判定其是否为某个回文串的排列之一。
回文串是指正反两个方向都一样的单词或短语。排列是指字母的重新排列。
回文串不一定是字典当中的单词。

示例1：
输入："tactcoa"
输出：true（排列有"tacocat"、"atcocta"，等等）
*/

bool canPermutePalindrome(char* s) {
  int hash[128] = {0};
  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    hash[s[i]]++;
  }

  int count = 0;
  for (int i = 0; i < 128; ++i) {
    if (hash[i] % 2) {
      ++count;
    }
  }

  return count < 2;
}