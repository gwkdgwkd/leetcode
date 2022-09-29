/*
nums1中数字x的下一个更大元素是指：
x在nums2中对应位置右侧的第一个比x大的元素。
给你两个没有重复元素的数组nums1和nums2，
下标从0开始计数，其中nums1是nums2的子集。
对于每个0<=i<nums1.length，找出满足nums1[i]==nums2[j]的下标j，
并且在nums2确定nums2[j]的下一个更大元素。
如果不存在下一个更大元素，那么本次查询的答案是-1。
返回一个长度为nums1.length的数组ans作为答案，
满足ans[i]是如上所述的下一个更大元素。

示例1：
输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
输出：[-1,3,-1]
解释：nums1中每个值的下一个更大元素如下所述：
     4不存在下一个更大元素，所以答案是-1。
     1下一个更大元素是3。
     2不存在下一个更大元素，所以答案是-1。

示例2：
输入：nums1 = [2,4], nums2 = [1,2,3,4].
输出：[3,-1]
解释：nums1中每个值的下一个更大元素如下所述：
     2下一个更大元素是3。
     4不存在下一个更大元素，所以答案是-1。

提示：
1 <= nums1.length <= nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 10^4
nums1和nums2中所有整数 互不相同
nums1中的所有整数同样出现在nums2中
*/

// 暴力法
// 时间复杂度：O(n1*n2)
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size,
                        int* returnSize) {
  int i, j;
  int* res = (int*)malloc(sizeof(int) * nums1Size);

  for (i = 0; i < nums1Size; i++) {
    res[i] = -1;
    /* 在nums2中找到nums1[i] */
    for (j = 0; j < nums2Size; j++) {
      if (nums2[j] == nums1[i]) {
        break;
      }
    }
    /* 找到下一个更大的元素, 输出结果 */
    for (j = j + 1; j < nums2Size; j++) {
      if (nums2[j] > nums1[i]) {
        res[i] = nums2[j];
        break;
      }
    }
  }
  *returnSize = nums1Size;
  return res;
}

// 单调栈 + 哈希表
// 时间复杂度为O(n1+n2)
typedef struct {
  int num;
  int greater;
  UT_hash_handle hh;
} NumHash;
NumHash* g_head;
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size,
                        int* returnSize) {
  int i, j;
  int* res = (int*)malloc(sizeof(int) * nums1Size);
  int stack[nums2Size];
  int top = 0;
  NumHash* s = NULL;
  g_head = NULL;

  // 用单调栈求出nums2元素的下一个更大值, 并记录在hash表中
  for (i = nums2Size - 1; i >= 0; i--) {
    while (top != 0 && nums2[i] >= stack[top - 1]) {
      top--;
    }
    s = (NumHash*)malloc(sizeof(NumHash));
    s->num = nums2[i];
    s->greater = (top == 0) ? -1 : stack[top - 1];
    HASH_ADD_INT(g_head, num, s);
    stack[top++] = nums2[i];
  }

  // 遍历nums1元素, 在hash表中找到更大元素输出即可
  for (i = 0; i < nums1Size; i++) {
    HASH_FIND_INT(g_head, &nums1[i], s);
    res[i] = s->greater;
  }
  *returnSize = nums1Size;
  return res;
}

// 单调栈模板[496,503,739]
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size,
                        int* returnSize) {
  if (nums1Size <= 0 || nums2Size <= 0) {
    return NULL;
  }

  int* result = (int*)malloc(nums1Size * sizeof(int));
  int res[nums2Size];
  int stack[nums2Size];
  int top = 0;

  // nums1:[4,1,2]
  // nums2:[1,3,4,2]

  // 倒着往栈里放，单调递增栈
  for (int i = nums2Size - 1; i >= 0; i--) {
    while (top > 0 && nums2[i] >= stack[top - 1]) {  // 当前元素大于等于栈顶
      top--;                                         // 出栈
    }

    res[i] = top > 0 ? stack[top - 1] : -1;
    stack[top++] = nums2[i];  // 入栈

    // for (int i = top - 1; i >= 0; --i) {
    //   printf("%d ", stack[i]);
    // }
    // printf("\n");

    // 2
    // 4
    // 3 4
    // 1 3 4
  }

  // for(int i = 0; i < nums2Size; ++i) {
  //   printf("%d ", res[i]);
  // }
  // printf("\n");
  // 3 4 -1 -1

  for (int i = 0; i < nums1Size; ++i) {
    // 这里可以用hash，节省循环
    for (int j = 0; j < nums2Size; ++j) {
      if (nums1[i] == nums2[j]) {
        result[i] = res[j];
      }
    }
  }

  *returnSize = nums1Size;
  return result;
  // -1,3,-1
}

class Solution {
 public:
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    int len = nums2.size();
    stack<int> stk;
    unordered_map<int, int> hashmap;
    for (int i = 0; i < len; ++i) {
      while (!stk.empty() && nums2[stk.top()] < nums2[i]) {
        hashmap[nums2[stk.top()]] = nums2[i];
        stk.pop();
      }
      stk.push(i);
    }

    vector<int> ans;
    for (int i = 0; i < nums1.size(); ++i) {
      if (hashmap.count(nums1[i])) {
        ans.emplace_back(hashmap[nums1[i]]);
      } else {
        ans.emplace_back(-1);
      }
    }

    return ans;
  }
};