/*
给你一个整数数组nums，数组中的元素互不相同。返回该数组所有可能的子集（幂集）。
解集不能包含重复的子集。你可以按任意顺序返回解集。

示例1：
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

示例2：
输入：nums = [0]
输出：[[],[0]]

提示：
1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums中的所有元素互不相同
*/

// 剑指OfferII079所有子集
// 面试题0804幂集

// 回溯算法
// 组合问题和分割问题都是收集树的叶⼦节点，⽽⼦集问题是找树的所有节点！
int** result;
int resultSize;
int* path;
int pathSize;
void backtracking(int* nums, int numsSize, int startIndex,
                  int** returnColumnSizes) {
  // 收集⼦集，要放在终⽌添加的上⾯，否则会漏掉⾃⼰
  result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
  memcpy(result[resultSize], path, sizeof(int) * pathSize);
  (*returnColumnSizes)[resultSize] = pathSize;
  resultSize++;
  // 其实可以不需要加终⽌条件，因为startIndex>=numsSize，本层for循环本来也结束了。
  // if (startIndex >= numsSize) {
  //   return;
  // }

  // 求取⼦集问题，不需要任何剪枝！因为⼦集就是要遍历整棵树。
  for (int i = startIndex; i < numsSize; i++) {
    path[pathSize++] = nums[i];
    // 从i+1开始，元素不重复取
    backtracking(nums, numsSize, i + 1, returnColumnSizes);
    pathSize--;
  }

  return;
}
int** subsets(int* nums, int numsSize, int* returnSize,
              int** returnColumnSizes) {
  int maxSize = 1 << numsSize;  // 不重复子集的个数？
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
    ans.emplace_back(path);

    // 不写也行，如果下面等式成立，那么start也比nums.size()大了
    // if (path.size() == nums.size()) {
    //   return;
    // }

    for (int i = start; i < nums.size(); ++i) {
      path.emplace_back(nums[i]);
      backtracking(nums, i + 1);
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    backtracking(nums, 0);
    return ans;
  }
};