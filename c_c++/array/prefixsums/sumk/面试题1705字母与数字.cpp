/*
给定一个放有字母和数字的数组，找到最长的子数组，且包含的字母和数字的个数相同。
返回该子数组，若存在多个最长子数组，返回左端点下标值最小的子数组。
若不存在这样的数组，返回一个空数组。

示例1：
输入：["A","1","B","C","D","2","3","4","E","5",
      "F","G","6","7","H","I","J","K","L","M"]
输出：["A","1","B","C","D","2","3","4","E","5","F","G","6","7"]

示例2：
输入：["A","A"]
输出：[]

提示：array.length <= 100000
*/

char** findLongestSubarray(char** array, int arraySize, int* returnSize) {
  int hash[2 * arraySize + 1];
  for (int i = 0; i < 2 * arraySize + 1; i++) {
    hash[i] = -2;
  }
  hash[arraySize] = -1;
  int maxLength = 0;
  int endPos = 0;
  int sum = 0;  // sum的范围在-arraySize到arraySize之间
  for (int i = 0; i < arraySize; i++) {
    if (array[i][0] >= '0' && array[i][0] <= '9') {
      sum++;
    } else {
      sum--;
    }
    if (hash[sum + arraySize] == -2) {  // 因为sum可能为负，所以加上偏移量
      hash[sum + arraySize] = i;
    } else if (i - hash[sum + arraySize] > maxLength) {
      maxLength = i - hash[sum + arraySize];
      endPos = i;
    }
  }
  *returnSize = maxLength;
  return &(array[endPos - maxLength + 1]);
}

// 与[525.连续数组]类似
class Solution {
 public:
  vector<string> findLongestSubarray(vector<string>& array) {
    unordered_map<int, int> hash;
    hash[0] = -1;
    int n = array.size();
    int start = 0;
    int sum = 0;
    int maxLen = 0;

    for (int i = 0; i < n; ++i) {
      isdigit(array[i][0]) ? sum++ : sum--;
      if (hash.find(sum) != hash.end()) {
        if (i - hash[sum] > maxLen) {
          maxLen = i - hash[sum];
          start = hash[sum] + 1;
        }
      } else {
        hash[sum] = i;
      }
    }

    return {array.begin() + start, array.begin() + start + maxLen};
  }
};