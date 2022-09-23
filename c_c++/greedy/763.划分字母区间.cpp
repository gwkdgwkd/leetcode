/*
字符串S由小写字母组成。
要把这个字符串划分为尽可能多的片段，
同一字母最多出现在一个片段中。
返回一个表示每个字符串片段的长度的列表。

示例：
输入：S = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为ababcbaca，defegde，hijhklij。
每个字母最多出现在一个片段中。
像ababcbacadefegde，hijhklij的划分是错误的，
因为划分的片段数较少。

提示：
S的长度在[1, 500]之间。
S只包含小写字母'a'到'z'。
*/

// 没有感受到贪心，找不出局部最优推出全局最优的过程。
// 时间复杂度：O(n)
// 空间复杂度：O(1)，使用的hash数组是固定大小
int* partitionLabels(char* s, int* returnSize) {
  int len = strlen(s);
  *returnSize = 0;
  int* res = (int*)malloc(sizeof(int) * len);

  int hash[26];
  memset(hash, 0, sizeof(hash));
  for (int i = 0; i < len; ++i) {
    hash[s[i] - 'a'] = i;  // 统计每一个字符最后出现的位置
  }
  int left = 0;
  int right = 0;
  // 从头遍历字符，并更新字符的最远出现下标，
  // 如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点
  for (int i = 0; i < len; ++i) {
    right = fmax(right, hash[s[i] - 'a']);  // 找到字符出现的最远边界
    if (i == right) {
      res[(*returnSize)++] = right - left + 1;
      left = i + 1;
    }
  }

  return res;
}

class Solution {
 public:
  vector<int> partitionLabels(string s) {
    int n = s.size();
    int hash[26];
    for (int i = 0; i < n; ++i) {
      hash[s[i] - 'a'] = i;
    }

    int left = 0;
    int right = 0;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
      right = max(right, hash[s[i] - 'a']);
      if (i == right) {
        ans.emplace_back(right - left + 1);
        left = right + 1;
      }
    }

    return ans;
  }
};