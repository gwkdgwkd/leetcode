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