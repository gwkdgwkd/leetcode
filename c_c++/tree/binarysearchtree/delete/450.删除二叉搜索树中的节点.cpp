/*
给定一个二叉搜索树的根节点root和一个值key，删除二叉搜索树中的key对应的节点，
并保证二叉搜索树的性质不变，返回二叉搜索树（有可能被更新）的根节点的引用。
一般来说，删除节点可分为两个步骤：
首先找到需要删除的节点；
如果找到了，删除它。

示例1：
输入：root = [5,3,6,2,4,null,7], key = 3
输出：[5,4,6,2,null,null,7]
解释：给定需要删除的节点值是3，所以我们首先找到3这个节点，然后删除它。
     一个正确的答案是[5,4,6,2,null,null,7]。
     另一个正确答案是[5,2,6,null,4,null,7]。

示例2：
输入：root = [5,3,6,2,4,null,7], key = 0
输出：[5,3,6,2,4,null,7]
解释：二叉树不包含值为0的节点

示例3：
输入：root = [], key = 0
输出：[]

提示：
节点数的范围[0, 10^4].
-10^5 <= Node.val <= 10^5
节点值唯一
root是合法的二叉搜索树
-10^5 <= key <= 10^5

进阶：要求算法时间复杂度为O(h)，h为树的高度。
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
  // 第⼀种情况：没找到删除的节点，遍历到空节点直接返回了
  if (root == NULL) return root;

  if (root->val > key) {
    root->left = deleteNode(root->left, key);
  } else if (root->val < key) {
    root->right = deleteNode(root->right, key);
  } else {
    if (root->left == NULL) {
      // 第⼆种情况：左右孩⼦都为空（叶⼦节点），什么都不做，直接删除节点，返回NULL为根节点
      // 第三种情况：其左孩⼦为空，右孩⼦不为空，删除节点，右孩⼦补位，返回右孩⼦为根节点
      return root->right;
    } else if (root->right == NULL) {
      // 第四种情况：其右孩⼦为空，左孩⼦不为空，删除节点，左孩⼦补位，返回左孩⼦为根节点
      return root->left;
    } else {
      // 第五种情况：左右孩⼦节点都不为空，则将删除节点的左⼦树放到删除节点的右⼦树的最左⾯
      //           节点的左孩⼦的位置并返回删除节点右孩⼦为新的根节点。
      struct TreeNode* cur = root->right;  // 找右⼦树最左⾯的节点
      while (cur->left) {
        cur = cur->left;
      }
      cur->left = root->left;  // 把要删除的节点root左⼦树放在cur的左孩⼦的位置
      struct TreeNode* tmp = root;  // 把root节点保存⼀下，下⾯来删除
      root = root->right;           // 返回旧root的右孩⼦作为新root
      free(tmp);                    // 释放节点内存
      return root;
    }
  }

  return root;
}

// 递归
// 代码中⽬标节点（要删除的节点）被操作了两次：
// 第⼀次是和⽬标节点的右⼦树最左⾯节点交换。
// 第⼆次直接被NULL覆盖了。
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
  if (root == NULL) return root;

  if (root->val == key) {
    if (root->right == NULL) {  // 这⾥第⼆次操作⽬标值：最终删除的作⽤
      return root->left;
    }
    struct TreeNode* cur = root->right;
    while (cur->left) {
      cur = cur->left;
    }
    // 这⾥第⼀次操作⽬标值：交换⽬标值其右⼦树最左⾯节点。
    int tmp = cur->val;
    cur->val = root->val;
    root->val = tmp;
  }
  root->left = deleteNode(root->left, key);
  root->right = deleteNode(root->right, key);

  return root;
}

// 递归，BST框架
struct TreeNode* getMin(struct TreeNode* node) {
  while (node->left != NULL) node = node->left;
  return node;
}
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
  if (root == NULL) return root;
  if (root->val == key) {
    if (root->left == NULL) return root->right;
    if (root->right == NULL) return root->left;
    struct TreeNode* minNode = getMin(root->right);
    root->val = minNode->val;
    root->right = deleteNode(root->right, minNode->val);
  } else if (root->val > key) {
    root->left = deleteNode(root->left, key);
  } else if (root->val < key) {
    root->right = deleteNode(root->right, key);
  }
  return root;
}

class Solution {
 public:
  TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;

    if (root->val < key) {
      root->right = deleteNode(root->right, key);
    } else if (root->val > key) {
      root->left = deleteNode(root->left, key);
    } else {
      if (root->left == nullptr) {
        return root->right;
      } else if (root->right == nullptr) {
        return root->left;
      } else {
        TreeNode* cur = root->right;
        while (cur->left) {
          cur = cur->left;
        }
        cur->left = root->left;
        TreeNode* temp = root;
        root = root->right;
        delete (temp);
        return root;
      }
    }
    return root;
  }
};

// 删除节点的迭代法比较复杂