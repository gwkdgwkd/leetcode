/*
一个整数数组nums，返回nums[i] XOR nums[j]的最大运算结果，其中0 ≤ i ≤ j< n。
进阶：你可以在O(n)的时间解决这个问题吗？

示例1：
输入：nums = [3,10,5,25,2,8]
输出：28
解释：最大运算结果是5 XOR 25 = 28.

示例2：
输入：nums = [0]
输出：0

示例3：
输入：nums = [2,4]
输出：6

示例4：
输入：nums = [8,10,2]
输出：10

示例5：
输入：nums = [14,70,53,83,49,91,36,80,92,51,66,70]
输出：127

提示：
1 <= nums.length <= 2 * 10^4
0 <= nums[i] <= 2^31 - 1
*/

// 剑指OfferII067最大的异或

// 超时
int findMaximumXOR(int *nums, int numsSize) {
  unsigned int max = 0, mask = 0;
  for (int i = 31; i >= 0; i--) {
    int set[numsSize];
    mask = mask | ((unsigned int)1 << i);
    for (int j = 0; j < numsSize; ++j) {
      set[j] = nums[j] & mask;
    }
    int temp = max | ((unsigned int)1 << i);
    for (int k = 0; k < numsSize - 1; ++k) {
      for (int l = k + 1; l < numsSize; ++l)
        if ((set[k] ^ set[l]) == temp) {
          max = temp;
          break;
        }
    }
  }
  return max;
}

// 字典树
#define BITS 30
#define MINS 2
typedef struct TypeNumTree {
  struct TypeNumTree *zero;
  struct TypeNumTree *one;
} NumTree;
static NumTree *CreatTree() {
  NumTree *tree = (NumTree *)malloc(sizeof(NumTree));
  if (tree == NULL) {
    return NULL;
  }
  tree->zero = NULL;
  tree->one = NULL;
  return tree;
}
static void AddNum(NumTree *tree, int num) {
  NumTree *itree = tree;
  for (int i = BITS; i >= 0; i--) {
    if ((num >> i) & 1) {
      if (!itree->one) {
        itree->one = CreatTree();
      }
      itree = itree->one;
    } else {
      if (!itree->zero) {
        itree->zero = CreatTree();
      }
      itree = itree->zero;
    }
  }
}
static int Dfs(const NumTree *a, const NumTree *b, int depth, int accu) {
  if (depth <= 0) {
    return accu;
  }
  unsigned max = 0;
  unsigned tmp = 0;
  if (a->zero && b->one) {
    max = Dfs(a->zero, b->one, depth - 1, accu + (1 << (depth - 1)));
  }
  if (a->one && b->zero) {
    tmp = Dfs(a->one, b->zero, depth - 1, accu + (1 << (depth - 1)));
    max = fmax(tmp, max);
  }
  if (max != 0) {
    return max;
  }
  if (a->one && b->one) {
    max = Dfs(a->one, b->one, depth - 1, accu);
  }
  if (a->zero && b->zero) {
    tmp = Dfs(a->zero, b->zero, depth - 1, accu);
    max = fmax(tmp, max);
  }
  return max;
}
int findMaximumXOR(int *nums, int numsSize) {
  if (numsSize < MINS) {
    return 0;
  }
  NumTree *tree = CreatTree();
  for (int i = 0; i < numsSize; i++) {
    AddNum(tree, nums[i]);
  }
  int bits = BITS;
  while (true) {
    if (!tree->zero) {
      tree = tree->one;
      bits--;
    } else if (!tree->one) {
      tree = tree->zero;
      bits--;
    } else {
      break;
    }
  }
  return Dfs(tree->zero, tree->one, bits, 1 << bits);
}

struct Trie {
  // 左子树指向表示 0 的子节点
  Trie *left = nullptr;
  // 右子树指向表示 1 的子节点
  Trie *right = nullptr;

  Trie() {}
};

class Solution {
 private:
  // 字典树的根节点
  Trie *root = new Trie();
  // 最高位的二进制位编号为30
  static constexpr int HIGH_BIT = 30;

 public:
  void add(int num) {
    Trie *cur = root;
    for (int k = HIGH_BIT; k >= 0; --k) {
      int bit = (num >> k) & 1;
      if (bit == 0) {
        if (!cur->left) {
          cur->left = new Trie();
        }
        cur = cur->left;
      } else {
        if (!cur->right) {
          cur->right = new Trie();
        }
        cur = cur->right;
      }
    }
  }

  int check(int num) {
    Trie *cur = root;
    int x = 0;
    for (int k = HIGH_BIT; k >= 0; --k) {
      int bit = (num >> k) & 1;
      if (bit == 0) {
        // a_i的第k个二进制位为0，应当往表示1的子节点right走
        if (cur->right) {
          cur = cur->right;
          x = x * 2 + 1;
        } else {
          cur = cur->left;
          x = x * 2;
        }
      } else {
        // a_i的第k个二进制位为1，应当往表示0的子节点left走
        if (cur->left) {
          cur = cur->left;
          x = x * 2 + 1;
        } else {
          cur = cur->right;
          x = x * 2;
        }
      }
    }
    return x;
  }

  int findMaximumXOR(vector<int> &nums) {
    int n = nums.size();
    int x = 0;
    for (int i = 1; i < n; ++i) {
      // 将nums[i-1]放入字典树，此时nums[0 .. i-1]都在字典树中
      add(nums[i - 1]);
      // 将nums[i]看作ai，找出最大的x更新答案
      x = max(x, check(nums[i]));
    }
    return x;
  }
};
