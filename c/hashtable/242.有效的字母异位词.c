// 哈希表
bool isAnagram(char* s, char* t) {
  int lens = strlen(s);
  int lent = strlen(t);

  int hash[26] = {0};
  for (int i = 0; i < lens; ++i) {
    hash[s[i] - 'a']++;
  }
  for (int i = 0; i < lent; ++i) {
    hash[t[i] - 'a']--;
  }
  for (int i = 0; i < 26; ++i) {
    if (hash[i] != 0) {
      return false;
    }
  }

  return true;
}