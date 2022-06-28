/*
给定一个可包含重复数字的序列nums，按任意顺序返回所有不重复的全排列。

示例1：
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]

示例2：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

提示：
1 <= nums.length <= 8
-10 <= nums[i] <= 10
*/

/*
->for循环，横向遍历
↓递归，纵向遍历              {1,1,2}
                           used{0,0,0}
              ↙ 取第1个1     d ↓ 取第2个1     ↘ 取元素2
        {1}                {1} 同层重复，丢弃      {2}
        used{1,0,0}        used{0,1,0}           used{0,0,1}
        [1,2]              [1,2]                 [1,1]
  a ↙ 取元素1    ↘ 取元素2                 ↙ 取第1个1  ↘ 取第2个1，c
{1,1}             {1,2}             {2,1}              {2,1} 同层重复，丢弃
used{1,1,0}       used{1,0,1}       used{1,0,1}        used{0,1,1}
[2]               [1]               [1]                [1]
   ↓ 取元素2          ↓ 取元素1        b ↓ 取元素1
{1,1,2}           {1,2,1}           {2,1,1}

a：i为1,nums[i] == nums[i - 1]，而used[i - 1]为1，
   说明同一树枝上有两个重复的元素，可以重复选取
b：同一树枝上可以重复选取
c：i为1,nums[i] == nums[i - 1]，而used[i - 1]为1，
   说明同一层上有两个重复元素，不可以重复选取
d：同一层前一位重复了，不能读取
*/

int** result;
int resultSize;
int* path;
int pathSize;
int cmp(int* a, int* b) { return *a > *b; }
void backtracking(int* nums, int numsSize, int* used) {
  if (pathSize == numsSize) {
    result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize++], path, sizeof(int) * pathSize);
    return;
  }

  for (int i = 0; i < numsSize; ++i) {
    // used[i-1] == 1，说明同⼀树⽀nums[i-1]使⽤过
    // used[i-1] == 0，说明同⼀树层nums[i-1]使⽤过
    // 如果同⼀树层nums[i-1]使⽤过则直接跳过
    // 如果要对树层中前⼀位去重，就⽤used[i-1] == false，
    // 如果要对树枝前⼀位去重⽤used[i-1] == true。
    // 对于排列问题，树层上去重和树枝上去重，都是可以的，但是树层上去重效率更⾼！
    // 树枝上对前⼀位去重虽然最后可以得到答案，但是做了很多⽆⽤搜索：

    // 树层去重
    // if (used[i] || (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == 0)) {
    // 树枝去重，从结果看，效率高些
    if (used[i] || (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == 1)) {
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
int** permuteUnique(int* nums, int numsSize, int* returnSize,
                    int** returnColumnSizes) {
  int maxSize = 1;
  for (int i = 1; i <= numsSize; i++) {
    maxSize *= i;
  }
  result = (int**)malloc(sizeof(int*) * maxSize);
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = (int*)malloc(sizeof(int) * maxSize);
  for (int i = 0; i < maxSize; ++i) {
    (*returnColumnSizes)[i] = numsSize;
  }
  resultSize = pathSize = 0;
  int used[numsSize];
  memset(used, 0, sizeof(used));
  qsort(nums, numsSize, sizeof(int), cmp);
  backtracking(nums, numsSize, used);
  *returnSize = resultSize;

  return result;
}

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
      if ((used[i]) || (i > 0 && nums[i] == nums[i - 1] &&
                        used[i - 1] == true)) {  // used[i - 1] == true也行
        continue;
      }
      path.emplace_back(nums[i]);
      used[i] = true;
      backtracking(nums);
      used[i] = false;
      path.pop_back();
    }
  }
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    used.assign(nums.size(), false);
    sort(nums.begin(), nums.end());
    backtracking(nums);
    return res;
  }
};
