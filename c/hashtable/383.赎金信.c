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