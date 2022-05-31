/*
给你一个整数数组nums，其中元素已经按升序排列，请你将其转换为一棵高度平衡二叉搜索树。
高度平衡二叉树是一棵满足每个节点的左右两个子树的高度差的绝对值不超过1的二叉树。

示例1：
输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9]也将被视为正确答案：

示例2：
输入：nums = [1,3]
输出：[3,1]
解释：[1,null,3]和[3,1]都是高度平衡二叉搜索树。

提示：
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums按严格递增顺序排列
*/

// 面试题0402最小高度树

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* convert(int* nums, int left, int right) {
  if (left > right) return NULL;
  struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  // 这么写其实有⼀个问题，就是数值越界，例如left和right都是最⼤int，
  // 这么操作就越界了，在⼆分法中尤其需要注意！
  // int mid = (left + right) / 2;
  int mid = left + (right - left) / 2;
  node->val = nums[mid];
  node->left = convert(nums, left, mid - 1);
  node->right = convert(nums, mid + 1, right);
  return node;
}
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
  return convert(nums, 0, numsSize - 1);
}

// 迭代法可以通过三个队列来模拟，⼀个队列放遍历的节点，⼀个队列放左区间下表，⼀个队列放右区间下表。
