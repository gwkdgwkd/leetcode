/*
给你一个由数字和运算符组成的字符串expression，
按不同优先级组合数字和运算符，计算并返回所有可能组合的结果。
你可以按任意顺序返回答案。

示例1：
输入：expression = "2-1-1"
输出：[0,2]
解释：
((2-1)-1) = 0
(2-(1-1)) = 2

示例2：
输入：expression = "2*3-4*5"
输出：[-34,-14,-10,-10,10]
解释：
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10

提示：
1 <= expression.length <= 20
expression由数字和算符'+'、'-'和'*'组成。
输入表达式中的所有整数值在范围[0, 99]
*/

// 分治算法
int *diffWaysToCompute(char *input, int *returnSize) {
  if (input == NULL) {
    *returnSize = 0;
    return NULL;
  }

  int len = strlen(input);
  char *lstr = (char *)calloc(len, sizeof(char));
  char *rstr = (char *)calloc(len, sizeof(char));

  int mid = 0;
  int retcnt = 0;
  int calflag = 0;
  int *ret = (int *)calloc(1, sizeof(int));
  while (mid < len) {
    if (input[mid] >= '0' && input[mid] <= '9') {
      mid++;
      continue;
    }

    calflag = 1;
    memcpy(lstr, input, mid);
    lstr[mid] = '\0';
    memcpy(rstr, input + mid + 1, len - mid - 1);
    rstr[len - mid - 1] = '\0';

    int lsize = 0;
    int rsize = 0;
    int *lret = diffWaysToCompute(lstr, &lsize);
    int *rret = diffWaysToCompute(rstr, &rsize);

    int *retmp = (int *)realloc(ret, (retcnt + lsize * rsize) * sizeof(int));
    if (retmp == NULL) {
      return NULL;
    }
    ret = retmp;
    for (int i = 0; i < lsize; i++) {
      for (int j = 0; j < rsize; j++) {
        switch (input[mid]) {
          case '+':
            ret[retcnt++] = lret[i] + rret[j];
            break;
          case '-':
            ret[retcnt++] = lret[i] - rret[j];
            break;
          case '*':
            ret[retcnt++] = lret[i] * rret[j];
            break;
          default:
            break;
        }
      }
    }
    mid++;
  }

  if (calflag == 0) {
    *returnSize = 1;
    ret[0] = atoi(input);
    return ret;
  }

  *returnSize = retcnt;
  return ret;
}

// 分治
class Solution {
 public:
  vector<int> diffWaysToCompute(string exp) {
    vector<int> ans;
    if (exp.size() == 0) return {};
    for (int i = 0; i < exp.size(); i++) {
      char act = exp[i];
      if (act == '+' || act == '-' || act == '*') {
        vector<int> left = diffWaysToCompute(exp.substr(0, i));
        vector<int> right =
            diffWaysToCompute(exp.substr(i + 1, exp.size() - i - 1));
        for (int l_num : left) {
          for (int r_num : right) {
            if (act == '+') {
              ans.push_back(l_num + r_num);
            }
            if (act == '-') {
              ans.push_back(l_num - r_num);
            }
            if (act == '*') {
              ans.push_back(l_num * r_num);
            }
          }
        }
      }
    }
    if (ans.size() == 0) ans.push_back(stoi(exp));
    return ans;
  }
};