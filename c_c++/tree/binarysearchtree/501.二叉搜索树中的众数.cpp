/*
给你一个含重复值的二叉搜索树（BST）的根节点root，
找出并返回BST中的所有众数（即，出现频率最高的元素）。
如果树中有不止一个众数，可以按任意顺序返回。

假定BST满足如下定义：
结点左子树中所含节点的值小于等于当前节点的值
结点右子树中所含节点的值大于等于当前节点的值
左子树和右子树都是二叉搜索树

示例1：
输入：root = [1,null,2,2]
输出：[2]

示例2：
输入：root = [0]
输出：[0]

提示：
树中节点的数目在范围[1, 10^4]内
-10^5 <= Node.val <= 10^5

进阶：你可以不使用额外的空间吗？
     假设由递归产生的隐式调用栈的开销不被计算在内。
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
int* result;
int resultSize;
int count;
int maxCount;
struct TreeNode* pre;
void traversal(struct TreeNode* root) {
  if (root == NULL) return;

  traversal(root->left);
  if (pre == NULL) {  // 第一个节点
    count = 1;
  } else if (root->val == pre->val) {  // 与当前值一样
    count++;
  } else {  // 与当前值不一样
    count = 1;
  }
  pre = root;
  if (count == maxCount) {  // 有多个众数
    result[resultSize++] = root->val;
  }
  if (count > maxCount) {
    maxCount = count;
    resultSize = 0;
    result[resultSize++] = root->val;
  }
  traversal(root->right);
  return;
}
int* findMode(struct TreeNode* root, int* returnSize) {
  result = (int*)malloc(sizeof(int) * 10000);
  count = maxCount = resultSize = 0;
  pre == NULL;
  traversal(root);
  *returnSize = resultSize;
  return result;
}

class Solution {
 public:
  vector<int> answer;
  int base, count, maxCount;

  void update(int x) {
    if (x == base) {
      ++count;
    } else {
      count = 1;
      base = x;
    }
    if (count == maxCount) {
      answer.push_back(base);
    }
    if (count > maxCount) {
      maxCount = count;
      answer = vector<int>{base};
    }
  }

  void dfs(TreeNode* o) {
    if (!o) {
      return;
    }
    dfs(o->left);
    update(o->val);
    dfs(o->right);
  }

  vector<int> findMode(TreeNode* root) {
    dfs(root);
    return answer;
  }
};
