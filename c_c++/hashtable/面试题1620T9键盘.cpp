/*
在老式手机上，用户通过数字键盘输入，手机将提供与这些数字相匹配的单词列表。
每个数字映射到0至4个字母，给定一个数字序列，实现一个算法来返回匹配单词的列表。
你会得到一张含有有效单词的列表。

示例1：
输入：num = "8733", words = ["tree", "used"]
输出：["tree", "used"]

示例2：
输入：num = "2", words = ["a", "b", "c", "d"]
输出：["a", "b", "c"]

提示：
num.length <= 1000
words.length <= 500
words[i].length == num.length
num中不会出现0, 1这两个数字
*/

char **getValidT9Words(char *num, char **words, int wordsSize,
                       int *returnSize) {
  int value[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6,
                   6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
  char **res = (char **)malloc(sizeof(char *) * wordsSize);
  *returnSize = 0;
  int flag;
  for (int i = 0; i < wordsSize; i++) {
    flag = 0;
    for (int j = 0; j < strlen(words[i]); j++) {
      if (value[words[i][j] - 'a'] != (int)num[j] - '0') {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      res[*returnSize] = (char *)malloc(sizeof(char) * (strlen(words[i]) + 1));
      strcpy(res[*returnSize], words[i]);
      (*returnSize)++;
    }
  }
  return res;
}

class Solution {
 private:
  int char2num[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6,
                      6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
  bool IsMatch(int *nums, const string &word, int n) {
    for (int i = 0; i < n; ++i) {
      if (char2num[word[i] - 'a'] != nums[i]) {
        return false;
      }
    }
    return true;
  }

 public:
  vector<string> getValidT9Words(string num, vector<string> &words) {
    int n = num.size();
    int *nums = new int[n];
    for (int i = 0; i < n; ++i) {
      nums[i] = num[i] - '0';
    }

    vector<string> res;
    for (const string &word : words) {
      if (word.size() == n) {
        if (IsMatch(nums, word, n)) {
          res.push_back(word);
        }
      }
    }
    return res;
  }
};
