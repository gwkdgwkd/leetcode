/*
给一个整数数组digits，其中每个元素是一个数字（0-9）。数组中可能存在重复元素。
需要找出所有满足下述条件且互不相同的整数：
该整数由digits中的三个元素按任意顺序依次连接组成。
该整数不含前导零
该整数是一个偶数
例如，给定的digits是[1,2,3] ，整数132和312满足上面列出的全部条件。
将找出的所有互不相同的整数按递增顺序排列，并以数组形式返回。

示例1：
输入：digits = [2,1,3,0]
输出：[102,120,130,132,210,230,302,310,312,320]
解释：所有满足题目条件的整数都在输出数组中列出。
     注意，答案数组中不含有奇数或带前导零的整数。

示例2：
输入：digits = [2,2,8,8,2]
输出：[222,228,282,288,822,828,882]
解释：同样的数字（0-9）在构造整数时可以重复多次，重复次数最多与其在digits中出现的次数一样。
     在这个例子中，数字8在构造288、828和882时都重复了两次。

示例3：
输入：digits = [3,7,5]
输出：[]
解释：使用给定的digits无法构造偶数。


提示：
3 <= digits.length <= 100
0 <= digits[i] <= 9
*/

class Solution {
 public:
  vector<int> findEvenNumbers(vector<int>& digits) {
    sort(digits.begin(), digits.end());
    int n = digits.size();
    set<int> ans;
    for (int i = 0; i < n; ++i) {
      if (digits[i] == 0) {
        continue;
      }
      for (int j = 0; j < n; ++j) {
        if (j == i) {
          continue;
        }
        for (int k = 0; k < n; ++k) {
          if (k == i || k == j || digits[k] % 2) {
            continue;
          }
          ans.insert(digits[i] * 100 + digits[j] * 10 + digits[k]);
        }
      }
    }

    return {ans.begin(), ans.end()};
  }
};

// 枚举数组中的元素组合
class Solution {
 public:
  vector<int> findEvenNumbers(vector<int>& digits) {
    unordered_set<int> nums;  // 目标偶数集合
    int n = digits.size();
    // 遍历三个数位的下标
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          // 判断是否满足目标偶数的条件
          if (i == j || j == k || i == k) {
            continue;
          }
          int num = digits[i] * 100 + digits[j] * 10 + digits[k];
          if (num >= 100 && num % 2 == 0) {
            nums.insert(num);
          }
        }
      }
    }
    // 转化为升序排序的数组
    vector<int> res;
    for (const int num : nums) {
      res.push_back(num);
    }
    sort(res.begin(), res.end());
    return res;
  }
};

// 遍历所有可能的3位偶数
class Solution {
 public:
  vector<int> findEvenNumbers(vector<int>& digits) {
    vector<int> res;               // 目标偶数数组
    unordered_map<int, int> freq;  // 整数数组中各数字的出现次数
    for (const int digit : digits) {
      ++freq[digit];
    }
    // 枚举所有三位偶数，维护整数中各数位的出现次数并比较判断是否为目标偶数
    for (int i = 100; i < 1000; i += 2) {
      unordered_map<int, int> freq1;
      int tmp = i;
      while (tmp) {
        ++freq1[tmp % 10];
        tmp /= 10;
      }
      if (all_of(freq1.begin(), freq1.end(), [&](const auto& x) {
            return freq[x.first] >= freq1[x.first];
          })) {
        res.push_back(i);
      }
    }
    return res;
  }
};

// 暴力枚举
class Solution {
 public:
  vector<int> findEvenNumbers(vector<int>& digits) {
    int cnt[10]{};
    for (int d : digits) {
      cnt[d]++;
    }
    vector<int> ans;
    for (int i = 100; i < 1000; i += 2) {  // 枚举所有三位数偶数i
      int c[10]{};
      bool ok = true;
      for (int x = i; x > 0; x /= 10) {  // 枚举i的每一位d
        int d = x % 10;
        // 如果i中d的个数比digits中的还多，那么i无法由digits中的数字组成
        if (++c[d] > cnt[d]) {
          ok = false;
          break;
        }

        if (ok) {
          ans.push_back(i);
        }
      }
      return ans;
    }
  }
};

// 回溯
class Solution {
 public:
  vector<int> findEvenNumbers(vector<int>& digits) {
    int cnt[10]{};
    for (int d : digits) {
      cnt[d]++;
    }
    vector<int> ans;
    // i=0百位，i=1十位，i=2个位，x表示当前正在构造的数字
    auto dfs = [&](this auto&& dfs, int i, int x) -> void {
      if (i == 3) {
        ans.push_back(x);
        return;
      }

      for (int d = 0; d < 10; d++) {
        if (cnt[d] > 0 && (i == 0 && d > 0 || i == 1 || i == 2 && d % 2 == 0)) {
          cnt[d]--;  // 消耗一个数字d
          dfs(i + 1, x * 10 + d);
          cnt[d]++;  // 复原
        }
      }
    };

    dfs(0, 0);

    return ans;
  }
};
