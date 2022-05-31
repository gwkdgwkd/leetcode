/*
给你一个字符串数组words，请你找出所有在words的每个字符串中都出现的共用字符（包括重复字符），并以数组形式返回。
你可以按任意顺序返回答案。

示例1：
输入：words = ["bella","label","roller"]
输出：["e","l","l"]

示例2：
输入：words = ["cool","lock","cook"]
输出：["c","o"]

提示：
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i]由小写英文字母组成
*/

// 哈希表
char** commonChars(char** words, int wordsSize, int* returnSize) {
  int minfreq[26], freq[26];
  for (int i = 0; i < 26; ++i) {
    minfreq[i] = INT_MAX;
    freq[i] = 0;
  }
  for (int i = 0; i < wordsSize; ++i) {
    memset(freq, 0, sizeof(freq));
    int n = strlen(words[i]);
    for (int j = 0; j < n; ++j) {
      ++freq[words[i][j] - 'a'];
    }
    for (int j = 0; j < 26; ++j) {
      minfreq[j] = fmin(minfreq[j], freq[j]);
    }
  }

  int sum = 0;
  for (int i = 0; i < 26; ++i) {
    sum += minfreq[i];
  }

  char** ans = malloc(sizeof(char*) * sum);
  *returnSize = 0;
  for (int i = 0; i < 26; ++i) {
    for (int j = 0; j < minfreq[i]; ++j) {
      ans[*returnSize] = calloc(2, sizeof(char));
      ans[(*returnSize)++][0] = i + 'a';
    }
  }
  return ans;
}

char** commonChars(char** words, int wordsSize, int* returnSize) {
  int hash1[26] = {0};
  int hash2[26] = {0};
  for (int i = 0; i < strlen(words[0]); ++i) {
    hash1[words[0][i] - 'a']++;
  }

  for (int i = 1; i < wordsSize; ++i) {
    memset(hash2, 0, sizeof(hash2));
    for (int j = 0; j < strlen(words[i]); ++j) {
      hash2[words[i][j] - 'a']++;
    }

    for (int j = 0; j < 26; ++j) {
      hash1[j] = fmin(hash1[j], hash2[j]);
    }
  }

  int count = 0;
  for (int j = 0; j < 26; ++j) {
    count += hash1[j];
  }

  char** res = (char**)malloc(sizeof(char*) * count);
  for (int i = 0; i < count; ++i) {
    res[i] = (char*)calloc(2, sizeof(char));
  }

  *returnSize = 0;
  for (int j = 0; j < 26; ++j) {
    while (hash1[j]--) {
      res[(*returnSize)++][0] = j + 'a';
    }
  }

  return res;
}