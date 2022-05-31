/*
给定一个仅包含数字2-9的字符串，返回所有它能表示的字母组合。
答案可以按任意顺序返回。
给出数字到字母的映射如下（与电话按键相同）。注意1不对应任何字母。

示例1：
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]

示例2：
输入：digits = ""
输出：[]

示例3：
输入：digits = "2"
输出：["a","b","c"]

提示：
0 <= digits.length <= 4
digits[i]是范围['2', '9']的一个数字。
*/

// 回溯算法
char *map[10] = {
    "",      // 0
    "",      // 1
    "abc",   // 2
    "def",   // 3
    "ghi",   // 4
    "jkl",   // 5
    "mno",   // 6
    "pqrs",  // 7
    "tuv",   // 8
    "wxyz",  // 9
};
char **result;
int resultSize;
char *path;
int pathSize;
void backtracking(char *digits, int index) {
  if (pathSize == strlen(digits)) {
    result[resultSize] = (char *)malloc(sizeof(char) * pathSize + 1);
    for (int i = 0; i < pathSize; ++i) {
      result[resultSize][i] = path[i];
    }
    result[resultSize][pathSize] = 0;
    resultSize++;

    return;
  }

  int len = strlen(map[digits[index] - '0']);
  for (int i = 0; i < len; ++i) {
    path[pathSize++] = map[digits[index] - '0'][i];
    // printf("%*c\n", pathSize * 2, map[digits[index] - '0'][i]);
    backtracking(digits, index + 1);
    pathSize--;
  }

  return;
}
char **letterCombinations(char *digits, int *returnSize) {
  int len = strlen(digits);
  if (0 == len) {
    *returnSize = 0;
    return NULL;
  }
  int max = 1;
  for (int i = 0; i < len; ++i) {
    max *= 4;
  }
  result = (char **)malloc(sizeof(char *) * max);
  path = (char *)malloc(sizeof(char) * len);
  resultSize = pathSize = 0;
  backtracking(digits, 0);
  *returnSize = resultSize;
  return result;
}

class Solution {
  vector<string> m;
  vector<string> ans;
  string path;

 public:
  void backtracking(string digits, int index) {
    if (path.size() == digits.size()) {
      ans.emplace_back(path);
      return;
    }
    int len = m[digits[index] - '0'].size();
    for (int i = 0; i < len; ++i) {
      path.push_back(m[digits[index] - '0'][i]);
      backtracking(digits, index + 1);
      path.pop_back();
    }
  }
  vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return ans;
    m.assign({
        "",      // 0
        "",      // 1
        "abc",   // 2
        "def",   // 3
        "ghi",   // 4
        "jkl",   // 5
        "mno",   // 6
        "pqrs",  // 7
        "tuv",   // 8
        "wxyz",  // 9
    });
    backtracking(digits, 0);
    return ans;
  }
};