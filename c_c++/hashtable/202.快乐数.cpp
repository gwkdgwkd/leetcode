/*
编写一个算法来判断一个数n是不是快乐数。
快乐数定义为：
对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为1，也可能是无限循环但始终变不到1。
如果这个过程结果为1，那么这个数就是快乐数。
如果n是快乐数就返回true；不是，则返回false。

示例1：
输入：n = 19
输出：true
解释：
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 02 = 1

示例2：
输入：n = 2
输出：false

提示：1 <= n <= 2^31 - 1
*/

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

class Solution {
 public:
  int getSum(int n) {
    int sum = 0;
    while (n) {
      sum += (n % 10) * (n % 10);
      n /= 10;
    }
    return sum;
  }

  bool isHappy(int n) {
    int sum = 0;
    unordered_set<int> set;
    while (1) {
      sum = getSum(n);
      if (sum == 1) {
        return true;
      }
      if (set.find(sum) != set.end()) {
        return false;
      } else {
        set.insert(sum);
      }
      n = sum;
    }
  }
};