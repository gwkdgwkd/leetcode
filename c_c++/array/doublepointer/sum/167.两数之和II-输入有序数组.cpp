/*
给你一个下标从1开始的整数数组numbers，该数组已按非递减顺序排列，
请你从数组中找出满足相加之和等于目标数target的两个数。
如果设这两个数分别是numbers[index1]和numbers[index2]，
则1<=index1<index2<=numbers.length。
以长度为2的整数数组[index1, index2]的形式返回这两个整数的下标index1和index2。
你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。
你所设计的解决方案必须只使用常量级的额外空间。

示例1：
输入：numbers = [2,7,11,15], target = 9
输出：[1,2]
解释2与7之和等于目标数9。因此index1 = 1, index2 = 2。返回[1, 2]。

示例2：
输入：numbers = [2,3,4], target = 6
输出：[1,3]
解释：2与4之和等于目标数6。因此index1 = 1, index2 = 3。返回[1, 3]。

示例3：
输入：numbers = [-1,0], target = -1
输出：[1,2]
解释：-1与0之和等于目标数-1。因此index1 = 1, index2 = 2。返回[1, 2]。


提示：
2 <= numbers.length <= 3 * 10^4
-1000 <= numbers[i] <= 1000
numbers按非递减顺序排列
-1000 <= target <= 1000
仅存在一个有效答案
*/

// 剑指OfferII006排序数组中两个数字之和，下标起点不同

// 双指针
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize) {
  int left = 0;
  int right = numbersSize - 1;

  int *res = (int *)malloc(sizeof(int) * 2);
  *returnSize = 2;
  while (left < right) {
    int sum = numbers[left] + numbers[right];
    if (sum == target) {
      res[0] = left + 1;
      res[1] = right + 1;
      return res;
    } else if (sum < target) {
      left++;
    } else if (sum > target) {
      right--;
    }
  }

  return res;
}

class Solution {
 public:
  vector<int> twoSum(vector<int> &numbers, int target) {
    sort(numbers.begin(), numbers.end());

    int left = 0;
    int right = numbers.size() - 1;
    while (left < right) {
      int sum = numbers[left] + numbers[right];
      if (sum < target) {
        ++left;
      } else if (sum > target) {
        --right;
      } else {
        return {left + 1, right + 1};
      }
    }

    return {};
  }
};

// 哈希表
#define MAXNUM 30000
typedef struct {
  int ikey;
  int index[MAXNUM];
  int count;
  UT_hash_handle hh;
} MYSTRUCT;
MYSTRUCT *g_user = NULL;
void InitGobal(void) {
  g_user = NULL;
  return;
}
MYSTRUCT *FindUser(int num) {
  MYSTRUCT *s = NULL;
  HASH_FIND_INT(g_user, &num, s);
  return s;
}
void AddUser(int num, int spc) {
  MYSTRUCT *s = NULL;
  HASH_FIND_INT(g_user, &num, s);
  if (s == NULL) {
    s = (MYSTRUCT *)malloc(sizeof(MYSTRUCT));
    s->ikey = num;
    s->index[0] = spc;
    s->count = 1;
    HASH_ADD_INT(g_user, ikey, s);
  } else {
    s->index[s->count] = spc;
    s->count += 1;
  }
}
void DelUser(void) {
  MYSTRUCT *currentUser = NULL;
  MYSTRUCT *tmp = NULL;
  HASH_ITER(hh, g_user, currentUser, tmp) {
    HASH_DEL(g_user, currentUser);
    free(currentUser);
  }
}
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize) {
  int i;
  MYSTRUCT *currentUser = NULL;
  MYSTRUCT *tmp = NULL;
  MYSTRUCT *s = NULL;
  int gap;
  InitGobal();
  for (i = 0; i < numbersSize; i++) {
    AddUser(numbers[i], i + 1);
  }
  HASH_ITER(hh, g_user, currentUser, tmp) {
    gap = target - currentUser->ikey;
    s = FindUser(gap);
    if (s != NULL) {
      break;
    }
  }

  int *ans = (int *)malloc(sizeof(int) * 2);
  if (s == currentUser) {
    ans[0] = currentUser->index[0];
    ans[1] = currentUser->index[1];
  } else {
    ans[0] = currentUser->index[0];
    ans[1] = s->index[0];
  }

  *returnSize = 2;
  DelUser();
  return ans;
}