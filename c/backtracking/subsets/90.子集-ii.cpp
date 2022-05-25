/*
给你一个整数数组nums，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
解集不能包含重复的子集。返回的解集中，子集可以按任意顺序排列。

示例1：
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]

示例2：
输入：nums = [0]
输出：[[],[0]]

提示：
1 <= nums.length <= 10
-10 <= nums[i] <= 10
*/

// 回溯算法
int** result;
int resultSize;
int* path;
int pathSize;
int cmp(int* a, int* b) { return *a - *b; }
void backtracking(int* nums, int numsSize, int startIndex,
                  int** returnColumnSizes, int* used) {
  result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
  memcpy(result[resultSize], path, sizeof(int) * pathSize);
  (*returnColumnSizes)[resultSize] = pathSize;
  resultSize++;

  for (int i = startIndex; i < numsSize; i++) {
    if (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == 0) {
      continue;
    }
    path[pathSize++] = nums[i];
    used[i] = 1;
    backtracking(nums, numsSize, i + 1, returnColumnSizes, used);
    used[i] = 0;
    pathSize--;
  }

  return;
}
int** subsetsWithDup(int* nums, int numsSize, int* returnSize,
                     int** returnColumnSizes) {
  int maxSize = 1 << numsSize;
  result = (int**)malloc(sizeof(int*) * maxSize);
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = malloc(sizeof(int) * maxSize);
  resultSize = pathSize = 0;
  int used[numsSize];
  memset(used, 0, sizeof(used));
  qsort(nums, numsSize, sizeof(int), cmp);
  backtracking(nums, numsSize, 0, returnColumnSizes, used);
  *returnSize = resultSize;

  return result;
}

class Solution {
  vector<vector<int>> ans;
  vector<int> path;
  void backtracking(vector<int>& nums, int start, vector<int>& used) {
    ans.emplace_back(path);

    for (int i = start; i < nums.size(); ++i) {
      if (i > start && nums[i] == nums[i - 1] && used[i] == 0) {
        continue;
      }
      path.emplace_back(nums[i]);
      used[i] = 1;
      backtracking(nums, i + 1, used);
      used[i] = 0;
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<int> used(nums.size(), 0);
    backtracking(nums, 0, used);
    return ans;
  }
};
