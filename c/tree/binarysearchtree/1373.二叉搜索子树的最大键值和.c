int maxSum;
int* traverse(struct TreeNode* root) {
  int* res = (int*)malloc(sizeof(int) * 4);
  if (!root) {
    res[0] = 1;
    res[1] = INT_MAX;
    res[2] = INT_MIN;
    res[3] = 0;
    return res;
  }

  // 后序遍历，减小时间复杂度

  // 递归计算左右子树
  int* left = traverse(root->left);
  int* right = traverse(root->right);

  // 这个if在判断以root为根的二叉树是不是BST
  if (left[0] == 1 && right[0] == 1 && root->val > left[2] &&
      root->val < right[1]) {
    // 以root为根的二叉树是BST
    res[0] = 1;
    // 计算以root为根的这棵BST的最小值
    res[1] = fmin(left[1], root->val);
    // 计算以root为根的这棵 BST 的最大值
    res[2] = fmax(right[2], root->val);
    // 计算以root为根的这棵 BST 所有节点之和
    res[3] = left[3] + right[3] + root->val;
    // 更新全局变量
    maxSum = fmax(maxSum, res[3]);
  } else {
    // 以root为根的二叉树不是BST
    res[0] = 0;
    // 其他的值都没必要计算了，因为用不到
  }

  return res;
}
int maxSumBST(struct TreeNode* root) {
  maxSum = 0;
  traverse(root);
  return maxSum;
}

// 时间比上面的快
#define MAX_VALUE 40001
int Max(int a, int b) { return a > b ? a : b; }
int Min(int a, int b) { return a < b ? a : b; }
int g_maxSum;
bool CalculateMaxSumBST(struct TreeNode* root, int* sum, int* max, int* min) {
  int leftSum = 0;
  int rightSum = 0;
  int leftMaxValue = -MAX_VALUE;
  int leftMinValue = MAX_VALUE;
  int rightMaxValue = -MAX_VALUE;
  int rightMinValue = MAX_VALUE;
  bool leftIsBSTTree = false;
  bool rightIsBSTTree = false;
  if (root == NULL) {
    return true;
  }

  leftIsBSTTree =
      CalculateMaxSumBST(root->left, &leftSum, &leftMaxValue, &leftMinValue);
  rightIsBSTTree = CalculateMaxSumBST(root->right, &rightSum, &rightMaxValue,
                                      &rightMinValue);
  if (leftIsBSTTree && rightIsBSTTree) {
    if (root->left != NULL) {
      if (root->val <= root->left->val) {
        return false;
      }
      if (root->val <= leftMaxValue) {
        return false;
      }
      *sum += leftSum;
    }
    *min = Min(root->val, leftMinValue);
    if (root->right != NULL) {
      if (root->val >= root->right->val) {
        return false;
      }
      if (root->val >= rightMinValue) {
        return false;
      }
      *sum += rightSum;
    }
    *max = Max(root->val, rightMaxValue);
    *sum += root->val;
    g_maxSum = Max(g_maxSum, *sum);
    return true;
  }
  return false;
}
int maxSumBST(struct TreeNode* root) {
  int sum = 0;
  int maxValue = -MAX_VALUE;
  int minValue = MAX_VALUE;
  g_maxSum = 0;
  CalculateMaxSumBST(root, &sum, &maxValue, &minValue);
  return g_maxSum;
}