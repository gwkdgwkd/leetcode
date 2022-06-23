/*
有个内含单词的超大文本文件，给定任意两个不同的单词，
找出在这个文件中这两个单词的最短距离(相隔单词数)。
如果寻找过程在这个文件中会重复多次，而每次寻找的单词不同，你能对此优化吗?

示例：
输入：words = ["I","am","a","student","from","a","university",
              "in","a","city"], word1 = "a", word2 = "student"
输出：1

提示：words.length <= 100000
*/

int findClosest(char** words, int wordsSize, char* word1, char* word2) {
  int p1, p2, res = INT_MAX;
  p1 = p2 = -1;
  for (int i = 0; i < wordsSize; ++i) {
    char* word = words[i];
    if (strcmp(word, word1) == 0) {
      p1 = i;
    }
    if (strcmp(word, word2) == 0) {
      p2 = i;
    }
    if (p1 != -1 && p2 != -1) {
      res = fmin(res, abs(p1 - p2));
    }
  }
  return res;
}
