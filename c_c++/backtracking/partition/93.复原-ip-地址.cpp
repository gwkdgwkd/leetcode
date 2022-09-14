/*
有效IP地址正好由四个整数，每个整数位于0到255之间组成，
且不能含有前导0，整数之间用'.'分隔。
例如："0.1.2.201"和"192.168.1.1"是有效IP地址，
但是"0.011.255.245"、"192.168.1.312"和"192.168@1.1"是无效IP地址。
给定一个只包含数字的字符串s，用以表示一个IP地址，返回所有可能的有效IP地址，
这些地址可以通过在s中插入'.'来形成。
你不能重新排序或删除s中的任何数字。你可以按任何顺序返回答案。

示例1：
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]

示例2：
输入：s = "0000"
输出：["0.0.0.0"]

示例3：
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

提示：
1 <= s.length <= 20
s 仅由数字组成
*/

// 剑指OfferII087复原IP

char **result;
int resultSize;
char *path;
int pathIndex;
int pathSize;
int isValid(const char *str, int start, int end) {
  if (end < start) {
    return 0;
  }
  if (str[start] == '0' && start != end) {
    return 0;
  }

  int num = 0;
  for (int i = start; i <= end; i++) {
    if (str[i] > '9' || str[i] < '0') {  // 遇到⾮数字字符不合法
      return 0;
    }
    num = num * 10 + (str[i] - '0');
    if (num > 255) {  // 如果⼤于255了不合法
      return 0;
    }
  }

  return 1;
}
void backtracking(char *s, int len, int startIndex) {
  if (pathSize == 3) {
    if (isValid(s, startIndex, len - 1)) {
      // printf("%s[%d %d]\n",path,startIndex,strlen(path));
      result[resultSize] = (char *)malloc(sizeof(char) * 16);
      strcpy(result[resultSize], path);
      // printf("%s\n",result[resultSize]);
      strcpy(result[resultSize] + strlen(path), s + startIndex);
      // printf("%s\n",result[resultSize]);
      resultSize++;
    }
    return;
  }

  int tmp = pathIndex;
  for (int i = startIndex; i < len; ++i) {
    if (isValid(s, startIndex, i)) {
      memcpy(path + pathIndex, s + startIndex, i - startIndex + 1);
      pathIndex += i - startIndex + 1;
      path[pathIndex++] = '.';
      path[pathIndex] = 0;
      // printf("%s\n",path);
      pathSize++;
      backtracking(s, len, i + 1);
      pathSize--;
      pathIndex = tmp;
    } else {
      break;
    }
  }

  // "25525511135"
  // 2.
  // 2.5.
  // 2.5.5.
  // 2.5.52.
  // 2.55.
  // 2.55.2.
  // 2.55.25.
  // 2.55.255.
  // 25.
  // 25.5.
  // 25.5.2.
  // 25.5.25.
  // 25.5.255.
  // 25.52.
  // 25.52.5.
  // 25.52.55.
  // 255.
  // 255.2.
  // 255.2.5.
  // 255.2.55.
  // 255.25.
  // 255.25.5.
  // 255.25.51.
  // 255.255.
  // 255.255.1.
  // 255.255.11.
  // 255.255.11.135
  // 255.255.111.
  // 255.255.111.35

  return;
}
char **restoreIpAddresses(char *s, int *returnSize) {
  int len = strlen(s);
  if (len > 12) {
    *returnSize = 0;
    return NULL;
  }
  int maxResultSize = len * (1 << len);
  // printf("%d %d\n", len, maxResultSize);
  result = (char **)malloc(sizeof(char *) * maxResultSize);
  path = (char *)malloc(sizeof(char) * 16);
  resultSize = pathSize = pathIndex = 0;
  backtracking(s, len, 0);
  *returnSize = resultSize;
  return result;
}

class Solution {
  vector<string> ans;
  string path;
  int pathSize;

 public:
  bool isValid(string str, int start, int end) {
    if (end < start) {
      return false;
    }
    if (str[start] == '0' && start != end) {
      return false;
    }

    int num = 0;
    for (int i = start; i <= end; i++) {
      if (str[i] > '9' || str[i] < '0') {  // 遇到⾮数字字符不合法
        return false;
      }
      num = num * 10 + (str[i] - '0');
      if (num > 255) {  // 如果⼤于255了不合法
        return false;
      }
    }

    return true;
  }
  void backtracking(string s, int start) {
    if (pathSize == 3) {
      if (isValid(s, start, s.size() - 1)) {
        path += string(s.begin() + start, s.end());
        ans.emplace_back(path);
      }
    }
    int index = path.size();
    for (int i = start; i < s.size(); ++i) {
      if (isValid(s, start, i)) {
        path += s.substr(start, i - start + 1) + '.';
        pathSize++;
        backtracking(s, i + 1);
        pathSize--;
        path.erase(path.begin() + index, path.end());
      } else {
        break;
      }
    }
  }
  vector<string> restoreIpAddresses(string s) {
    if (s.size() > 12) {
      return ans;
    }
    pathSize = 0;
    backtracking(s, 0);
    return ans;
  }
};