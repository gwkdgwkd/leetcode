/*
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

数值（按顺序）可以分成以下几个部分：
1.若干空格
2.一个小数或者整数
3.（可选）一个'e'或'E'，后面跟着一个整数
4.若干空格

小数（按顺序）可以分成以下几个部分：
1.（可选）一个符号字符（'+'或'-'）
2.下述格式之一：
  a.至少一位数字，后面跟着一个点'.'
  b.至少一位数字，后面跟着一个点'.'，后面再跟着至少一位数字
  c.一个点'.'，后面跟着至少一位数字

整数（按顺序）可以分成以下几个部分：
1.（可选）一个符号字符（'+' 或 '-'）
2.至少一位数字

部分数值列举如下：
["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]

部分非数值列举如下：
["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]

示例1：
输入：s = "0"
输出：true

示例2：
输入：s = "e"
输出：false

示例3：
输入：s = "."
输出：false

示例4：
输入：s = "    .1  "
输出：true

提示：
1 <= s.length <= 20
s仅含英文字母（大写和小写），数字（0-9），加号'+'，减号'-'，空格' '或者点'.'。
*/

// 确定有限状态自动机（以下简称自动机）是一类计算模型。
// 它包含一系列状态，这些状态中：
// 有一种特殊的状态，被称作初始状态，还有一系列状态被称为接受状态，
// 它们组成了一个特殊的集合，其中，一个状态可能既是初始状态，也是接受状态。
// 起初，这个自动机处于初始状态，随后，它顺序地读取字符串中的每一个字符，
// 并根据当前状态和读入的字符，按照某个事先约定好的转移规则，转移到下一个状态；
// 当状态转移完成后，它就读取下一个字符，当字符串全部读取完毕后，
// 如果自动机处于某个接受状态，则判定该字符串被接受，否则，判定该字符串被拒绝。
// 如果输入的过程中某一步转移失败了，即不存在对应的转移规则，此时计算将提前中止，
// 在这种情况下也判定该字符串被拒绝。
// 一个自动机，总能够回答某种形式的对于给定的输入字符串S，判断其是否满足条件P的问题。
// 在本题中，条件P即为构成合法的表示数值的字符串。

// 确定有限状态自动机
// 时间复杂度：O(n)
// 空间复杂度：O(1)
enum State {
  STATE_INITIAL,            // 起始的空格
  STATE_INT_SIGN,           // 符号位
  STATE_INTEGER,            // 整数部分
  STATE_POINT,              // 左侧有整数的小数点
  STATE_POINT_WITHOUT_INT,  // 左侧无整数的小数点（需要对左侧有无整数的两种小数点做区分）
  STATE_FRACTION,           // 小数部分
  STATE_EXP,                // 字符e
  STATE_EXP_SIGN,           // 指数部分的符号位
  STATE_EXP_NUMBER,         // 指数部分的整数部分
  STATE_END,                // 末尾的空格
  STATE_ILLEGAL
};
enum CharType {
  CHAR_NUMBER,
  CHAR_EXP,
  CHAR_POINT,
  CHAR_SIGN,
  CHAR_SPACE,
  CHAR_ILLEGAL
};
enum CharType toCharType(char ch) {
  if (ch >= '0' && ch <= '9') {
    return CHAR_NUMBER;
  } else if (ch == 'e' || ch == 'E') {
    return CHAR_EXP;
  } else if (ch == '.') {
    return CHAR_POINT;
  } else if (ch == '+' || ch == '-') {
    return CHAR_SIGN;
  } else if (ch == ' ') {
    return CHAR_SPACE;
  } else {
    return CHAR_ILLEGAL;
  }
}
enum State transfer(enum State st, enum CharType typ) {
  switch (st) {
    case STATE_INITIAL: {
      switch (typ) {
        case CHAR_SPACE:
          return STATE_INITIAL;
        case CHAR_NUMBER:
          return STATE_INTEGER;
        case CHAR_POINT:
          return STATE_POINT_WITHOUT_INT;
        case CHAR_SIGN:
          return STATE_INT_SIGN;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_INT_SIGN: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_INTEGER;
        case CHAR_POINT:
          return STATE_POINT_WITHOUT_INT;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_INTEGER: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_INTEGER;
        case CHAR_EXP:
          return STATE_EXP;
        case CHAR_POINT:
          return STATE_POINT;
        case CHAR_SPACE:
          return STATE_END;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_POINT: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_FRACTION;
        case CHAR_EXP:
          return STATE_EXP;
        case CHAR_SPACE:
          return STATE_END;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_POINT_WITHOUT_INT: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_FRACTION;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_FRACTION: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_FRACTION;
        case CHAR_EXP:
          return STATE_EXP;
        case CHAR_SPACE:
          return STATE_END;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_EXP: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_EXP_NUMBER;
        case CHAR_SIGN:
          return STATE_EXP_SIGN;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_EXP_SIGN: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_EXP_NUMBER;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_EXP_NUMBER: {
      switch (typ) {
        case CHAR_NUMBER:
          return STATE_EXP_NUMBER;
        case CHAR_SPACE:
          return STATE_END;
        default:
          return STATE_ILLEGAL;
      }
    }
    case STATE_END: {
      switch (typ) {
        case CHAR_SPACE:
          return STATE_END;
        default:
          return STATE_ILLEGAL;
      }
    }
    default:
      return STATE_ILLEGAL;
  }
}
bool isNumber(char* s) {
  int len = strlen(s);
  enum State st = STATE_INITIAL;

  for (int i = 0; i < len; i++) {
    enum CharType typ = toCharType(s[i]);
    enum State nextState = transfer(st, typ);
    if (nextState == STATE_ILLEGAL) return false;
    st = nextState;
  }
  return st == STATE_INTEGER || st == STATE_POINT || st == STATE_FRACTION ||
         st == STATE_EXP_NUMBER || st == STATE_END;
}

class Solution {
 public:
  enum State {
    STATE_INITIAL,
    STATE_INT_SIGN,
    STATE_INTEGER,
    STATE_POINT,
    STATE_POINT_WITHOUT_INT,
    STATE_FRACTION,
    STATE_EXP,
    STATE_EXP_SIGN,
    STATE_EXP_NUMBER,
    STATE_END
  };

  enum CharType {
    CHAR_NUMBER,
    CHAR_EXP,
    CHAR_POINT,
    CHAR_SIGN,
    CHAR_SPACE,
    CHAR_ILLEGAL
  };

  CharType toCharType(char ch) {
    if (ch >= '0' && ch <= '9') {
      return CHAR_NUMBER;
    } else if (ch == 'e' || ch == 'E') {
      return CHAR_EXP;
    } else if (ch == '.') {
      return CHAR_POINT;
    } else if (ch == '+' || ch == '-') {
      return CHAR_SIGN;
    } else if (ch == ' ') {
      return CHAR_SPACE;
    } else {
      return CHAR_ILLEGAL;
    }
  }

  bool isNumber(string s) {
    unordered_map<State, unordered_map<CharType, State>> transfer{
        {STATE_INITIAL,
         {{CHAR_SPACE, STATE_INITIAL},
          {CHAR_NUMBER, STATE_INTEGER},
          {CHAR_POINT, STATE_POINT_WITHOUT_INT},
          {CHAR_SIGN, STATE_INT_SIGN}}},
        {STATE_INT_SIGN,
         {{CHAR_NUMBER, STATE_INTEGER}, {CHAR_POINT, STATE_POINT_WITHOUT_INT}}},
        {STATE_INTEGER,
         {{CHAR_NUMBER, STATE_INTEGER},
          {CHAR_EXP, STATE_EXP},
          {CHAR_POINT, STATE_POINT},
          {CHAR_SPACE, STATE_END}}},
        {STATE_POINT,
         {{CHAR_NUMBER, STATE_FRACTION},
          {CHAR_EXP, STATE_EXP},
          {CHAR_SPACE, STATE_END}}},
        {STATE_POINT_WITHOUT_INT, {{CHAR_NUMBER, STATE_FRACTION}}},
        {STATE_FRACTION,
         {{CHAR_NUMBER, STATE_FRACTION},
          {CHAR_EXP, STATE_EXP},
          {CHAR_SPACE, STATE_END}}},
        {STATE_EXP,
         {{CHAR_NUMBER, STATE_EXP_NUMBER}, {CHAR_SIGN, STATE_EXP_SIGN}}},
        {STATE_EXP_SIGN, {{CHAR_NUMBER, STATE_EXP_NUMBER}}},
        {STATE_EXP_NUMBER,
         {{CHAR_NUMBER, STATE_EXP_NUMBER}, {CHAR_SPACE, STATE_END}}},
        {STATE_END, {{CHAR_SPACE, STATE_END}}}};

    int len = s.length();
    State st = STATE_INITIAL;

    for (int i = 0; i < len; i++) {
      CharType typ = toCharType(s[i]);
      if (transfer[st].find(typ) == transfer[st].end()) {
        return false;
      } else {
        st = transfer[st][typ];
      }
    }
    return st == STATE_INTEGER || st == STATE_POINT || st == STATE_FRACTION ||
           st == STATE_EXP_NUMBER || st == STATE_END;
  }
};