/*
给你两个字符串：ransomNote和magazine，判断ransomNote能不能由magazine里面的字符构成。
如果可以，返回true；否则返回false。
magazine中的每个字符只能在ransomNote中使用一次。

示例1：
输入：ransomNote = "a", magazine = "b"
输出：false

示例2：
输入：ransomNote = "aa", magazine = "ab"
输出：false

示例3：
输入：ransomNote = "aa", magazine = "aab"
输出：true

提示：
1 <= ransomNote.length, magazine.length <= 105
ransomNote和magazine由小写英文字母组成
*/

// 哈希表
bool canConstruct(char* ransomNote, char* magazine) {
  int lenr = strlen(ransomNote);
  int lenm = strlen(magazine);

  int hash[26] = {0};
  for (int i = 0; i < lenm; ++i) {
    hash[magazine[i] - 'a']++;
  }
  for (int i = 0; i < lenr; ++i) {
    hash[ransomNote[i] - 'a']--;
    if (hash[ransomNote[i] - 'a'] < 0) {
      return false;
    }
  }

  return true;
}

// 哈希表
bool canConstruct(char* ransomNote, char* magazine) {
  int lenr = strlen(ransomNote);
  int lenm = strlen(magazine);

  int hash[26] = {0};
  for (int i = 0; i < lenr; ++i) {
    hash[ransomNote[i] - 'a']++;
  }
  for (int i = 0; i < lenm; ++i) {
    if (hash[magazine[i] - 'a'] > 0) {
      hash[magazine[i] - 'a']--;
    }
  }
  for (int i = 0; i < 26; ++i) {
    if (hash[i] != 0) {
      return false;
    }
  }

  return true;
}