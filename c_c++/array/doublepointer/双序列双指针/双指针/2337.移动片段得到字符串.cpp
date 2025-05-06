/*
给两个字符串start和target，长度均为n。
每个字符串仅由字符'L'、'R'和'_'组成，其中：
字符'L'和'R'表示片段，其中片段'L'只有在其左侧直接存在一个空位时才能向左移动，
而片段'R'只有在其右侧直接存在一个空位时才能向右移动。
字符'_'表示可以被任意'L'或'R'片段占据的空位。
如果在移动字符串start中的片段任意次之后可以得到字符串target，
返回true；否则，返回false。

示例1：
输入：start = "_L__R__R_", target = "L______RR"
输出：true
解释：可以从字符串start获得target，需要进行下面的移动：
     将第一个片段向左移动一步，字符串现在变为"L___R__R_"。
     将最后一个片段向右移动一步，字符串现在变为"L___R___R"。
     将第二个片段向右移动三步，字符串现在变为"L______RR"。
     可以从字符串start得到target，所以返回true。

示例2：
输入：start = "R_L_", target = "__LR"
输出：false
解释：字符串start中的'R'片段可以向右移动一步得到"_RL_"。
     但是，在这一步之后，不存在可以移动的片段，所以无法从字符串start得到target。

示例3：
输入：start = "_R", target = "R_"
输出：false
解释：字符串start中的片段只能向右移动，所以无法从字符串start得到target。


提示：
n == start.length == target.length
1 <= n <= 10^5
start和target由字符'L'、'R'和'_'组成
*/

// 双指针
class Solution {
  // 时间复杂度：O(n)，其中n是字符串start和target的长度。需要遍历两个字符串各一次。
  // 空间复杂度：O(1)。只需要使用常量的额外空间。
 public:
  bool canChange(string start, string target) {
    int n = start.size();
    int i = 0;
    int j = 0;

    while (i < n && j < n) {
      // 跳过所有的‘_’
      while (i < n && start[i] == '_') {
        ++i;
      }
      while (j < n && target[j] == '_') {
        ++j;
      }

      // 当i和j都小于n时，比较非‘_’的字符：
      if (i < n && j < n) {
        // 1.如果start[i]!=target[j]，则start和target中的当前字符不匹配，返回false；
        if (start[i] != target[j]) {
          return false;
        }
        // 2.如果start[i]=target[j]，则当前字符是‘L’时应有i≥j，
        //   当前字符是‘R’时应有i≤j，如果当前字符与两个下标的关系不符合该规则，返回false。
        char c = start[i];
        if ((c == 'L' && i < j) || (c == 'R' && i > j)) {
          return false;
        }
        ++i;
        ++j;
      }
    }

    // 如果i和j中有一个下标大于等于n，则有一个字符串已经遍历到末尾，
    // 继续遍历另一个字符串中的其余字符，如果其余字符中出现非‘_’的字符，
    // 则该字符不能与任意字符匹配，返回false：
    while (i < n) {
      if (start[i] != '_') {
        return false;
      }
      ++i;
    }
    while (j < n) {
      if (target[j] != '_') {
        return false;
      }
      ++j;
    }

    return true;
  }
};

// 脑筋急转弯
class Solution {
  // 时间复杂度：O(n)，其中n为start的长度。
  // 空间复杂度：O(n)。
 public:
  bool canChange(string start, string target) {
    string s = start, t = target;

    // 首先，无论怎么移动，由于L和R无法互相穿过对方，
    // 那么去掉_后的剩余字符应该是相同的，否则返回false：
    s.erase(remove(s.begin(), s.end(), '_'), s.end());
    t.erase(remove(t.begin(), t.end(), '_'), t.end());
    if (s != t) {
      return false;
    }

    // 用双指针从左向右遍历start和target，分类讨论：
    // 如果当前字符为L且i<j，由于L由于无法向右移动，返回false；
    // 如果当前字符为R且i>j，由于R由于无法向左移动，返回false。
    for (int i = 0, j = 0; i < start.length(); i++) {
      if (start[i] == '_') {
        continue;
      }
      while (target[j] == '_') {
        j++;
      }
      if (i != j && (start[i] == 'L') == (i < j)) {
        return false;
      }

      j++;
    }

    return true;  // 遍历完，若中途没有返回false就返回true
  }
};