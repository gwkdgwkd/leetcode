/*
设计一个算法，找出数组中两数之和为指定值的所有整数对。一个数只能属于一个数对。

示例1：
输入：nums = [5,6,5], target = 11
输出：[[5,6]]

示例2：
输入：nums = [5,6,5,6], target = 11
输出：[[5,6],[5,6]]

提示：nums.length <= 100000
*/

int compare(void* n1, void* n2) { return *((int*)n1) - *((int*)n2); }
int** pairSums(int* nums, int numsSize, int target, int* returnSize,
               int** returnColumnSizes) {
  int** ans = (int**)malloc(sizeof(int*) * numsSize / 2);
  *returnColumnSizes = (int*)malloc(sizeof(int) * numsSize / 2);
  for (int i = 0; i < numsSize / 2; ++i) {
    ans[i] = (int*)malloc(sizeof(int) * 2);
    (*returnColumnSizes)[i] = 2;
  }
  qsort(nums, numsSize, sizeof(int), compare);
  int size = 0;
  int left = 0;
  int right = numsSize - 1;
  int value;
  while (left < right) {
    value = nums[left] + nums[right];
    if (value == target) {
      ans[size][0] = nums[left];
      ans[size++][1] = nums[right];
      ++left;
      --right;
    } else if (value > target) {
      --right;
    } else {
      ++left;
    }
  }
  *returnSize = size;
  return ans;
}

class Solution {
 public:
  vector<vector<int>> pairSums(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());

    int left = 0;
    int right = nums.size() - 1;

    vector<vector<int>> res;
    while (left < right) {
      int sum = nums[left] + nums[right];
      if (sum < target) {
        ++left;
      } else if (sum > target) {
        --right;
      } else {
        vector<int> v{nums[left++], nums[right--]};
        res.emplace_back(v);
      }
    }

    return res;
  }
};

class Solution {
 public:
  vector<vector<int>> pairSums(vector<int>& nums, int target) {
    int n = nums.size();
    unordered_map<int, vector<int>> cnt;
    vector<vector<int>> ans;
    for (int i = 0; i < n; ++i) {
      auto it = cnt.find(target - nums[i]);
      if (it != cnt.end()) {
        vector<int> v{nums[it->second.back()], nums[i]};
        ans.emplace_back(v);
        it->second.pop_back();
        if (it->second.size() == 0) {
          cnt.erase(target - nums[i]);
        }
      } else {
        cnt[nums[i]].emplace_back(i);
      }
    }
    return ans;
  }
};