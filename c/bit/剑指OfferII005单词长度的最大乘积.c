/*
给定一个字符串数组words，请计算当两个字符串words[i]和words[j]不包含相同字符时，它们长度的乘积的最大值。
假设字符串中只包含英语的小写字母。
如果没有不包含相同字符的一对字符串，返回0。

示例1:
输入: words = ["abcw","baz","foo","bar","fxyz","abcdef"]
输出: 16 
解释: 这两个单词为"abcw","fxyz"。它们不包含相同字符，且长度的乘积最大。

示例2:
输入: words = ["a","ab","abc","d","cd","bcd","abcd"]
输出: 4 
解释: 这两个单词为 "ab", "cd"。

示例3:
输入: words = ["a","aa","aaa","aaaa"]
输出: 0 
解释: 不存在这样的两个单词。

提示：
2 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i]仅包含小写字母

注意：本题与318题相同
*/

int str2int(char *s) {
  int len = strlen(s);
  int res = 0;
  for (int i = 0; i < len; ++i) {
    res |= 1 << (s[i] - 'a');
  }

  return res;
}
int maxProduct(char **words, int wordsSize) {
  if (words == NULL || wordsSize < 1) {
    return 0;
  }
  int *nums = (int *)malloc(sizeof(int) * wordsSize);
  for (int i = 0; i < wordsSize; ++i) {
    nums[i] = str2int(words[i]);
  }

  int max = 0;
  for (int i = 1; i < wordsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      int tmp = strlen(words[i]) * strlen(words[j]);
      if ((nums[i] & nums[j]) == 0 && tmp > max) {
        max = tmp;
      }
    }
  }
  return max;
}