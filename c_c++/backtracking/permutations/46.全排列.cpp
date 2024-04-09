#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

/*
给定一个不含重复数字的数组nums，返回其所有可能的全排列，可以按任意顺序返回答案。

示例1：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

示例2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]

示例3：

输入：nums = [1]
输出：[[1]]

提示：
1 <= nums.length <= 6
-10 <= nums[i] <= 10
nums中的所有整数互不相同
*/

// 剑指OfferII083没有重复元素集合的全排列
// 面试题0807无重复字符串的排列组合

int** result;
int resultSize;
int* path;
int pathSize;
// 处理排列问题就不⽤使⽤startIndex了，需要重头遍历，如果已被用过，则跳过
void backtracking(int* nums, int numsSize, int* used) {
  if (pathSize == numsSize) {
    result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize++], path, sizeof(int) * pathSize);
    return;
  }

  for (int i = 0; i < numsSize; ++i) {
    // used数组，其实就是记录此时path⾥都有哪些元素使⽤了，⼀个排列⾥⼀个元素只能使⽤⼀次
    if (used[i]) {  // path⾥已经收录的元素，直接跳过
      continue;
    }
    path[pathSize++] = nums[i];
    used[i] = 1;
    backtracking(nums, numsSize, used);
    used[i] = 0;
    pathSize--;
  }

  return;
}
int** permute(int* nums, int numsSize, int* returnSize,
              int** returnColumnSizes) {
  (*returnSize) = 1;
  for (int i = 1; i <= numsSize; i++) {
    (*returnSize) *= i;
  }
  result = (int**)malloc(sizeof(int*) * (*returnSize));
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
  for (int i = 0; i < *returnSize; ++i) {
    (*returnColumnSizes)[i] = numsSize;
  }
  resultSize = pathSize = 0;
  int used[numsSize];  // 排列问题需要⼀个used数组，标记已经选择的元素
  memset(used, 0, sizeof(used));
  backtracking(nums, numsSize, used);

  return result;
}

using namespace std;
namespace n1 {
class Solution {
  vector<vector<int>> res;
  vector<int> path;
  vector<bool> used;

 public:
  void backtracking(vector<int>& nums) {
    if (path.size() == nums.size()) {
      res.emplace_back(path);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i]) {
        continue;
      }
      path.emplace_back(nums[i]);
      used[i] = true;
      backtracking(nums);
      used[i] = false;
      path.pop_back();
    }
  }
  vector<vector<int>> permute(vector<int>& nums) {
    used.assign(nums.size(), false);
    backtracking(nums);
    return res;
  }
};
}  // namespace n1

namespace n2 {
class Solution {
 public:
  void backtrack(vector<vector<int>>& res, vector<int>& output, int first,
                 int len) {
    if (first == len) {  // 所有数都填完了
      res.emplace_back(output);
      return;
    }
    for (int i = first; i < len; ++i) {
      // 动态维护数组
      swap(output[i], output[first]);
      // 继续递归填下一个数
      backtrack(res, output, first + 1, len);
      // 撤销操作
      swap(output[i], output[first]);
    }
  }
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    backtrack(res, nums, 0, (int)nums.size());
    return res;
  }
};
}  // namespace n2

int main() {
  vector<int> v{1, 2, 3};
  n1::Solution s;
  vector<vector<int>> ret = s.permute(v);

  [&ret]() {
    for (auto v : ret) {
      for (auto i : v) {
        cout << i << " ";
      }
      cout << endl;
    }
  }();

  // 1 2 3
  // 1 3 2
  // 2 1 3
  // 2 3 1
  // 3 1 2
  // 3 2 1
}