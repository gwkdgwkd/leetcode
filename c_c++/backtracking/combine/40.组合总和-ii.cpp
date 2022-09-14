/*
给定一个候选人编号的集合candidates和一个目标数target，
找出candidates中所有可以使数字和为target的组合。
candidates中的每个数字在每个组合中只能使用一次。
注意：解集不能包含重复的组合。

示例1:
输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

示例2:
输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
]

提示:
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
*/

// 剑指OfferII082含有重复元素集合的组合

// 和39.组合总和如下区别：
// 1.candidates中的每个数字在每个组合中只能使⽤⼀次。
// 2.数组candidates的元素是有重复的，⽽39.组合总和是⽆重复元素的数组candidates
// 和39.组合总和要求⼀样，解集不能包含重复的组合。
int **result;
int resultSize;
int *path;
int pathSize;
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
void backtracking(int *candidates, int candidatesSize, int target,
                  int startIndex, int **returnColumnSizes, int *used) {
  if (target == 0) {
    result[resultSize] = (int *)malloc(sizeof(int) * pathSize);
    for (int i = 0; i < pathSize; ++i) {
      result[resultSize][i] = path[i];
    }
    (*returnColumnSizes)[resultSize] = pathSize;
    resultSize++;
    return;
  }
  for (int i = startIndex; i < candidatesSize && candidates[i] <= target; ++i) {
    // 元素在同⼀个组合内是可以重复的，怎么重复都没事，但两个组合不能相同。
    // 所以我们要去重的是同⼀树层上的“使⽤过”，同⼀树枝上的都是⼀个组合⾥的元素，不⽤去重。
    // 如果candidates[i]==candidates[i-1]并且used[i-1]==false，
    // 就说明：前⼀个树枝，使⽤了candidates[i-1]，也就是说同⼀树层使⽤过candidates[i-1]。
    if (i > 0 && candidates[i - 1] == candidates[i] && used[i - 1] == 0) {
      continue;
    }
    path[pathSize++] = candidates[i];
    // printf("%*d[%d %d]\n", pathSize * 2, candidates[i], i, target);
    used[i] = 1;  // used[i-1]==true，说明同⼀树⽀candidates[i-1]使⽤过
    backtracking(candidates, candidatesSize, target - candidates[i], i + 1,
                 returnColumnSizes, used);
    used[i] = 0;  // used[i-1]==false，说明同⼀树层candidates[i-1]使⽤过
    pathSize--;
  }

  return;
}
int **combinationSum2(int *candidates, int candidatesSize, int target,
                      int *returnSize, int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 1001);
  path = (int *)malloc(sizeof(int) * 2000);
  resultSize = pathSize = 0;
  *returnColumnSizes = malloc(sizeof(int) * 1001);
  // 强调⼀下，树层去重的话，需要对数组排序！
  qsort(candidates, candidatesSize, sizeof(int), cmp);
  int used[candidatesSize];
  memset(used, 0, sizeof(used));
  backtracking(candidates, candidatesSize, target, 0, returnColumnSizes, used);
  *returnSize = resultSize;

  return result;
}

class Solution {
  vector<vector<int>> ans;
  vector<int> path;
  vector<bool> used;
  void backtracking(vector<int> &candidates, int target, int start) {
    if (target == 0) {
      ans.emplace_back(path);
      return;
    }

    for (int i = start; i < candidates.size() && candidates[i] <= target; ++i) {
      if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false) {
        continue;
      }
      path.emplace_back(candidates[i]);
      used[i] = true;
      backtracking(candidates, target - candidates[i], i + 1);
      used[i] = false;
      path.pop_back();
    }
  }

 public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    used.assign(candidates.size(), false);
    sort(candidates.begin(), candidates.end());
    backtracking(candidates, target, 0);
    return ans;
  }
};

// 不使用used数组也可以：
class Solution {
  vector<vector<int>> ans;
  vector<int> path;

 public:
  void dfs(vector<int> &candidates, int target, int start) {
    if (target == 0) {
      ans.emplace_back(path);
      return;
    }

    for (int i = start; i < candidates.size() && candidates[i] <= target; ++i) {
      if (i > start && candidates[i] == candidates[i - 1]) {
        // 这个避免重复当思想是在是太重要了。
        // 这个方法最重要的作用是，可以让同一层级，不出现相同的元素。
        // 这种情况不会发生：
        //     1
        //    / \
        //   2   2
        //  /     \
        // 5       5
        // 这种情况确是允许的：
        //     1
        //    /
        //   2
        //  /
        // 2
        // 为何会有这种神奇的效果呢？
        // 首先candidates[i] == candidates[i - 1]，
        // 是用于判定当前元素是否和之前元素相同的语句。
        // 这个语句就能砍掉第一中情况，可是问题来了，
        // 如果把所有与之前一个元素相同的都砍掉，那么第二种情况也会消失。
        // 因为当第二个2出现的时候，他就和前一个2相同了。
        // 那么如何保留例2呢？
        // 那么就用i > start来避免这种情况，
        // 第一种情况的两个2是处在同一个层级上的，当i>start时，
        // 证明同一层中已经使用过了相同的元素。
        // 第二种情况的两个2是处在不同层级上的，当i==start时，
        // 证明是当前层的第一个元素，虽然candidates[i]==candidates[i-1]，
        // 但这是一个树枝上的，不是同一层的。
        continue;
      }
      path.emplace_back(candidates[i]);
      dfs(candidates, target - candidates[i], i + 1);
      path.pop_back();
    }
  }
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    dfs(candidates, target, 0);
    return ans;
  }
};