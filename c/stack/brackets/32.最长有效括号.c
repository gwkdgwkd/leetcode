/*
给你一个只包含'('和')'的字符串，找出最长有效（格式正确且连续）括号子串的长度。

示例1：
输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"

示例2：
输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"

示例3：
输入：s = ""
输出：0

提示：
0 <= s.length <= 3 * 104
s[i]为'('或')'
*/

// 动态规划
// 时间复杂度：O(n)
// 空间复杂度：O(n)
int longestValidParentheses(char* s) {
  int maxans = 0, n = strlen(s);
  if (n == 0) return 0;
  int dp[n];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i < n; i++) {
    if (s[i] == ')') {
      if (s[i - 1] == '(') {
        dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
      } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
        dp[i] =
            dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
      }
      maxans = fmax(maxans, dp[i]);
    }
  }
  return maxans;
}

// 栈
// 时间复杂度：O(n)
// 空间复杂度：O(n)
int longestValidParentheses(char* s) {
  int maxans = 0, n = strlen(s);
  int stk[n + 1], top = -1;
  // 如果一开始栈为空，第一个字符为左括号的时候我们会将其放入栈中，
  // 这样就不满足提及的「最后一个没有被匹配的右括号的下标」，
  // 为了保持统一，在一开始的时候往栈中放入一个值为−1的元素
  stk[++top] = -1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') {
      stk[++top] = i;  // 对于遇到的每个(，将它的下标放入栈中
    } else {
      // 对于遇到的每个)，先弹出栈顶元素表示匹配了当前右括号：
      // 1.如果栈为空，说明当前的右括号为没有被匹配的右括号，
      //   将其下标放入栈中来更新我们之前提到的「最后一个没有被匹配的右括号的下标」
      // 2.如果栈不为空，当前右括号的下标减去栈顶元素即为「以该右括号为结尾的最长有效括号的长度」
      --top;
      if (top == -1) {
        stk[++top] = i;
      } else {
        maxans = fmax(maxans, i - stk[top]);
      }
    }
  }
  return maxans;
}

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int longestValidParentheses(char* s) {
  int n = strlen(s);
  int left = 0, right = 0, maxlength = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') {
      left++;
    } else {
      right++;
    }
    if (left == right) {
      maxlength = fmax(maxlength, 2 * right);
    } else if (right > left) {
      left = right = 0;
    }
  }
  left = right = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == '(') {
      left++;
    } else {
      right++;
    }
    if (left == right) {
      maxlength = fmax(maxlength, 2 * left);
    } else if (left > right) {
      left = right = 0;
    }
  }
  return maxlength;
}