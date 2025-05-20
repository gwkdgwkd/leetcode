/*
给一个二叉搜索树的根节点root，和一个由正整数组成、长度为n的数组queries。
请找出一个长度为n的二维答案数组answer，其中answer[i] = [mini, maxi]：
mini是树中小于等于queries[i]的最大值。如果不存在这样的值，则使用-1代替。
maxi是树中大于等于queries[i]的最小值。如果不存在这样的值，则使用-1代替。
返回数组answer。

示例1 ：
输入：root = [6,2,13,1,4,9,15,null,null,null,null,null,null,14],
     queries = [2,5,16]
输出：[[2,2],[4,6],[15,-1]]
解释：按下面的描述找出并返回查询的答案：
     树中小于等于2的最大值是2，且大于等于2的最小值也是2。第一个答案是[2,2]。
     树中小于等于5的最大值是4，且大于等于5的最小值是6。第二个答案是[4,6]。
     树中小于等于16的最大值是15，且大于等于16的最小值不存在。第三个答案是[15,-1]。

示例2：
输入：root = [4,null,9], queries = [3]
输出：[[-1,4]]
解释：树中不存在小于等于3的最大值，且大于等于3的最小值是4。所以查询的答案是[-1,4]。


提示：
树中节点的数目在范围[2, 10^5]内
1 <= Node.val <= 10^6
n == queries.length
1 <= n <= 10^5
1 <= queries[i] <= 10^6
*/

class Solution {
 public:
  vector<int> find(TreeNode* root, int target) {
    int smaller = root->val;
    int larger = root->val;
    vector<int> ans(2, 0);

    while (root) {
      if (root->val == target) {
        ans[0] = target;
        ans[1] = target;
        return ans;
      }

      if (root->val > target) {
        larger = root->val;
        root = root->left;
      } else {
        smaller = root->val;
        root = root->right;
      }
    }

    ans[0] = smaller <= target ? smaller : -1;
    ans[1] = larger >= target ? larger : -1;

    return ans;
  }

  vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
    int n = queries.size();
    vector<vector<int>> ans(n, vector<int>(2, -1));

    for (int i = 0; i < n; i++) {
      int q = queries[i];
      ans[i] = find(root, q);
    }

    return ans;
  }
};

class Solution {
 public:
  vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
    vector<int> arr;
    function<void(TreeNode*)> dfs = [&](TreeNode* root) {
      if (!root) {
        return;
      }
      dfs(root->left);
      arr.emplace_back(root->val);
      dfs(root->right);
    };
    dfs(root);

    vector<vector<int>> res;
    for (int val : queries) {
      int maxVal = -1, minVal = -1;
      auto it = lower_bound(arr.begin(), arr.end(), val);
      if (it != arr.end()) {
        maxVal = *it;
        if (*it == val) {
          minVal = *it;
          res.push_back({minVal, maxVal});
          continue;
        }
      }
      if (it != arr.begin()) {
        minVal = *(--it);
      }
      res.push_back({minVal, maxVal});
    }
    return res;
  }
};