/*
给你一个字符串数组words，找出并返回length(words[i])*length(words[j])的最大值，
并且这两个单词不含有公共字母。
如果不存在这样的两个单词，返回0。

示例1：
输入：words = ["abcw","baz","foo","bar","xtfn","abcdef"]
输出：16
解释：这两个单词为"abcw","xtfn"。

示例2：
输入：words = ["a","ab","abc","d","cd","bcd","abcd"]
输出：4
解释：这两个单词为 "ab", "cd"。

示例3：
输入：words = ["a","aa","aaa","aaaa"]
输出：0
解释：不存在这样的两个单词。

提示：
2 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i]仅包含小写字母
*/

// 剑指OfferII005单词长度的最大乘积

int str2int(char *str) {
  int res = 0;
  int size = strlen(str);
  for (int i = 0; i < size; i++) {
    res |= 1 << (str[i] - 'a');
  }
  return res;
}
int maxProduct(char **words, int wordsSize) {
  if (words == NULL || wordsSize < 1) {
    return 0;
  }
  int *ptr = (int *)malloc(sizeof(int) * wordsSize);
  for (int i = 0; i < wordsSize; i++) {
    ptr[i] = str2int(words[i]);
  }
  int res = 0;
  for (int i = 1; i < wordsSize; i++) {
    for (int j = 0; j < i; j++) {
      if ((ptr[i] & ptr[j]) == 0 &&
          (strlen(words[i]) * strlen(words[j])) > res) {
        res = strlen(words[i]) * strlen(words[j]);
      }
    }
  }
  return res;
}