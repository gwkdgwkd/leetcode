/*
给一个整数数组nums，找出并返回所有该数组中不同的递增子序列，
递增子序列中至少有两个元素，可以按任意顺序返回答案。
数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。

示例1：
输入：nums = [4,6,7,7]
输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

示例2：
输入：nums = [4,4,3,2,1]
输出：[[4,4]]

提示：
1 <= nums.length <= 15
-100 <= nums[i] <= 100
*/

// 回溯算法
// 递增⼦序列⽐较像是取有序的⼦集，⽽且也要求不能有相同的递增⼦序列。
// ⼜是⼦集，⼜是去重，是不是不由⾃主的想起了90，子集-ii，
// 但求⾃增⼦序列，是不能对原数组经⾏排序的，排完序的数组都是⾃增⼦序列了。
// 所以不能使⽤之前的去重逻辑！
int** result;
int resultSize;
int* path;
int pathSize;
// 求⼦序列，很明显⼀个元素不能重复使⽤，所以需要startIndex，调整下⼀层递归的起始位置。
void backtracking(int* nums, int numsSize, int startIndex,
                  int** returnColumnSizes) {
  if (pathSize > 1) {
    result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize], path, sizeof(int) * pathSize);
    (*returnColumnSizes)[resultSize] = pathSize;
    resultSize++;
  }

  // 和78⼀样，可以不加终⽌条件，startIndex每次都会加1，并不会⽆限递归。

  // 同⼀⽗节点下的同层上使⽤过的元素就不能在使⽤了
  int used[201];  // hash
  memset(used, 0, sizeof(used));
  for (int i = startIndex; i < numsSize; ++i) {
    if ((pathSize > 0 && nums[i] < path[pathSize - 1]) ||
        (used[nums[i] + 100] == 1)) {
      continue;
    }
    // 只有赋值，没有复位
    used[nums[i] + 100] = 1;  // 记录元素在本层⽤过了，本层后⾯不能再⽤
    path[pathSize++] = nums[i];
    backtracking(nums, numsSize, i + 1, returnColumnSizes);
    pathSize--;
  }

  return;
}
int** findSubsequences(int* nums, int numsSize, int* returnSize,
                       int** returnColumnSizes) {
  int maxSize = 1 << numsSize;
  result = (int**)malloc(sizeof(int*) * maxSize);
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = malloc(sizeof(int) * maxSize);
  resultSize = pathSize = 0;
  backtracking(nums, numsSize, 0, returnColumnSizes);
  *returnSize = resultSize;

  return result;
}

class Solution {
  vector<vector<int>> ans;
  vector<int> path;
  void backtracking(vector<int>& nums, int start) {
    if (path.size() > 1) {
      ans.emplace_back(path);
    }

    unordered_set<int> used;
    for (int i = start; i < nums.size(); ++i) {
      // 不满足递增或者该元素在同一层使用过，不使用该元素：
      if ((path.size() > 0 && nums[i] < path.back()) || used.count(nums[i])) {
        continue;
      }
      used.insert(nums[i]);
      path.emplace_back(nums[i]);
      backtracking(nums, i + 1);
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> findSubsequences(vector<int>& nums) {
    backtracking(nums, 0);
    return ans;
  }
};