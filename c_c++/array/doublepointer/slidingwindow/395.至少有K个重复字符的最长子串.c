/*
给你一个字符串s和一个整数k，请你找出s中的最长子串，
要求该子串中的每一字符出现次数都不少于k。
返回这一子串的长度。

示例1：
输入：s = "aaabb", k = 3
输出：3
解释：最长子串为"aaa"，其中'a'重复了3次。

示例2：
输入：s = "ababbc", k = 2
输出：5
解释：最长子串为"ababb"，其中'a'重复了2次，'b'重复了3次。

提示：
1 <= s.length <= 10^4
s仅由小写英文字母组成
1 <= k <= 10^5
*/

int dfs(char* s, int l, int r, int k) {
  int cnt[26];
  memset(cnt, 0, sizeof(cnt));
  for (int i = l; i <= r; i++) {
    cnt[s[i] - 'a']++;
  }

  char split = 0;
  for (int i = 0; i < 26; i++) {
    if (cnt[i] > 0 && cnt[i] < k) {
      split = i + 'a';
      break;
    }
  }
  if (split == 0) {
    return r - l + 1;
  }

  int ret = 0;
  for (int i = l; i <= r; ++i) {
    while (i <= r && s[i] == split) {
      i++;
    }
    if (i > r) {
      break;
    }
    int start = i;
    while (i <= r && s[i] != split) {
      i++;
    }

    int length = dfs(s, start, i - 1, k);
    ret = fmax(ret, length);
  }
  return ret;
}
int longestSubstring(char* s, int k) { return dfs(s, 0, strlen(s) - 1, k); }

// 滑动窗口
int longestSubstring(char* s, int k) {
  int ret = 0;
  int n = strlen(s);
  for (int t = 1; t <= 26; t++) {
    int l = 0, r = 0;
    int cnt[26];
    memset(cnt, 0, sizeof(cnt));
    int tot = 0;
    int less = 0;
    while (r < n) {
      cnt[s[r] - 'a']++;
      if (cnt[s[r] - 'a'] == 1) {
        tot++;
        less++;
      }
      if (cnt[s[r] - 'a'] == k) {
        less--;
      }

      while (tot > t) {
        cnt[s[l] - 'a']--;
        if (cnt[s[l] - 'a'] == k - 1) {
          less++;
        }
        if (cnt[s[l] - 'a'] == 0) {
          tot--;
          less--;
        }
        l++;
      }
      if (less == 0) {
        ret = fmax(ret, r - l + 1);
      }
      r++;
    }
  }
  return ret;
}