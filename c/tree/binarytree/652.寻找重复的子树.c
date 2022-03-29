/*
给定一棵二叉树root，返回所有重复的子树。
对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。
如果两棵树具有相同的结构和相同的结点值，则它们是重复的。

示例1：
输入：root = [1,2,3,4,null,2,4,null,null,4]
输出：[[2,4],[4]]

示例 2：
输入：root = [2,1,1]
输出：[[1]]

示例3：
输入：root = [2,2,2,3,null,3,null]
输出：[[2,3],[3]]

提示：
树中的结点数在[1,10^4]范围内。
-200 <= Node.val <= 200
*/

// DFS+哈希
typedef struct {
  char key[20000];
  struct TreeNode* node;
  int cnt;
  UT_hash_handle hh;
} HASH_TABLE;
HASH_TABLE* set = NULL;
char* dfsAddHash(struct TreeNode* root, HASH_TABLE* obj) {
  if (root == NULL) {
    return "#";
  }
  char* str = (char*)calloc(20000, sizeof(char));
  sprintf(str, "%d ", root->val);
  strcat(str, dfsAddHash(root->left, set));
  strcat(str, dfsAddHash(root->right, set));
  HASH_TABLE* tmp;
  HASH_FIND_STR(set, str, tmp);
  if (tmp == NULL) {
    tmp = (HASH_TABLE*)calloc(1, sizeof(HASH_TABLE));
    memcpy(tmp->key, str, strlen(str));
    tmp->node = root;
    tmp->cnt = 1;
    HASH_ADD_STR(set, key, tmp);
  } else {
    tmp->cnt++;
  }
  return str;
}
struct TreeNode** findDuplicateSubtrees(struct TreeNode* root,
                                        int* returnSize) {
  *returnSize = 0;
  if (root == NULL) {
    return NULL;
  }
  dfsAddHash(root, set);
  HASH_TABLE *cur, *tmp;
  struct TreeNode** queue =
      (struct TreeNode**)calloc(20000, sizeof(struct TreeNode*));
  HASH_ITER(hh, set, cur, tmp) {
    if (cur->cnt > 1) {
      queue[(*returnSize)++] = cur->node;
    }
    HASH_DEL(set, cur);
    free(cur);
  }
  return queue;
}