/*
给定一个不重复的整数数组nums。
最大二叉树可以用下面的算法从nums递归地构建:
创建一个根节点，其值为nums中的最大值。
递归地在最大值左边的子数组前缀上构建左子树。
递归地在最大值右边的子数组后缀上构建右子树。
返回nums构建的最大二叉树。

示例1：
输入：nums = [3,2,1,6,0,5]
输出：[6,3,5,null,2,0,null,null,1]
解释：递归调用如下所示：
     [3,2,1,6,0,5]中的最大值是6，左边部分是[3,2,1]，右边部分是[0,5]。
     [3,2,1]中的最大值是3，左边部分是[]，右边部分是[2,1]。
     空数组，无子节点。
     [2,1]中的最大值是2，左边部分是[]，右边部分是[1]。
     空数组，无子节点。
     只有一个元素，所以子节点是一个值为1的节点。
     [0,5]中的最大值是5，左边部分是[0]，右边部分是[]。
     只有一个元素，所以子节点是一个值为0的节点。
     空数组，无子节点。

示例2：
输入：nums = [3,2,1]
输出：[3,null,2,null,1]

提示：
1 <= nums.length <= 1000
0 <= nums[i] <= 1000
nums中的所有整数互不相同
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct TreeNode* traversal(int* nums, int start, int end) {
  if (start == end) return NULL;

  int delimiter;
  int max = INT_MIN;
  for (int i = start; i < end; ++i) {
    if (nums[i] > max) {
      max = nums[i];
      delimiter = i;
    }
  }
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = max;
  if (start + 1 == end) {
    root->left = NULL;
    root->right = NULL;
    return root;
  }

  root->left = traversal(nums, start, delimiter);
  root->right = traversal(nums, delimiter + 1, end);

  return root;
}
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
  if (numsSize == 0) return NULL;

  return traversal(nums, 0, numsSize);
}

struct TreeNode* build(int* nums, int lo, int hi) {
  if (lo > hi) {
    return NULL;
  }

  int index = -1, maxVal = INT_MIN;
  for (int i = lo; i <= hi; ++i) {
    if (maxVal < nums[i]) {
      maxVal = nums[i];
      index = i;
    }
  }

  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = maxVal;
  root->left = build(nums, lo, index - 1);
  root->right = build(nums, index + 1, hi);

  return root;
}
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
  return build(nums, 0, numsSize - 1);
}

class Solution {
 public:
  TreeNode* constructMaximumBinaryTree(vector<int>& nums, int left, int right) {
    if (left > right) {
      return nullptr;
    }
    if (left == right) {
      new TreeNode(left);
    }

    int index = left;
    int max = nums[left];
    for (int i = left; i <= right; ++i) {
      if (nums[i] > max) {
        max = nums[i];
        index = i;
      }
    }

    TreeNode* node = new TreeNode(max);
    node->left = constructMaximumBinaryTree(nums, left, index - 1);
    node->right = constructMaximumBinaryTree(nums, index + 1, right);
    return node;
  }
  TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return constructMaximumBinaryTree(nums, 0, nums.size() - 1);
  }
};
