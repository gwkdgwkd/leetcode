/*
给你二叉树的根节点root和一个整数目标和targetSum，
找出所有从根节点到叶子节点路径总和等于给定目标和的路径。
叶子节点是指没有子节点的节点。

示例1：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：[[5,4,11,2],[5,8,4,5]]

示例2：
输入：root = [1,2,3], targetSum = 5
输出：[]

示例3：
输入：root = [1,2], targetSum = 0
输出：[]

提示：
树中节点总数在范围[0, 5000]内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000

注意：本题与113题相同
*/

int **result;
int resultSize;
int *path;
int pathSize;
int *colSize;
void traversal(struct TreeNode *root, int target) {
  if (root == NULL) return;

  path[pathSize++] = root->val;
  target -= root->val;
  if (!root->left && !root->right && target == 0) {
    result[resultSize] = (int *)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize], path, sizeof(int) * pathSize);
    colSize[resultSize] = pathSize;
    ++resultSize;
    --pathSize;
    return;
  }

  traversal(root->left, target);
  traversal(root->right, target);
  --pathSize;
}
int **pathSum(struct TreeNode *root, int target, int *returnSize,
              int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 2001);
  path = (int *)malloc(sizeof(int) * 2001);
  colSize = (int *)malloc(sizeof(int) * 2001);
  resultSize = pathSize = 0;
  traversal(root, target);
  *returnColumnSizes = colSize;
  *returnSize = resultSize;
  return result;
}