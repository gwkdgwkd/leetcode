// 哈希表
typedef struct {
  int val;
  int key;
  UT_hash_handle hh;
} hashTable;
hashTable *userInfo;
hashTable *FindUser(int ikey) {
  hashTable *s = NULL;

  HASH_FIND_INT(userInfo, &ikey, s);
  return s;
}
void AddUsers(int ikey, int ival) {
  hashTable *s = FindUser(ikey);
  if (s == NULL) {
    hashTable *tmp = (hashTable *)malloc(sizeof(hashTable));
    if (tmp == NULL) {
      return;
    }

    tmp->val = ival;
    tmp->key = ikey;

    HASH_ADD_INT(userInfo, key, tmp);
  } else {
    s->val = ival;
  }

  return;
}

int GetResult(int x) {
  int result = 0;
  int tmp = 0;

  while (x != 0) {
    tmp = x % 10;
    result += tmp * tmp;
    x = x / 10;
  }

  return result;
}
bool isHappy(int n) {
  int result;
  int num = n;
  userInfo = NULL;

  while (1) {
    hashTable *p = FindUser(num);
    if (p != NULL) {
      return false;
    }

    AddUsers(num, 0);
    result = GetResult(num);
    if (result == 1) {
      return true;
    } else {
      num = result;
    }
  }

  return false;
}

// 快慢指针
int get_next(int n) {
  int sum = 0;
  int a;
  while (n) {
    a = n % 10;
    sum += a * a;
    n /= 10;
  }
  return sum;
}
bool isHappy(int n) {
  int a = n, b = n;
  while (true) {
    b = get_next(b);

    if (b == 1) return true;

    b = get_next(b);
    a = get_next(a);

    if (a == b) return false;
  }
}
bool isHappy(int n) {
  int slow = n, quick = n;
  do {
    quick = getsum(quick);
    quick = getsum(quick);  // 快指针每次走两步
    slow = getsum(slow);    // 慢指针每次走一步
    if (slow == 1 || quick == 1) return true;
  } while (quick != slow);
  return false;
}