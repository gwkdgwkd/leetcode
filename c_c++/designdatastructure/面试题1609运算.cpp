/*
请实现整数数字的乘法、减法和除法运算，运算结果均为整数数字，
程序中只允许使用加法运算符和逻辑运算符，允许程序中出现正负常数，不允许使用位运算。

你的实现应该支持如下操作：
Operations() 构造函数
minus(a, b) 减法，返回a - b
multiply(a, b) 乘法，返回a * b
divide(a, b) 除法，返回a / b

示例：
Operations operations = new Operations();
operations.minus(1, 2); // 返回-1
operations.multiply(3, 4); // 返回12
operations.divide(5, -2); // 返回-2

提示：
你可以假设函数输入一定是有效的，例如不会出现除法分母为0的情况
单个用例的函数调用次数不会超过1000次
*/

typedef struct {
} Operations;

Operations* operationsCreate() {
  Operations* ope = NULL;
  return ope;
}
// 这个要返回long型，不然INT_MIN取反会出错
long oppNum(long a) {
  if (a == 0) {
    return 0;
  }
  long ret = 0;
  long temp;
  if (a > 0) {
    temp = -1;
    while (ret + a > 0) {
      if (ret + temp + a == 0) {
        break;
      } else if (ret + temp + a > 0) {
        ret += temp;
        temp = temp + temp;
      } else {
        temp = -1;
      }
    }
  }
  if (a < 0) {
    temp = 1;
    while (ret + a < 0) {
      if (ret + temp + a == 0) {
        break;
      } else if (ret + temp + a < 0) {
        ret += temp;
        temp = temp + temp;
      } else {
        temp = 1;
      }
    }
  }
  return ret + temp;
}

// 将形参a和b改成long型，方便除法中a为-INT_MIN时的运用，
// 其实也可以通过将m设置成负的，n设置成正的来解决
long operationsMinus(Operations* obj, long a, long b) {
  // printf("%d\n",neg(-4));
  return a + oppNum(b);
}
int operationsMultiply(Operations* obj, int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  }
  int flag = 1;
  if (b < 0) {  // 处理b为负的情况
    flag = 0;
    b = oppNum(b);
  }
  long ret = 0;
  long fre = 1;   // 对应的倍数
  long temp = a;  // a*fre
  while (b > 0) {
    if (operationsMinus(0, b, fre) == 0) {
      break;
    } else if (operationsMinus(0, b, fre) > 0) {
      ret += temp;
      b = operationsMinus(0, b, fre);

      temp += temp;
      fre += fre;
    } else {
      temp = a;
      fre = 1;
    }
  }
  return flag == 1 ? ret + temp : oppNum(ret + temp);
}

long operationsDivide(Operations* obj, int a, int b) {
  if (a == 0) {
    return 0;
  }
  // 处理异号的情况,不然会溢出
  int flag = 1;
  long m = a;
  long n = b;
  if ((m > 0 && n < 0) || m < 0 && n > 0) {
    flag = 0;
    if (m < 0) {
      m = oppNum(m);
    } else {
      n = oppNum(n);
    }
  } else if (m < 0) {
    m = oppNum(m);
    n = oppNum(n);
  }
  long ret = 0;
  long temp = n;
  long fre = 1;
  while (m > 0) {
    if (operationsMinus(0, m, temp) >= 0) {
      ret += fre;
      m = operationsMinus(0, m, temp);
      fre += fre;
      temp += temp;
    } else {
      fre = 1;
      temp = n;
      if (operationsMinus(0, m, temp) < 0) {
        break;
      }
    }
  }
  return flag == 1 ? ret : oppNum(ret);
}
void operationsFree(Operations* obj) {}

class Operations {
 private:
  // 存的是[-1,-2,-4...]、[1,2,4...]，取反和判断溢出时用：
  vector<int> negs, poss;

  int neg(int a) {
    if (!a) return 0;
    int result = 0;
    if (a > 0) {
      // 从绝对值最大的部分开始填充：
      for (auto p = negs.rbegin(); p != negs.rend(); p++) {
        if (*p + a < 0) continue;

        a += *p;
        result += *p;
      }
    } else {
      for (auto p = poss.rbegin(); p != poss.rend(); p++) {
        if (*p + a > 0) continue;

        a += *p;
        result += *p;
      }
    }
    return result;
  }

 public:
  Operations() {
    // 构造poss和negs
    int p = 1, n = -1;
    poss.push_back(p);
    negs.push_back(n);

    for (int i = 0; i < 30; i++) {
      p += p;
      n += n;

      poss.push_back(p);
      negs.push_back(n);
    }
  }

  int minus(int a, int b) { return a + neg(b); }

  int multiply(int a, int b) {
    if (!a || !b) return 0;
    // 这一步是针对b=INT_MIN的情况，防止下一步取neg时溢出
    if (a == 1) return b;
    if (b < 0) return neg(multiply(a, neg(b)));

    int result = a;
    int times = 1;  // times表示当前结果里已经累加了几个a了

    // times < poss[30]是为了防止溢出
    while (times < poss[30] && times + times <= b) {
      result += result;
      times += times;
    }
    result += multiply(a, minus(b, times));

    return result;
  }

  int divide(int a, int b) {
    if (!a) return 0;

    int result = 1;
    // 只写同号的情况，非同号时用neg转化成同号，但是要注意溢出
    if (a > 0) {
      if (b == INT_MIN) return 0;  // 防止下一句取neg的时候溢出
      if (b < 0) return neg(divide(a, neg(b)));
      if (a < b) return 0;

      int acc = b;  // 不断往acc里填充b，直到acc达到a
      while (acc < poss[30] && a >= acc + acc) {
        result += result;  // result表示已经填充了几个b了
        acc += acc;
      }
      result += divide(minus(a, acc), b);
    } else {
      if (b == 1) return a;  // 防止若a=INT_MIN造成下一句运算时溢出
      if (b > 0) return neg(divide(a, neg(b)));
      if (a > b) return 0;

      int acc = b;
      while (acc >= negs[30] && a <= acc + acc) {
        result += result;
        acc += acc;
      }
      result += divide(minus(a, acc), b);
    }
    return result;
  }
};
